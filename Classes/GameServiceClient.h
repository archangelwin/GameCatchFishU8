/**
 * @file GameServiceClient
 * @brief ������Ϸ�Ŀͻ��˷�װ
 * @author tjl
 * @date
 */

#ifndef __GAMESERVICECLIENT_H_
#define __GAMESERVICECLIENT_H_

#include "cocos2d.h"
//#include "core/TCPSocket.h"
#include "core/GameSocket.h"
#include "GolbalDefine/Macro.h"
#include "MsgDefine/CMD_UserManage.h"
#include "Model/MatchModel.h"
#include "Model/RoomLevelInfo.h"
#include "Message.h"
#include "Common/ShopManager.h"

#define MAX_TCP_LEN 1024*5
struct SendData
{
	char sSendData[MAX_TCP_LEN];
	DWORD dwDataLen;
};


#define VERSION_FRAME				16777217
#define VERSION_CLIENT				17170433
#define VERSION_PLAZA 				17235969

#define FRAME_SORKET_INDEX 1 //����SORKET ����
#define GAMEROOM_SORKET_INDEX 2//��ϷSORKET  ����
#define TASK_SORKET_INDEX     3 //����SORKET ����

#define MAX_HORN_MSG_COUNT 10
#define  taskClient "taskClient" 

USING_NS_CC;

//������Ϣkey
#define ERROR_MESSAGE_KEY       "ErrorMessage"

//������Ϣ����
#define PublicMessageCommand    "PublicMessage"

//��������ʧ����
#define ConnectionLostMessage   "ConnectionLostMessage"

//smartfox��ʼ�Զ�retry
#define ConnectionStartRetryMessage "ConnectionStartRetryMessage"

//����ָ���
#define ConnectionResumeMessage "ConnectionResumeMessage"

//������Ϣ
//���뷿��ɹ�, ����������������
#define JoinRoomSucceedMessage         "JoinRoomSucceedMessage"
//���뷿��ʧ��
#define JoinRoomFailedMessage         "JoinRoomFailedMessage"

//ר�Ÿ������б��õļ��뷿����Ϣ��ֻ�м���lobby����ķ���ʱ���Żᴥ���������ĵط���Ҫ�ã�������������
#define JoinGameRoomMessage "JoinGameRoomMessage"

//�����û����뷿��
#define UserEnterRoomMessage         "UserEnterRoomMessage"

//�����û��˳�����, ����������������
#define UserExitRoomMessage         "UserExitRoomMessage"

//�������, ����������������
#define UpdateRoomMessage       "UpdateRoomMessage"

//�û���Ϣ������Ϣ
#define UpdateUserInfoVariableMessage   "UpdateUserInfoVariableMessage"

//�����ɫת��
#define PlayerToSpectatorMessage        "PlayerToSpectatorMessage"
#define PlayerToSpectatorErrorMessage   "PlayerToSpectatorErrorMessage"
#define SpectatorToPlayerMessage        "SpectatorToPlayerMessage"
#define SpectatorToPlayerErrorMessage   "SpectatorToPlayerErrorMessage"

//�յ����������͹�������������Ϣ, ���п���Ϸ��ת
#define ModeratorUpdateMessage          "ModeratorUpdateMessage"

//��Ϸ��¼�ɹ�
#define LoginGameSucceedMessage "LoginGameSucceedMessage"

//���յ���Ϸ��¼�ɹ�����Ϣ
#define ReceiveLoginGameSucceedMessage "ReceiveLoginGameSucceedMessage"

//��Ϸ��¼ʧ��
#define LoginGameFailedMessage "LoginGameFailedMessage"

//�ǳ���Ϸ
#define LogoutGameMessage "LogoutGameMessage"

//����ϲ����Ϣ
#define BadNetworkingMessage "BadNetworkingMessage"

//����ָ�
#define NetworkingTurnGoodMessage "NetworkingTurnGoodMessage"

