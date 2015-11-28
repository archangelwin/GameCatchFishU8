#ifndef _GAME_SCENE_H_H_
#define _GAME_SCENE_H_H_

#include "cocos2d.h"
#include "GameServiceClient.h"
#include "GameBaseScene.h"
#include "Message.h"
#include "GameFishManager.h"
#include "GameShooter.h"
#include "GamePlayerManager.h"
#include "GameScenefishManager.h"
#include "LoadingScene.h"
#include "Model/UserModel.h"
#include "Widgets/GameGuideWidget.h"
#include "Model/MatchModel.h"
#include "GameMatchManager.h"

#include "cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace ui;

struct MessageInfo {
	const char* msg[1024];
};

class GameScene :public GameBaseScene
{
public:
	GameScene();
	~GameScene();
	static GameScene* create(int level,int gameKind,bool isMatch = false);
	bool init(int level,int gameKind,bool isMatch);
	virtual void onEnter();
	virtual void onExit();
	virtual void render(Renderer* renderer);
	virtual void loadUI();

	virtual void okCallback();
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent); 
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent); 
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
	//��ʼ����ҽ���Ԫ��
	void initPlayer(GamePlayer* player);
	//�Ƴ���ҽ���Ԫ��
	void removePlayer(GamePlayer* player);
public:
	virtual __Array * getResourceNeedLoad();
	virtual void updateProgress(int resourceLeftToLoad);
	void addChain(GameAnimation* chain,WORD view_chair_id);
	void onChainpro(WORD view_chair_id,const CatchFish* fishArr,int cnt);
	void hideChainPro(WORD view_chair_id);
	void addScore(WORD view_chair_id,SCORE score,bool coin_effect,bool bingo_effect);
	Vec2 GetTurretPosition(WORD view_chair_id);
	void addCoin(Node* coinNode);
	GamePlayerManager* getPlayerManager() {return mPlayerManager;}
	GameMatchModel*  getGameMatchModel() {return mGameMatchInfo;}
private:
	void update(float dt);
	void receiveSubDistributeFish(EventCustom* event);//�յ��ַ������Ϣ����
	void receiveGameSceneMsg(EventCustom* event);//�յ��л�������Ϣ����
	void receiveGameStausMsg(EventCustom* event);//�յ���Ϸ״̬��Ϣ����
	void receiveUserEnterMsg(EventCustom* event);//�յ��û�������Ϣ����
	void receivePlayerToSeperaterMsg(EventCustom* event);//�յ�վ����Ϣ����
	void receiveUserFireMsgMsg(EventCustom* event);//�յ��û�������Ϣ����
	void receiveCatchFishMsg(EventCustom* event);//�յ���׽�����Ϣ����
	void receiveRemoveLoadingMsg(EventCustom* event);//�յ��Ƴ����ؽ�����Ϣ����
	void receiveExchangeScoreMsg(EventCustom* event);//��ҽ�ұ䶯������Ϣ����
	void receiveTimerSyncMsg(EventCustom* event);//ʱ��ͬ��������Ϣ����
	void receiveForceTimerSyncMsg(EventCustom* event);//ǿ��ʱ��ͬ����Ϣ���ش���
	void receiveSubSceneFishMsg(EventCustom* event);//���������������ָ���Ϣ���ش���
	void receiveBulletDoubleTimeoutMsg(EventCustom* event);//˫��ʱ�䵽����Ϣ����
	void receiveChangeSceneMsg(EventCustom* event);////�յ��л���������Ϣ����
	void receiveModifyLkMulriple(EventCustom* event);//�յ����Ӹı䱶������Ϣ����

	//chain ���
	void receiveCatchChainMsg(EventCustom* event); //����׽�����������Ϣ����
	void receiveFishArriveMsg(EventCustom* event); //���յ��㱻����ǣ����λ����Ϣ
	void receiveDealBingoEffectMsg(EventCustom* event); //���տ�ʼ��ʾBING Ч����Ϣ
	void receiveDealBgluEffectMsg(EventCustom* event);//���տ�ʼ��ʾ����¯Ч����Ϣ
	void receiveDealJettonEffectMsg(EventCustom* event);//���տ�ʼ���ų���Ч����Ϣ
	void receiveSystemMsg(EventCustom* event);//���ܵ�ϵͳ��Ϣ

	void receiveGameSorketCloseMsg(EventCustom* event);//����Ͽ�
	void receiveKeyEscapeMsg(EventCustom* evt);

	//�������
	void receiveUpdateMatchStatusMsg(EventCustom* evt);
	void receiveUpdateMatchInfoMsg(EventCustom* evt);
	//�յ�����������Ϣ����
	void receiveMatchAwardMsg(EventCustom* evt);
	//�ٴ���ս
	void toSendTryAgainMatch(EventCustom* evt);
	void showMatchTryAgainMsg(EventCustom* evt);
	void receiveMatchIsBeingStartMsg(EventCustom* evt);


	void loadBg();
	WORD SwitchViewChairID(WORD chair_id);//ת�����ҵ��ӽ��µ�CHAIR ID
	void createShooter();
	void onBulletFire();//�����ӵ�
	bool IsSameSide(WORD chair_id1, WORD chair_id2);
	void showLoading();
	void startChain(WORD view_chair_id);
	void removeBingo(Node* pSender);
	void shakeScreen();
	void reset(Node* pSender);//�����㸴λ
	void changeScenePro(float dt);
	void changeSceneOver(Node* pSender);//�����л����
	void createWave(Node* parent,bool isNextScene =false);
	void fishPauseOver(Node* pSender);
	void bgLuDealOver(Node* pSender);
	void preLoadSoundRes();
	void DealBaoJiEffect(WORD chair_id);//���ű���Ч��
	void dealbombEffect(Vec2 pos);

	void ExecuteEffect(GameFish* fish);
	void dealPauseStartEffect();//���ſ�ʼ��ͣЧ��
	void dealPauseEndEffect();

	void fengyinStay(Node* pSend);
	void onBack(Ref* pSender,ui::Widget::TouchEventType type);
	void onClickGuide(Ref* pSender,ui::Widget::TouchEventType type);
	//������ʾ
	void RenderKickoutTips();
	//����ϵͳ��Ϣ
	void popCommonTip(__String* content);
	void showNextTip(Node* pSender);
	//����վ������ʱ����
	void standupOverTime(Node* node);
	//
	std::string getMusicBackgroudName(int index);

	void showOutTip(FishKind kid);
	void hideOutTip(Node* pSender);
	void exitGameRoom();

	BulletKind calBulletKind();

