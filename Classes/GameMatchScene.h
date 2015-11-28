
/**
 * @file GameMatchScene
 * @brief ��Ϸ��������
 * @author tjl
 * @date 2015-10-23
 */


#ifndef __GameMatchScene_SCENE_H__
#define __GameMatchScene_SCENE_H__

#include "cocos2d.h"
#include "GameBaseScene.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace ui;
USING_NS_CC;


class GameMatchScene : public GameBaseScene {
public:
	GameMatchScene();
	~GameMatchScene();
	static GameMatchScene* create(bool isBcontinue = false);//�Ƿ��Ǽ�������
	virtual bool init(bool isBcontinue);
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();

	virtual void onExit();
	virtual void okCallback();

	void loadUI();

	void DeleteMatchRoomMsg(EventCustom* evt);
	void receiveMatchRoomListMsg(EventCustom* evt);
	void updateRoomInfoMsg(EventCustom* evt);
	//�����ɹ����ش���
	void receiveSignUpSuccessMsg(EventCustom* evt);
	//����ʧ�ܷ��ش���
	void receiveSignUpFaildMsg(EventCustom* evt);
	//�����ɹ����ش���
	void receiveUnSignUpSuccessMsg(EventCustom* evt);
	//����ʧ�ܷ��ش���
	void receiveUnSignUpFaildMsg(EventCustom* evt);
	//����ʱ���ش���
	void receiveMatchCountDownMsg(EventCustom* evt);
	//���ͱ�������
	void toSendSignUpRequest(EventCustom* evt);
	//������������
	void toSendunSignUpRequest(EventCustom* evt);
	//����������������Ϣ����
	void ReceiveMatchPlayCountIsMaxMsg(EventCustom* evt);
	void taskSorketConnetFail(EventCustom* evt);

	void updateSignUpPlayers(float dt);
	int getMatchRoomCountByType(int type);

	void showLoading();
	void removeLoading();
	void setShowWait(bool value) {mShowWait = value;} 
protected:
	void onClickBack(Ref* pSender,ui::Widget::TouchEventType type);
	void playScaleAnimation(bool less, Ref* pSender) ;
	char* getWidgetJsonName();
	ListView* mMatchList;
	cocos2d::ui::Widget* m_mainWidget;
	bool          mbContinueMatch; //��������
	bool          mNeedBind;
	bool          mShowWait;
};

#endif //__GameMatch_SCENE_H__
