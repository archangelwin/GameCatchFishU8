#include "GameSocket.h"
#include <thread>
#include "SessionManager.h"

CGameSocket::CGameSocket()
{ 
	// ��ʼ��
	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));

	m_cbSendRound = 0;
	m_cbRecvRound = 0;
	m_dwSendXorKey = 0;
	m_dwRecvXorKey = 0;

	m_dwSendTickCount = 0;
	m_dwRecvTickCount = 0;
	m_dwSendPacketCount = 0;
	m_dwRecvPacketCount = 0;

	m_eSocketStatus = eSoccketUnknown;
	m_pGameSocketSink = nullptr;
	m_dwPreRecvTick = 0;
	m_nMaxKeepAliveTime = BLOCKSECONDS + 2;
}

CGameSocket::~CGameSocket()
{
	Destroy();
}

void CGameSocket::closeSocket()
{
#ifdef WIN32
    closesocket(m_sockClient);
    WSACleanup();
#else
    close(m_sockClient);
#endif
}

bool CGameSocket::Create(const char* pszServerIP, int nServerPort, int nBlockSec, bool bKeepAlive /*= FALSE*/)
{
	// ������
	if(pszServerIP == 0 || strlen(pszServerIP) > 15) {
		return false;
	}

#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if (ret != 0) {
		return false;
	}
#endif

	m_cbSendRound = 0;
	m_cbRecvRound = 0;
	m_dwSendXorKey = 0;
	m_dwRecvXorKey = 0;

	m_dwSendTickCount = 0;
	m_dwRecvTickCount = 0;
	m_dwSendPacketCount = 0;
	m_dwRecvPacketCount = 0;

	// �������׽���
	m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sockClient == INVALID_SOCKET) {
        closeSocket();
		return false;
	}

	// ����SOCKETΪKEEPALIVE
	if(bKeepAlive)
	{
		int		optval=1;
		if(setsockopt(m_sockClient, SOL_SOCKET, SO_KEEPALIVE, (char *) &optval, sizeof(optval)))
		{
            closeSocket();
			return false;
		}
	}

#ifdef WIN32
	DWORD nMode = 1;
	int nRes = ioctlsocket(m_sockClient, FIONBIO, &nMode);
	if (nRes == SOCKET_ERROR) {
		closeSocket();
		return false;
	}
#else
	// ����Ϊ��������ʽ
	fcntl(m_sockClient, F_SETFL, O_NONBLOCK);
#endif

	unsigned long serveraddr = inet_addr(pszServerIP);
	if(serveraddr == INADDR_NONE)	// ���IP��ַ��ʽ����
	{
		closeSocket();
		return false;
	}

	sockaddr_in	addr_in;
	memset((void *)&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(nServerPort);
	addr_in.sin_addr.s_addr = serveraddr;
	
	if(connect(m_sockClient, (sockaddr *)&addr_in, sizeof(addr_in)) == SOCKET_ERROR) {
		if (hasError()) {
			closeSocket();
			return false;
		}
		else	// WSAWOLDBLOCK
		{
			timeval timeout;
			timeout.tv_sec	= nBlockSec;
			timeout.tv_usec	= 0;
			fd_set writeset, exceptset;
			FD_ZERO(&writeset);
			FD_ZERO(&exceptset);
			FD_SET(m_sockClient, &writeset);
			FD_SET(m_sockClient, &exceptset);

			int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
			if (ret == 0 || ret < 0) {
				closeSocket();
				return false;
			} else	// ret > 0
			{
				ret = FD_ISSET(m_sockClient, &exceptset);
				if(ret)		// or (!FD_ISSET(m_sockClient, &writeset)
				{
					closeSocket();
					return false;
				}
			}
		}
	}

	m_nInbufLen		= 0;
	m_nInbufStart	= 0;
	m_nOutbufLen	= 0;

	struct linger so_linger;
	so_linger.l_onoff = 1;
	so_linger.l_linger = 500;
	setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

	return true;
}