/************************************************************************/
/* GameServiceClient Class                                              */
/************************************************************************/
// һ����Ϸ��Ӧ��ôһ���ͻ���
// �����ȡ���ã���������¼��Ϸ�����뷿��

class GameServiceClient : public Ref,public IGameSocketSink {
public:
    static GameServiceClient *create(int sorketIndex);
    bool init(int sorketIndex);
    GameServiceClient();
    virtual ~GameServiceClient();

	// �����¼�
	virtual bool OnEventTCPSocketLink(bool bConnectSucc);
	//�ر��¼�
	virtual bool OnEventTCPSocketShut(unsigned char cbShutReason);

    void update(float dt);
    void cleanup();
	//virtual bool initSocket(int index);
	bool Connect(const char* ip, unsigned short port);
    //����, ��������ΪNULLʱ, ���ӵ�С��, ��ΪNULLʱ, ���ӵ�ָ������
    CC_SYNTHESIZE(bool, m_isRetrying, IsRetrying);

    //��Ϸ����
    CC_SYNTHESIZE(std::string, m_gameZone, GameZone);

    //��ǰ����
    CC_SYNTHESIZE(std::string, m_roomName, RoomName);

	//defautl is yes. ���scene�˳�������client��Ҫ���棬�Ͱ�����������ó�false
	CC_SYNTHESIZE(bool, m_needPassToResponseHandler, NeedPassToResponseHandler);
public:
	//��¼����
	void onLogin(const char* accout,const char* pwd);
	//U8��¼
	void onLoginU8(const char* umid, const char* username, const char* token, const char* userid);
	//΢�ŵ�¼
	void onWxLogin(const char* token);
	//��¼��������
	void loginRealRoom(RoomLevelInfo* info);
	//��¼��������
	void loginMatchRoom();
	//���ͻ�ȡ��Ϸ����
	void sendGetGameConfig();
	//
	void sendGetGameMatchConfig();
	//�ǳ�
	void logout();
	//ע��
	void onRegister(char* account,char* nick,char* pwd);
	//����
	void retry();

	void registerHandler();
	//���Ϳ�����Ϣ
	void sendUserFire(float angle,int bullet_mulriple);
	//�����Ϸ���Ϣ
	void exchangeScore(int score);
	//����ͬ��ʱ����Ϣ
	void SendTimerSync();
	//����������Ϣ
	void sendStandUp();
	//���ͻ�ȡ���/�׾�����
	void  SendRequestShop(int type);
	void  sendBuyGiftRequest(int proType, int proNum,int proId);//���� �һ�����
	void  sendUserKnapsackRequset(int id,int num,const char* szNote = "");//ʹ�ñ���
	//�����������������
	void  SendAuctionRequset(int subCmd,int pageIndex,int pageCount,WORD userId = 0,int lastday = 12);
	//��ȡ�ϼ���Ʒ
	void SendAuctionListRequset();
	//�����ϼ���Ʒ����
	void sendSellAuctionRequest(__Dictionary*info);
	//���͹�����Ʒ����
	void sendBuyAuctionRequest(__Dictionary*info);
	//���ͳ�����������
	void sendCancelAuctionRequest(__Dictionary* info);
	//��ѯ����
	void sendQueryAuctionRequest(int pageIndex,int pageCount,char* text,int lastday = 12);
	//��ȡ�Ƹ���ϸ����
	void sendTreasureRequest();
	//��ȡ������������
	void sendConvertAutionScoreRequest();
	//��������һ�����
	void sendGiftConvertRequest(const char* covertCode);
	//bag ���
	void sendKnapSackRequest();
	//vippower ���
	void sendVipPowerRequest();
	//������ȡVIP ��۽����
	void sendVipAwardRequest(int awardType);
	//��¼���������
	void loginTaskServer();
	//���ͻ�ȡ�����б�����
	void sendGetTaskList();
	//������ȡ����������
	void sendTaskAwardRequest(int taskId);
	//����������
	void sendRefrshMatchPlayers();
	//��������
	void sendSignUpRequest(MatchInfoModel* info);
	//ȡ������
	void sendUnSignUpRequest(MatchInfoModel* info);
	//��ȡ������ʼʱ��
	void sendCountDownRequest(MatchInfoModel* info);
	//���ͱ���������Ϣ
	void sendMatchUserComeRequest();
	//�뿪����
	void sendLeaveMatchRequest();
	//�ٴ���ս
	void sendTryAaginRequest();

