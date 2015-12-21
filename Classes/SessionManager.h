#ifndef _SessionManager_H_H_
#define _SessionManager_H_H_

#include "cocos2d.h"
#include "Model/RoomLevelInfo.h"
#include "Model/UserModel.h"
#include <iostream>
#include <time.h>
#include "Model/LoginUserModel.h"
#include "Model/OnlineUserModel.h"
#include "Model/MatchModel.h"

#define GameKindDntg    260
#define GameKindLkpy    290
#define GameKindJcpy    250

#define RoomLevel_0     511
#define RoomLevel_1     512
#define RoomLevel_2     513

#define  FULLPLAYERMATCH    4
#define  BUYUFOREVERMATCH 6
#define  BUYUTIMEMATCH       7 
#define  BUYUBIGAWARDMATCH 8

#define GAME_IP						"login1.qicainiu.net"						//��ʽ������

class SessionManager : public Ref
{
public:
	SessionManager();
	~SessionManager();
	static SessionManager* shareInstance();
	virtual void purgeInstance();
	bool init();

	void setAllRoomLevels(__Array* pArr);
	__Array* getAllRoomLevels();
	RoomLevelInfo* getLevelInfoByRoomID(int id);
	RoomLevelInfo* getLevelInfoByRoomLevel(int gameKind,int roomLevel);
	void setUserId(int id);
	int  getUserId();

	void  setPwd(char* pwd);
	std::string getPwd();

	void setChairId(int id){mChairId = id;}
	int  getChairId(){return mChairId;}

	//��ȡʱ������ӹ�Ԫ1970 ��1��1��0ʱ0��0�����������UTCʱ����������������
	static time_t getTimeStamp();
	//��ǰ����
	static std::string getDateTime();
	//��ȡ����ʱ��
	static std::string  getMatchTime();
	//��ȡ��ǰʱ����뼶
	long getCurrentTime();
	__Array* getAllUsers() {return mAllUsers;}
	UserModel* getUserById(int usrId);

	LoginUserModel* getLoginModel() {return m_userLoginModel;}
	OnlineUserModel* getUser() {return m_user;}
	void flush();
	void restoreUserData();
	void increaseGameLaunchCount();

	// �������ֿ���
	bool getMusicOn() const;
	void setMusicOn(bool on);

	// ��Ч���� , 1:���� 0:�ر�
	bool getEffectOn() const;
	void setEffectOn(bool on);

	//���ö�Ӧ���������
	void setResponseData(Ref *data, const char* key);
	Ref* getResponseDataForKey(const char* key);

	//������л�������
	void clearAllResponseCache();
	//���浱ǰ�������������ɼ�
	void setTaskCnt(int cnt) {m_taskCnt = cnt;}
	int  getTaskCnt() const {return m_taskCnt;}
	//�������������IP �Ͷ˿�
	void setTaskServer(char* ip) {m_taskServerAddr = ip;}
	void setTaskPort(int port){m_taskPort = port;}
	std::string getTaskServer() const {return m_taskServerAddr;}
	int getTaskPort() const {return m_taskPort;}

	bool isResetBankPwd() const { return mBankPwdFlag;}//�Ƿ�������������
	void setBankPwdFlag(bool flag) {mBankPwdFlag = flag;}

	__Array* getMsgArray() {return mMsgArray;}
	void clearMsgArray() {mMsgArray->removeAllObjects();}

	void setInsurePass(std::string insurePwd);
	std::string getInsurePass();
	bool isInPlayers(UserModel* model );
	void addPlayer(UserModel*model);
	__Array* getGamePlayers() const {return mGamePlayers;}
	void clearGamePlayers();
	bool isInGame() const {return mInGame;}//��������Ϸ��ı�־
	void setInGame(bool flag) { mInGame = flag;} 
	void setGameKind(int value);
	int getGameKind() const {return mGameKindIndex;}


	//��¼�ʺ��б�
	void readAccountFile();
	void writeAccountFile();
	__Array* getAccountList() {return mAccountArray;}
	bool isNotLogin(std::string accountInfo);
	int getIndexByAccount(std::string account);

	//vippower���
	void setLoginScoreStatus(int status) {mLoginScoreStatus = status;}//ÿ�յ�¼
	int  getLoginScoreStatus() const {return mLoginScoreStatus;}

	void setRedStatus(int status) {mRedStatus = status;}//ÿ�շ���
	int  getRedStatus() const {return mRedStatus;}