bool CGameSocket::SendMsg(unsigned short wMainCmdID, unsigned short wSubCmdID, void* pBuf, int nSize)
{
	//if(pBuf == 0 || nSize <= 0) {
	//	return false;
	//}

	if (m_sockClient == INVALID_SOCKET) {
		{

		}
		return false;
	}

	if (nSize > SOCKET_TCP_PACKET) return false;

	//��������
	BYTE cbDataBuffer[SOCKET_TCP_BUFFER];
	TCP_Head * pHead = (TCP_Head *)cbDataBuffer;
	pHead->CommandInfo.wMainCmdID = wMainCmdID;
	pHead->CommandInfo.wSubCmdID = wSubCmdID;
	if (nSize > 0)
	{
		memcpy(pHead + 1, pBuf, nSize);
	}

	//��������
	unsigned short wSendSize = EncryptBuffer(cbDataBuffer, sizeof(TCP_Head)+nSize, sizeof(cbDataBuffer));

	// ���ͨѶ��Ϣ������
	// ���BUF���
	if (m_nOutbufLen + wSendSize > OUTBUFSIZE) {
		// ��������OUTBUF�е����ݣ������OUTBUF��
		Flush();
		if (m_nOutbufLen + wSendSize > OUTBUFSIZE) {
			// ������
			Destroy();
			return false;
		}
	}
	// ������ӵ�BUFβ
	memcpy(m_bufOutput + m_nOutbufLen, cbDataBuffer, wSendSize);
	m_nOutbufLen += wSendSize;
	return true;
}

bool CGameSocket::ReceiveMsg(void* pBuf, int& nSize)
{
	//������
	if(pBuf == NULL || nSize <= 0) {
		return false;
	}
	
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	// ����Ƿ���һ����Ϣ(С��2���޷���ȡ����Ϣ����)
	if (m_nInbufLen < sizeof(TCP_Head)) {
		//  ���û������ɹ�  ����   ���û��������ֱ�ӷ���
		if (!recvFromSock() || m_nInbufLen < sizeof(TCP_Head)) {		// ���m_nInbufLen������
			return false;
		}
	}


    // ����Ҫ��������Ϣ�Ĵ�С��һ����Ϣ����СΪ������Ϣ�ĵ�һ��16�ֽڣ�����Ϊ���λ�����������Ҫ�ֿ�����
	//int packsize = (unsigned char)m_bufInput[m_nInbufStart] +
	//	(unsigned char)m_bufInput[(m_nInbufStart + 1) % INBUFSIZE] * 256; // ע���ֽ��򣬸�λ+��λ
	// ���Ƴ�һ����Ϣͷ
	if (m_nInbufStart + sizeof(TCP_Head) > INBUFSIZE) {
		// ���һ����Ϣ�лؾ�����������ڻ��λ�������ͷβ��
		// �ȿ������λ�����ĩβ������
		int copylen = INBUFSIZE - m_nInbufStart;
		memcpy(pBuf, m_bufInput + m_nInbufStart, copylen);

		// �ٿ������λ�����ͷ����ʣ�ಿ��
		memcpy((unsigned char *)pBuf + copylen, m_bufInput, sizeof(TCP_Head)-copylen);
	}
	else {
		// ��Ϣû�лؾ�����һ�ο�����ȥ
		memcpy(pBuf, m_bufInput + m_nInbufStart, sizeof(TCP_Head));
	}
	TCP_Head * pHead = (TCP_Head *)pBuf;
	int packsize = pHead->TCPInfo.wPacketSize;
	// �����Ϣ���ߴ���� �ݶ����16k
	if (packsize <= 0 || packsize > _MAX_MSGSIZE) {
		m_nInbufLen = 0;		// ֱ�����INBUF
		m_nInbufStart = 0;
		return false;
	}

	// �����Ϣ�Ƿ�����(�����Ҫ��������Ϣ���ڴ�ʱ���������ݳ��ȣ���Ҫ�ٴ��������ʣ������)
	if (packsize > m_nInbufLen) {
		// ���û������ɹ�   ����    ��Ȼ�޷���ȡ�����������ݰ�  �򷵻أ�ֱ��ȡ��������
		if (!recvFromSock() || packsize > m_nInbufLen) {	// ���m_nInbufLen�Ѹ���
			return false;
		}
	}

	// ���Ƴ�һ����Ϣ
	if(m_nInbufStart + packsize > INBUFSIZE) {
		// ���һ����Ϣ�лؾ�����������ڻ��λ�������ͷβ��
		// �ȿ������λ�����ĩβ������
		int copylen = INBUFSIZE - m_nInbufStart;
		memcpy(pBuf, m_bufInput + m_nInbufStart, copylen);

		// �ٿ������λ�����ͷ����ʣ�ಿ��
		memcpy((unsigned char *)pBuf + copylen, m_bufInput, packsize - copylen);
		nSize = packsize;
	} else {
		// ��Ϣû�лؾ�����һ�ο�����ȥ
		memcpy(pBuf, m_bufInput + m_nInbufStart, packsize);
		nSize = packsize;
	}

	//��������
	m_dwRecvPacketCount++;
	//��������
	unsigned short wRealySize = CrevasseBuffer((unsigned char*)pBuf, packsize);
	nSize = wRealySize;
	//��������
	unsigned short wDataSize = wRealySize - sizeof(TCP_Head);
	void * pDataBuffer = (unsigned char*)pBuf + sizeof(TCP_Head);
	TCP_Command Command = ((TCP_Head *)pBuf)->CommandInfo;
	//�ں�����
	if (Command.wMainCmdID == MDM_KN_COMMAND)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_KN_DETECT_SOCKET:	//������
		{
			//��������
			SendMsg(MDM_KN_COMMAND, SUB_KN_DETECT_SOCKET, pDataBuffer, wDataSize);
			break;
		}
		}
	}

	// �������ݰ�����ʱ��
	m_dwPreRecvTick = SessionManager::shareInstance()->getTimeStamp();
	// ���¼��㻷�λ�����ͷ��λ��
	m_nInbufStart = (m_nInbufStart + packsize) % INBUFSIZE;
	m_nInbufLen -= packsize;
	return	true;
}