	void closeSoket();

	//��ȡ������Ϣ
	void sendQueryBankRequest();
	//������
	void sendUserSaveScoreRequest(SCORE score);
	//��ȡ���
	void sendUserTakeScoreRequest(SCORE score);
	//�޸���������
	void sendModifyInsurePass(const char* pwd);
	//������������
	void sendVerifyInsurePass(const char* pwd);
	//�޸ĵ�¼����/��������
	void sendModifyPassword(const char* oldPwd,const char *newPwd ,int type); //type = 0 ��ʾ�޸ĵ�¼���룬1��ʾ�޸���������
	//���ͻ�ȡǩ���б�
	void sendGetAssignList();
	//����ǩ����Ϣ
	void sendAssignMsg();

	//���ֻ����
	//���ͻ�ȡ��֤������
	void sendGetVerifyCode(const char* phone);
	//���Ͱ��ֻ�����
	void sendBindPhoneRequest( int code );

	//�һص�¼�������
	void sendEnsureAccoutRequest(const char* accout);
	void sendGetVerifyCodeByUid();
	void sendSetPassRequest(int verifyCode ,const char* newPwd);
	//�һ����������
	void sendInsureVerifyRequest();
	void sendSetInsuerPass(int verifyCode,const char* newInsurePwd);
	//Ԫ���һ�
	void sendExchangeIngotRequest(int ingot);
	//�޸��Ա�
	void sendModifyIndividual(bool isMan = false);//0ΪŮ��1Ϊ��
	//�޸�ͷ��
	void sendModifyFaceId(int id);
	//���ͷ�����Ϣ
	void sendFeedBackRequest(const char* content,const char* pQQ);
	//���͸�����Ϸ
	void sendMoreGameRequest();
	//���ͻ�ȡ������Դ�����Ϣ
	void sendDownLoadUrlRequest(int gameKind);
	//�Ƿ�����
	bool isConnect() { return m_GameSocket.IsConnected();}

	//���Ϳ��ٵ�¼
	void sendQucikLogin(const char* uuid);
	//��ֵ�¶���
	void sendRechargeOrder(int ingot,const char* orderInfo, bool isFirstRecharge = false);
	//������¼��������
	void parseLoginExpandData(void * pDataBuffer, unsigned short wDataSize);
	//������������
	void sendhornRequset(const char* content);
	//����ת������
	void sendLuckSpinRequest();
protected:
	bool OnTCPSocketRead(WORD wSocketID, TCP_Command Command, VOID * pData, WORD wDataSize);
	bool OnTCPNetworkMainMBLogon(WORD wSubCmdID, VOID * pData, WORD wDataSize, DWORD dwSocketID);
	bool OnTCPNetworkMainMBCount(WORD wSubCmdID, VOID * pData, WORD wDataSize, DWORD dwSocketID);

	void parseGift(void* pData,WORD wDataSize,ShopItemType type);
	std::list<SendData> m_RecvData; 
	__Array* m_responseHandlers;
	BYTE mGameStatus;//��Ϸ״̬
	bool m_isLookOn; //�Ƿ��Թ�
	bool m_isLogin;
	std::mutex    m_mutex;
	CGameSocket   m_GameSocket;
	int           m_clientType;
	bool          m_bConnectFail;

};

#endif //__GAMESERVICECLIENT_H_