	long getLastBombTick() const {return mLastDealBombTick;}
	void setBombTick(long tick) {mLastDealBombTick = tick;}

	//�����ʺ�ǩ����Ϣ
	void readAssignInfo();
	void saveAssignInfo();
	bool isShowAssign();

	//�����ʺ��Ѷ���Ϣ
	void loadReadMsgInfo();
	void SaveReadMsgInfo();
	bool hasRead(int msgId);
	//����������
	void setNewMsgTag(bool value) {mBNewMsg = value;}
	bool getNewMsgTag() {return mBNewMsg;}

	void setNewTaskTag(bool value) {mBNewTask = value;}
	bool getNewTaskTag()  {return mBNewTask;}

	//�µ������м�¼
	void setNewAuctionTag(bool value) {mBNewAuction = value;}
	bool getNewAuctionTag() const{return mBNewAuction;}

	//��Ϸ�����ʼ����ɱ��
	void setHasFinish(bool value ) {mGameInitFinish = value;}
	bool getHasFinish() const { return mGameInitFinish;}

	//��¼��ǰ����������
	void setMusicName(const char* name) {mCurBgMusicName = name;}
	std::string getMusicName() {return mCurBgMusicName;}

	//��������ID
	void setGameMatchKind(int id){ mMatchId = id;}
	int   getGameMatchKind() {  return mMatchId;}

	__Array* getMatchRooms() {return mMatchRooms;}
	void sortMatchRooms();
	bool         isInMatchRooms(int matchInfoID);
	MatchInfoModel* getMatchInfoByID(LONGLONG matchInfoID);
	bool     isHastheMatch(int matchType);
	void     removeMatchRoomByMatchInfoID(LONGLONG matchInfoID);
	int       getMatchRoomCountByType(int matchType);
	void    setMatchStatus(int status) {mMatchGameStatus = status;}
	int       getMatchStatus() {return mMatchGameStatus;}
	void     clearMatchRooms() {mMatchRooms->removeAllObjects();}
	MatchSerialModel* getRoomSerial() { return mMatchSerialModel;}

	void setMatchSever(const char* addr) {match_server = addr;}
	std::string getMatchSever() {return match_server;}

	void setMatchPort(int port) {match_port = port;}
	int getMatchPort() {return match_port;}

	void setMatchStart(int value) {bMatch_Start = value;}
	int    getMatchStart() {return bMatch_Start;}

	std::string getLoginAddr();
	void        setLoginAddrNull() { login_server = ""; }
	__Array*   getLoginUrls() { return mLoginUrls; }
	void       clearHornMsg();
	//������Ϣ
	std::list<std::string> listHornMsg;
private:
	__Array* mRoomLevels;//���з�����Ϣ�б�
	__Array* mAllUsers; //�����û��б�
	int mUserId;
	int mChairId;
	bool m_IsMusicOn;
	bool m_IsEffectOn;
	LoginUserModel* m_userLoginModel;
	OnlineUserModel* m_user;
	int m_gameLaunchCount;
	//���ݻ���
	std::shared_ptr<Map<std::string, Ref*> >    m_responseDataCache;
	std::string mPwd;
	int  m_taskCnt;
	std::string m_taskServerAddr;
	int  m_taskPort;
	bool mBankPwdFlag;
	__Array* mMsgArray;//��Ϣ����
	std::string mInsurePass;
	__Array* mGamePlayers;//�������������
	bool mInGame;
	int  mGameKindIndex;   //��Ϸ��������

	__Array* mAccountArray;

	int   mLoginScoreStatus;//��¼���� �Ƿ���ȡ   0:��Ч 1��δ��ȡ 2������ȡ
	int   mRedStatus;//����������Ƭ �Ƿ���ȡ 0:��Ч 1��δ��ȡ 2������ȡ

	long   mLastDealBombTick;

	std::map<std::string,std::string> mAssignMap;
	std::map<std::string,std::vector<int>> mMsgMap;
	bool mBNewMsg;//���µ���Ϣ
	bool mBNewTask;//���µ��������
	bool mBNewAuction;//���µ�������¼

	bool mGameInitFinish ;
	std::string mCurBgMusicName;
	int   mMatchId;

	//�������б�
	__Array* mMatchRooms;
	int    mMatchGameStatus;

	//��ǰ��������Ψ һ�� 
	MatchSerialModel* mMatchSerialModel;

	std::string match_server;
	int              match_port;
	bool            bMatch_Start;
	std::string login_server;
	__Array* mLoginUrls;

};




#endif //_SessionManager_H_H_