bool CGameSocket::hasError()
{
#ifdef WIN32
	int err = WSAGetLastError();
	if(err != WSAEWOULDBLOCK) {
#else
	int err = errno;
	if(err != EINPROGRESS && err != EAGAIN) {
#endif
		return true;
	}

	return false;
}

// �������ж�ȡ�����ܶ�����ݣ�ʵ����������������ݵĵط�
bool CGameSocket::recvFromSock(void)
{
	if (m_nInbufLen >= INBUFSIZE || m_sockClient == INVALID_SOCKET) {
		return false;
	}

	// ���յ�һ������
	int	savelen, savepos;			// ����Ҫ����ĳ��Ⱥ�λ��
	if(m_nInbufStart + m_nInbufLen < INBUFSIZE)	{	// INBUF�е�ʣ��ռ��л���
		savelen = INBUFSIZE - (m_nInbufStart + m_nInbufLen);		// �󲿿ռ䳤�ȣ����������ݵĳ���
	} else {
		savelen = INBUFSIZE - m_nInbufLen;
	}

	// ���������ݵ�ĩβ
	savepos = (m_nInbufStart + m_nInbufLen) % INBUFSIZE;
	CHECKF(savepos + savelen <= INBUFSIZE);
	int inlen = recv(m_sockClient, m_bufInput + savepos, savelen, 0);
	if(inlen > 0) {
		// �н��յ�����
		m_nInbufLen += inlen;
		
		if (m_nInbufLen > INBUFSIZE) {
			return false;
		}

		// ���յڶ�������(һ�ν���û����ɣ����յڶ�������)
		if(inlen == savelen && m_nInbufLen < INBUFSIZE) {
			int savelen = INBUFSIZE - m_nInbufLen;
			int savepos = (m_nInbufStart + m_nInbufLen) % INBUFSIZE;
			CHECKF(savepos + savelen <= INBUFSIZE);
			inlen = recv(m_sockClient, m_bufInput + savepos, savelen, 0);
			if(inlen > 0) {
				m_nInbufLen += inlen;
				if (m_nInbufLen > INBUFSIZE) {
					return false;
				}	
			} else if(inlen == 0) {
				Destroy();
				return false;
			} else {
				// �����ѶϿ����ߴ��󣨰���������
				if (hasError()) {
					Destroy();
					return false;
				}
			}
		}
	} else if(inlen == 0) {
		Destroy();
		return false;
	} else {
		// �����ѶϿ����ߴ��󣨰���������
		if (hasError()) {
			Destroy();
			return false;
		}
	}

	return true;
}

bool CGameSocket::Flush(void)		//? ��� OUTBUF > SENDBUF ����Ҫ���SEND����
{
	if (m_sockClient == INVALID_SOCKET) {
		log("Flush false == INVALID_SOCKET");
		return false;
	}

	if(m_nOutbufLen <= 0) {
		log("Flush false == m_nOutbufLen <= 0");
		return true;
	}
	
	// ����һ������
	int	outsize;
	outsize = send(m_sockClient, m_bufOutput, m_nOutbufLen, 0);
	if(outsize > 0) {
		// ɾ���ѷ��͵Ĳ���
		if(m_nOutbufLen - outsize > 0) {
			memcpy(m_bufOutput, m_bufOutput + outsize, m_nOutbufLen - outsize);
		}

		m_nOutbufLen -= outsize;

		if (m_nOutbufLen < 0) {
			log("Flush false == m_nOutbufLen < 0");
			return false;
		}
	} else {
		if (hasError()) {
			log("Flush false == hasError()");
			Destroy();
			return false;
		}
	}

	return true;
}

bool CGameSocket::Check(void)
{
	// ���״̬
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	char buf[1];
	int	ret = recv(m_sockClient, buf, 1, MSG_PEEK);
	if(ret == 0) {
		Destroy();
		return false;
	} else if(ret < 0) {
		if (hasError()) {
			Destroy();
			return false;
		} else {	// ����
			// ��ʱ�ж�
			if (SessionManager::shareInstance()->getTimeStamp()-m_dwPreRecvTick > m_nMaxKeepAliveTime)
			{
				Destroy();
				return false;
			}
			return true;
		}
	} else {	// ������
		return true;
	}
	
	return true;
}

void CGameSocket::Destroy(void)
{
	// �ȴ������߳��˳�
	m_bRunConnectThread = false;
	while (m_eSocketStatus == eSocketConnecting)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	// �ر�
	struct linger so_linger;
	so_linger.l_onoff = 1;
	so_linger.l_linger = 0;
	int ret = setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

    closeSocket();

	m_sockClient = INVALID_SOCKET;
	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;

	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));

	m_eSocketStatus = eSoccketUnknown;
}

