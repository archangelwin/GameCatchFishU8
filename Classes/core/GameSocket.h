
#pragma once
#if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define NTAPI __stdcall
#else
#define _cdecl
#define __cdecl
#define NTAPI
#endif

#include "GameGlobalSetting.h"
#include "cocos2d.h"

#include "Packet.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#define RtlCopyMemory(Destination,Source,Length) memcpy((Destination),(Source),(Length))
#define CopyMemory RtlCopyMemory
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
//typedef char TCHAR, *PTCHAR;
#endif

#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#else
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#endif

#ifndef CHECKF
#define CHECKF(x) \
	do \
{ \
	if (!(x)) { \
	printf("CHECKF:%s %s", __FILE__, __LINE__); \
	return 0; \
	} \
} while (0)
#endif

#define _MAX_MSGSIZE 16 * 1024		// �ݶ�һ����Ϣ���Ϊ16k
#define BLOCKSECONDS	30			// INIT��������ʱ��
#define INBUFSIZE	(64*1024)		//?	����ߴ�������汨�����  �������ݵĻ���
#define OUTBUFSIZE	(SOCKET_TCP_PACKET)		//? ����ߴ�������汨������� �������ݵĻ��棬��������8Kʱ��FLUSHֻ��ҪSENDһ��

enum eSocketStatus
{
	eSoccketUnknown = 0,
	eSocketConnecting = 1,
	eSocketConnected = 2,
	eSocketConnectFailed = 3,
};

//����ӿ�
struct IGameSocketSink
{
	//�����¼�
public:
	// �����¼�
	virtual bool OnEventTCPSocketLink(bool bConnectSucc) = 0;
	//�ر��¼�
	virtual bool OnEventTCPSocketShut(unsigned char cbShutReason) = 0;
};

class CGameSocket {
public:
	CGameSocket(void);
	~CGameSocket();
	bool	Connect(const char* ip, unsigned short por, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
	bool	SendMsg(unsigned short wMainCmdID, unsigned short wSubCmdID, void* pBuf, int nSize);
	bool	ReceiveMsg(void* pBuf, int& nSize);
	bool	Flush(void);
	bool	Check(void);
	void	Destroy(void);
	SOCKET	GetSocket(void) const { return m_sockClient; }
	bool	IsConnected();
	void	SetGameSocketSink(IGameSocketSink* pSocketSink){ m_pGameSocketSink = pSocketSink; }
	void	SetMaxKeepAliveTime(unsigned int nMaxTime){ m_nMaxKeepAliveTime = nMaxTime; }
	//���ܺ���
protected:
	//��������
	unsigned short CrevasseBuffer(unsigned char cbDataBuffer[], unsigned short wDataSize);
	//��������
	unsigned short EncryptBuffer(unsigned char cbDataBuffer[], unsigned short wDataSize, unsigned short wBufferSize);

	//�ֽ�ӳ��
	inline unsigned short SeedRandMap(unsigned short wSeed);
	//����ӳ��
	inline unsigned char MapSendByte(unsigned char cbData);
	//����ӳ��
	inline unsigned char MapRecvByte(unsigned char cbData);
	
private:
	bool	recvFromSock(void);		// �������ж�ȡ�����ܶ������
	bool    hasError();			// �Ƿ�������ע�⣬�첽ģʽδ��ɷǴ���
	void    closeSocket();
	void	ConnectThread();
	bool	Create(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);

	//��������
protected:
	unsigned char							m_cbSendRound;						//�ֽ�ӳ��
	unsigned char							m_cbRecvRound;						//�ֽ�ӳ��
	unsigned int							m_dwSendXorKey;						//������Կ
	unsigned int							m_dwRecvXorKey;						//������Կ

	unsigned int							m_dwSendTickCount;					//����ʱ��
	unsigned int							m_dwRecvTickCount;					//����ʱ��
	unsigned int							m_dwSendPacketCount;				//���ͼ���
	unsigned int							m_dwRecvPacketCount;				//���ܼ���
	// ������Ϣ
	sockaddr_in								m_sockaddr;
	int										m_nBlockSec;						// ���ӳ�ʱʱ��
	bool									m_bKeepAlive;						// socket KeepAlive
	bool									m_bRunConnectThread;				// 
	eSocketStatus							m_eSocketStatus;					// socket ״̬

	SOCKET	m_sockClient;
	IGameSocketSink* m_pGameSocketSink;	// ���Ӽ����ص�

	// �������ݻ���
	char	m_bufOutput[SOCKET_TCP_BUFFER];	//? ���Ż�Ϊָ������
	int		m_nOutbufLen;

	// ���λ�����
	char	m_bufInput[INBUFSIZE];
	int		m_nInbufLen;
	int		m_nInbufStart;				// INBUFʹ��ѭ��ʽ���У��ñ���Ϊ������㣬0 - (SIZE-1)

	unsigned int							m_dwPreRecvTick;					// ���հ�ʱ���
	unsigned int							m_nMaxKeepAliveTime;				// �ж��Ƿ���߱�ʶ
};
