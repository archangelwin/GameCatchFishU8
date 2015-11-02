
/**
 * @file GameSmallScene
 * @brief ��ϷС��
 * @author tjl
 * @date 2015-6-29
 */


#ifndef __GAMESAMLL_SCENE_H__
#define __GAMESAMLL_SCENE_H__

#include "cocos2d.h"
#include "GameBaseScene.h"
#include "GameFishAction.h"
#include "GameBulletManager.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Common/ResourcePackManager.h"
#include "Common/SmallLoadingProgressWidget.h"

using namespace ui;
USING_NS_CC;

enum  BubbleType
{
	BubbleNormal = 0,
	BubbleDntg,
	BubbleLkpy,
	BubbleJcpy,
	BUBBLE_MAXCOUNT
};

class BubbleItem : public Sprite
{
public:
	BubbleItem();
	~BubbleItem();
	static BubbleItem* create(float angle,float speed,Vec2 pos,BubbleType Bubbletype );
	bool init(float angle,float speed,Vec2 pos,BubbleType Bubbletype );
	void update(float delta);
	void render();
	ActionBubbletMove* getAction() const {return mAction;}
protected:
	ActionBubbletMove* mAction;
	BubbleType  mBubbleType;

};

class GameSmallScene : public GameBaseScene,public ResourcePackProtocol {
public:
	GameSmallScene();
	~GameSmallScene();
	static GameSmallScene* create(int roomLevel);
	virtual bool init(int roomLevel);
	virtual void onEnter();
	virtual void onExit();

	void loadUI();
	void creatBubble(BubbleType type, Vec2 pos);
	void update(float dt);

	virtual void okCallback();
	void showLoading();
	void removeLoading();

	//ȫ�����̳ɹ�ʱ�ص�, ����ǵ�����Դ����ģʽ, ÿ����Դ����������̺�Ҳ��ص�
	virtual void onSuccess(ResourcePack *pack);

	//ʧ�ܻص�
	virtual void onError(ResourcePack *pack, TNAssetsManagerActionCode errorCode);

	//��ǰ��Դ�����صĽ��Ȼص�, progress(0-100)
	virtual void onProgress(ResourcePack *pack, int progress);

	void loginRealRoomSuccessRsp(EventCustom* evt);
	void loginRealRoomFailureRsp(EventCustom* evt);
	//ˢ�½��
	void refreshTreasureData(EventCustom* evt);
protected:
	char* getWidgetJsonName();
	void onClickJcpy(Ref* pSender,ui::Widget::TouchEventType type);
	void onClickLkpy(Ref* pSender,ui::Widget::TouchEventType type);
	void onClickDntg(Ref* pSender,ui::Widget::TouchEventType type);
	void onClickBack(Ref* pSender,ui::Widget::TouchEventType type);
	void playScaleAnimation(bool less, Ref* pSender) ;
	void createGameSorket();
	void connectGameServer(RoomLevelInfo* info);
	void receiveConnectFailMsg(EventCustom* evt);
	void receiveDownLoadInfo(EventCustom* evt);
protected:
	int     mRoomLevel;
	__Array* mBubbleArray;
	cocos2d::ui::Widget* m_mainWidget;
	int      mSelectGameKind;
	SmallLoadingProgressWidget* mLoading_forLk;
	SmallLoadingProgressWidget* mLoading_forJc;

};

#endif //__GAMESAMLL_SCENE_H__