//��������
unsigned short CGameSocket::EncryptBuffer(unsigned char pcbDataBuffer[], unsigned short wDataSize, unsigned short wBufferSize)
{
	//Ч�����
	CHECKF(wDataSize >= sizeof(TCP_Head));
	CHECKF(wBufferSize >= (wDataSize + 2 * sizeof(unsigned int)));
	CHECKF(wDataSize <= (sizeof(TCP_Head)+SOCKET_TCP_PACKET));

	//��������
	unsigned short wEncryptSize = wDataSize - sizeof(TCP_Command), wSnapCount = 0;
	if ((wEncryptSize%sizeof(unsigned int)) != 0)
	{
		wSnapCount = sizeof(unsigned int)-wEncryptSize%sizeof(unsigned int);
		memset(pcbDataBuffer + sizeof(TCP_Info)+wEncryptSize, 0, wSnapCount);
	}

	//Ч�������ֽ�ӳ��
	BYTE cbCheckCode = 0;
	for (unsigned short i = sizeof(TCP_Info); i < wDataSize; i++)
	{
		cbCheckCode += pcbDataBuffer[i];
		pcbDataBuffer[i] = MapSendByte(pcbDataBuffer[i]);
	}

	//��д��Ϣͷ
	TCP_Head * pHead = (TCP_Head *)pcbDataBuffer;
	pHead->TCPInfo.cbCheckCode = ~cbCheckCode + 1;
	pHead->TCPInfo.wPacketSize = wDataSize;
	//	pHead->CmdInfo.cbVersion=SOCKET_VER;  lhm delete

	//������Կ
	unsigned int dwXorKey = m_dwSendXorKey;
	if (m_dwSendPacketCount == 0)
	{
		//���ɵ�һ���������
		GUID Guid;
		Guid.Data1 = abs(rand() % 10000);
		Guid.Data2 = abs(rand() % 100);
		Guid.Data3 = abs(rand() % 100);
		for (int i = 0; i < 8; i++) {
			Guid.Data4[i] = 's';
		}

		//CoCreateGuid(&Guid);
		//dwXorKey = GetTickCount()*GetTickCount();
		dwXorKey = 0;
		dwXorKey ^= Guid.Data1;
		dwXorKey ^= Guid.Data2;
		dwXorKey ^= Guid.Data3;
		dwXorKey ^= *((unsigned int *)Guid.Data4);

		//���ӳ������
		dwXorKey = SeedRandMap((unsigned short)dwXorKey);
		dwXorKey |= ((unsigned int)SeedRandMap((unsigned short)(dwXorKey >> 16))) << 16;
		dwXorKey ^= g_dwPacketKey;
		m_dwSendXorKey = dwXorKey;
		m_dwRecvXorKey = dwXorKey;
	}

	//��������
	unsigned short * pwSeed = (unsigned short *)(pcbDataBuffer + sizeof(TCP_Info));
	unsigned int * pdwXor = (unsigned int *)(pcbDataBuffer + sizeof(TCP_Info));
	unsigned short wEncrypCount = (wEncryptSize + wSnapCount) / sizeof(unsigned int);
	for (int i = 0; i < wEncrypCount; i++)
	{
		*pdwXor++ ^= dwXorKey;
		dwXorKey = SeedRandMap(*pwSeed++);
		dwXorKey |= ((unsigned int)SeedRandMap(*pwSeed++)) << 16;
		dwXorKey ^= g_dwPacketKey;
	}

	//������Կ
	if (m_dwSendPacketCount == 0)
	{
		//MoveMemory(pcbDataBuffer + sizeof(TCP_Head)+sizeof(unsigned int), pcbDataBuffer + sizeof(TCP_Head), wDataSize);
		memmove(pcbDataBuffer + sizeof(TCP_Head)+sizeof(unsigned int), pcbDataBuffer + sizeof(TCP_Head), wDataSize);
		*((unsigned int *)(pcbDataBuffer + sizeof(TCP_Head))) = m_dwSendXorKey;
		pHead->TCPInfo.wPacketSize += sizeof(unsigned int);
		wDataSize += sizeof(unsigned int);
	}

	//���ñ���
	m_dwSendPacketCount++;
	m_dwSendXorKey = dwXorKey;
	return wDataSize;
}