protected:
	int                mRoomLevel;
	int                mGameKind;
	GamePlayerManager* mPlayerManager;//��ҹ�����
	GamePlayer*        me;
	Sprite*            mCursorSp;
	Sprite*            mBgSp;
	ImageView*		   mIceImage;
	int mGameStaus;
	bool mIsLookOn;
	ClientGameConfig mGameConfig;
	Layer* myLayer;//fish ��
	Layer* mBgLayer;//�����㣬��������
	DWORD mLastFireTime;
	DWORD mSpcialSceneBeganTime;//���ⳡ����ʼʱ��
	float   mAngle;
	bool    mBlongPressed;
	int    mLoadResourseCount;
	LoadingScene* mLoadingWidget;
	typedef std::deque<GameBullet*> BulletQueue;
	BulletQueue mBulletQueue;
	bool  mCanShooter;//�Ƿ���������
	SceneKind next_scene_kind;//��һ������ID 
	SceneFishManager* mSceneFishManager;
	bool is_special_scene_;//����������
	float special_scene_waited_time_;//�����������ʱ��
	int mCurBgIndex;
	__Array * mWaves;
	int  mWaveIndex;
	__Array* mNextSceneWaves;
	float mWaveInterval;
	int   mDealCnt;//Ч�����������
	float bubble_elapsed_;
	LabelAtlas* mKickOutLabel;
	__Array*    mMsgArray;

	bool bSend;//�Ƿ��ѷ�������

	ImageView* mTipOutFish;//����������ֵ���ʾͼƬ
	__Array* mParticlesArray;
	SpriteBatchNode* mBulletBatchNode;
	SpriteBatchNode* mCoinBatchNode;

	//�򵼲�
	GameGuideWidget*  mGuideWidget;
	bool  mScoreIsChange ; 
	bool  mIsMatchFlag;

	//�������
	GameMatchModel* mGameMatchInfo;
	GameMatchManager* mMatchManager;
	bool mbEnterMatch;
	bool bShowAward;
};




#endif //_GAME_SCENE_H_H_