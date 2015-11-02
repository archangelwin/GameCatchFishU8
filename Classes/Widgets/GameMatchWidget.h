#ifndef __GameMatchWidget_H_H_
#define __GameMatchWidget_H_H_

/**
 * @file GameMatchWidget
 * @brief  ��Ϸ�������� 
 * @author tjl
 * @date 15-10-16
 */


#include "cocos2d.h"
#include "Common/TNWidget.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Model/MatchModel.h"
using namespace cocos2d::ui;
USING_NS_CC;

class GameMatchItem : public Layout
{
public:
	GameMatchItem();
	~GameMatchItem();
	static GameMatchItem* create(bool isRoot ,MatchInfoModel* info = nullptr ,int matchtype =0);
	virtual bool init(bool isRoot ,MatchInfoModel* info = nullptr,int matchtype =0);
	bool isRoot() {return mBRoot;}
	MatchInfoModel* getMatchInfo() {return mData;}
	void refreshData(MatchInfoModel* info);
	void refreshSignUpplayer();
	int    getMatchType () {return m_matchtype;}
	void onClickSignUp(Ref* pSender,ui::Widget::TouchEventType type);
protected:
	bool mBRoot; //�Ǹ���ڵ�
	MatchInfoModel* mData;
	int   m_matchtype;
	Text* m_signUpPlayers;//��������
	Button* m_btnSignUp;
};

/*class GameMatchWidget : public TNWidget
{
public:
	GameMatchWidget();
	~GameMatchWidget();
	virtual bool init();
	void onEnter();
	void onExit();
	std::string getWidgetJsonName();
	void loadUI();
	CREATE_FUNC(GameMatchWidget);
	void onBack(Ref* pSender,ui::Widget::TouchEventType type);
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
	//������ʼ���ش���
	void receiveMatchStartMsg(EventCustom* evt);
	//����ʱ���ش���
	void receiveMatchCountDownMsg(EventCustom* evt);
	//��¼��������ɹ�
	void loginMatchRoomSuccessRsp(EventCustom* evt);
	//��¼��������ʧ��
	void loginMatchRoomFailureRsp(EventCustom* evt);
	//���ͱ�������
	void toSendSignUpRequest(EventCustom* evt);
	//������������
	void toSendunSignUpRequest(EventCustom* evt);

	void updateSignUpPlayers(float dt);
	int getMatchRoomCountByType(int type);
protected:
	void createGameSorket();
	void connectGameServer(const char* ip ,int port);//���ӱ���������
	void showLoading();
	void removeLoading();
	ListView* mMatchList;
};*/


#endif//__GameMatchWidget_H_H_