//��������
unsigned short CGameSocket::CrevasseBuffer(unsigned char pcbDataBuffer[], unsigned short wDataSize)
{
	//Ч�����
	CHECKF(m_dwSendPacketCount > 0);
	CHECKF(wDataSize >= sizeof(TCP_Head));
	CHECKF(((TCP_Head *)pcbDataBuffer)->TCPInfo.wPacketSize == wDataSize);

	//��������
	unsigned short wSnapCount = 0;
	if ((wDataSize%sizeof(unsigned int)) != 0)
	{
		wSnapCount = sizeof(unsigned int)-wDataSize%sizeof(unsigned int);
		memset(pcbDataBuffer + wDataSize, 0, wSnapCount);
	}

	//��������
	unsigned int dwXorKey = m_dwRecvXorKey;
	unsigned int * pdwXor = (unsigned int *)(pcbDataBuffer + sizeof(TCP_Info));
	unsigned short  * pwSeed = (unsigned short *)(pcbDataBuffer + sizeof(TCP_Info));
	unsigned short wEncrypCount = (wDataSize + wSnapCount - sizeof(TCP_Info)) / 4;
	for (unsigned short i = 0; i<wEncrypCount; i++)
	{
		if ((i == (wEncrypCount - 1)) && (wSnapCount>0))
		{
			BYTE * pcbKey = ((BYTE *)&m_dwRecvXorKey) + sizeof(unsigned int)-wSnapCount;
			CopyMemory(pcbDataBuffer + wDataSize, pcbKey, wSnapCount);
		}
		dwXorKey = SeedRandMap(*pwSeed++);
		dwXorKey |= ((unsigned int)SeedRandMap(*pwSeed++)) << 16;
		dwXorKey ^= g_dwPacketKey;
		*pdwXor++ ^= m_dwRecvXorKey;
		m_dwRecvXorKey = dwXorKey;
	}

	//Ч�������ֽ�ӳ��
	TCP_Head * pHead = (TCP_Head *)pcbDataBuffer;
	BYTE cbCheckCode = pHead->TCPInfo.cbCheckCode;
	for (int i = sizeof(TCP_Info); i < wDataSize; i++)
	{
		pcbDataBuffer[i] = MapRecvByte(pcbDataBuffer[i]);
		cbCheckCode += pcbDataBuffer[i];
	}
	//if (cbCheckCode != 0) throw TEXT("���ݰ�Ч�������");//ע���Ȳ�������
	if (cbCheckCode != 0)
	{
		//CCLog("���ݰ�Ч�������");
	}

	return wDataSize;
}
//���ӳ��
unsigned short CGameSocket::SeedRandMap(unsigned short wSeed)
{
	unsigned int dwHold = wSeed;
	return (unsigned short)((dwHold = dwHold * 241103L + 2533101L) >> 16);
}

//ӳ�䷢������
BYTE CGameSocket::MapSendByte(BYTE const cbData)
{
	BYTE cbMap = g_SendByteMap[(BYTE)(cbData + m_cbSendRound)];
	m_cbSendRound += 3;
	return cbMap;
}

//ӳ���������
BYTE CGameSocket::MapRecvByte(BYTE const cbData)
{
	BYTE cbMap = g_RecvByteMap[cbData] - m_cbRecvRound;
	m_cbRecvRound += 3;
	return cbMap;
}

bool CGameSocket::Connect(const char* ip, unsigned short port, int nBlockSec/* = BLOCKSECONDS*/, bool bKeepAlive/* = false*/)
{
	if (m_eSocketStatus == eSocketConnecting)
	{
		return false;
	}
	else if (m_eSocketStatus == eSocketConnected)
	{
		Destroy();
	}

#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if (ret != 0) {
		return false;
	}
#endif
	// �������׽���
	m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	unsigned long serveraddr = inet_addr(ip);
	if (serveraddr == INADDR_NONE)	// ���IP��ַ��ʽ����
	{
		m_eSocketStatus = eSocketConnectFailed;
		return false;
	}

	memset((void *)&m_sockaddr, 0, sizeof(m_sockaddr));
	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_port = htons(port);
	m_sockaddr.sin_addr.s_addr = serveraddr;

	m_eSocketStatus = eSocketConnecting;
	m_nBlockSec = nBlockSec;
	m_bKeepAlive = bKeepAlive;

	m_bRunConnectThread = true;
	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;
	m_cbSendRound = 0;
	m_cbRecvRound = 0;
	m_dwSendXorKey = 0;
	m_dwRecvXorKey = 0;

	m_dwSendTickCount = 0;
	m_dwRecvTickCount = 0;
	m_dwSendPacketCount = 0;
	m_dwRecvPacketCount = 0;
	// ���������߳�
	std::thread connectThread(&CGameSocket::ConnectThread, this);
	connectThread.detach();

	return true;
}

void CGameSocket::ConnectThread()
{
	if (m_eSocketStatus == eSocketConnecting)
	{
		// ����SOCKETΪKEEPALIVE
		if (m_bKeepAlive)
		{
			int		optval = 1;
			if (setsockopt(m_sockClient, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)))
			{
				goto ErrorSocket;
			}
		}

#ifdef WIN32
		DWORD nMode = 1;
		int nRes = ioctlsocket(m_sockClient, FIONBIO, &nMode);
		if (nRes == SOCKET_ERROR) {
			goto ErrorSocket;
		}
#else
		// ����Ϊ��������ʽ
		fcntl(m_sockClient, F_SETFL, O_NONBLOCK);
#endif

		if (connect(m_sockClient, (sockaddr *)&m_sockaddr, sizeof(m_sockaddr)) == SOCKET_ERROR) {
			if (hasError()) {
				goto ErrorSocket;
			}
			else	// WSAWOLDBLOCK
			{
				bool bSucc = false;
				for (int i = 0; (i < MAX(m_nBlockSec, 1)&&m_bRunConnectThread); ++i)
				{
					timeval timeout;
					timeout.tv_sec = 1/*m_nBlockSec*/;
					timeout.tv_usec = 0;
					fd_set writeset, exceptset;
					FD_ZERO(&writeset);
					FD_ZERO(&exceptset);
					FD_SET(m_sockClient, &writeset);
					FD_SET(m_sockClient, &exceptset);

					int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
					if (ret > 0)
					{
						ret = FD_ISSET(m_sockClient, &exceptset);
						if (ret)		// or (!FD_ISSET(m_sockClient, &writeset)
						{
							continue;
						}
						else
						{
							bSucc = true;
							break;
						}
					}
				}

				if (!bSucc)
				{
					goto ErrorSocket;
				}
			}
		}

		struct linger so_linger;
		so_linger.l_onoff = 1;
		so_linger.l_linger = 500;
		setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

		m_eSocketStatus = eSocketConnected;
		m_dwPreRecvTick =SessionManager::shareInstance()->getTimeStamp();
		if (m_pGameSocketSink != nullptr)
		{
			m_pGameSocketSink->OnEventTCPSocketLink(true);
		}
		return;
	}

ErrorSocket:
	closeSocket();
	m_eSocketStatus = eSocketConnectFailed;
	if (m_pGameSocketSink != nullptr)
	{
		m_pGameSocketSink->OnEventTCPSocketLink(false);
	}
}

bool CGameSocket::IsConnected()
{
	return (m_eSocketStatus == eSocketConnected);
}
