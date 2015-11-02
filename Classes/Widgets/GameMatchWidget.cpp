#include "GameMatchWidget.h"
#include "Common/TNVisibleRect.h"
#include "SessionManager.h"
#include "GameResourcesManager.h"
#include "CommonFunction.h"
#include "SessionManager.h"
#include "MsgDefine/CMD_LogonServer.h"
#include "MsgDefine/CMD_GameServer.h"
#include "Message.h"
#include "GameServiceClientManager.h"
#include "Common/AlertWidget.h"
#include "Common/ModalViewManager.h"
#include "GameScene.h"
#include "Common/CommonLoadingWidget.h"
#include "GameMatchEnterWidget.h"

#define  imageBgTag 42
#define  ListViewBgTag 12548
#define ListViewTag  12488

GameMatchItem::GameMatchItem()
{
	mData = nullptr;
	m_btnSignUp = nullptr;
	m_signUpPlayers = nullptr;
	m_matchtype = 0;
}

GameMatchItem::~GameMatchItem()
{
	CC_SAFE_RELEASE_NULL(mData);
}

GameMatchItem* GameMatchItem::create(bool isRoot ,MatchInfoModel* info,int matchtype)
{
	GameMatchItem* pitem = new GameMatchItem();
	if (pitem&&pitem->init(isRoot,info,matchtype))
	{
		pitem->autorelease();
		return pitem;
	}
	delete pitem;
	pitem = nullptr;
	return pitem;
}

bool GameMatchItem::init(bool isRoot ,MatchInfoModel* info,int matchtype)
{
	if (!Layout::init())
		return false;
	setContentSize(Size(920,65));
	mBRoot = isRoot;
	m_matchtype = matchtype;
	if (isRoot)
	{
		ui::Scale9Sprite* itemBg = ui::Scale9Sprite::create("match/u_root_bg.png");
		itemBg->setPosition(Vec2(getSize().width/2,getSize().height/2));
		itemBg->setContentSize(Size(920,45));
		addChild(itemBg);

		ImageView* icon = ImageView::create();
		icon->loadTexture("match/u_icon_fish.png",ui::Widget::TextureResType::LOCAL);
		icon->setPosition(Vec2(icon->getContentSize().width/2 + 15,getSize().height/2));
		addChild(icon);

		Text* title = Text::create();
		switch (matchtype)
		{
		case  FULLPLAYERMATCH:
			title->setText(CommonFunction::GBKToUTF8("���˱���"));
			break;
		case  BUYUFOREVERMATCH:
			title->setText(CommonFunction::GBKToUTF8("����ѭ����"));
			break;
		case  BUYUTIMEMATCH:
			title->setText(CommonFunction::GBKToUTF8("���㶨ʱ��"));
			break;
		case  BUYUBIGAWARDMATCH:
			title->setText(CommonFunction::GBKToUTF8("�������"));
			break;
		}
		title->setFontSize(30);
		title->setPosition(Vec2(icon->getContentSize().width/2 + icon->getPositionX() + 10,getSize().height/2));
		title->setTextColor(ccc4(255,252,0,255));
		title->setAnchorPoint(Vec2(0, 0.5));
		addChild(title);
	}
	else
	{
		mData = info;
		mData->retain();
		
		Text* remarks = Text::create();
		remarks->setFontSize(25);
		remarks->setText(CommonFunction::GBKToUTF8(mData->getMatchRemark().c_str()));
		remarks->setPosition(Vec2( 15,getSize().height/2));
		remarks->setAnchorPoint(Vec2(0, 0.5));
		addChild(remarks);

		Text* signUpScoreText = Text::create();
		signUpScoreText->setFontSize(25);
		__String* signStr = nullptr;
		if (mData->getSignUpTicket() > 0)
		{
			signStr = __String::createWithFormat("%d%s",mData->getSignUpTicket(),CommonFunction::GBKToUTF8("������").c_str());
			signUpScoreText->setText(signStr->getCString());
		}
		else if(mData->getSignUpScore() > 0)
		{
			signStr = __String::createWithFormat("%lld%s",mData->getSignUpScore(),CommonFunction::GBKToUTF8("���").c_str());
			signUpScoreText->setText(signStr->getCString());
		}
		bool isFreeCharge = false;//���
		if ( nullptr == signStr)
		{
			isFreeCharge = true;
			signUpScoreText->setText(CommonFunction::GBKToUTF8("��ѱ���"));
		}
		signUpScoreText->setPosition(Vec2(385,getSize().height/2));
		signUpScoreText->setAnchorPoint(Vec2(0.5, 0.5));
		signUpScoreText->setTextColor(ccc4(255,0,0,255));
		addChild(signUpScoreText);

		Text* matchTimeText = Text::create();
		matchTimeText->setFontSize(25);
		SYSTEMTIME curtime = info->getMatchTime();
		std::string time_str = __String::createWithFormat("%d-%d",curtime.wMonth,curtime.wDay)->getCString();
		if (strcmp(time_str.c_str(),SessionManager::shareInstance()->getMatchTime().c_str()) == 0 )//����
		{
			__String* content= __String::createWithFormat("%s %02d:%02d",CommonFunction::GBKToUTF8("����").c_str(),curtime.wHour,curtime.wMinute);
			matchTimeText->setText(content->getCString());
		}
		else
		{
			__String* content= __String::createWithFormat("%d-%d %02d:%02d",curtime.wMonth,curtime.wDay,curtime.wHour,curtime.wMinute);
			matchTimeText->setText(content->getCString());
		}
		matchTimeText->setPosition(Vec2(465,getSize().height/2));
		matchTimeText->setAnchorPoint(Vec2(0,0.5));
		addChild(matchTimeText);

		//�ѱ�������
		m_signUpPlayers = Text::create();
		m_signUpPlayers->setFontSize(25);
		__String* signNumber = nullptr;
		if (info->getSerialModel()->getMatchType() != 4)
		{
			signNumber = __String::createWithFormat("%d%s",info->getSignUpPlayerNum(),CommonFunction::GBKToUTF8("���ѱ���").c_str());
		}
		else
		{
			signNumber = __String::createWithFormat("%d%s",info->getSignUpPlayerNum(),CommonFunction::GBKToUTF8("���Ѳ���").c_str());
		}
		m_signUpPlayers->setText(signNumber->getCString());
		m_signUpPlayers->setAnchorPoint(Vec2(0,0.5));
		m_signUpPlayers->setPosition(Vec2(620,getSize().height/2));
		addChild(m_signUpPlayers);

		//������ť
		m_btnSignUp = Button::create();
		if (info->getsignUpStatus() == SignUpStatus::NoSignUp)
		{
			if(isFreeCharge)
			{
				m_btnSignUp->loadTextureNormal("match/btn_free.png",Widget::TextureResType::LOCAL);
				m_btnSignUp->loadTexturePressed("match/btn_free_on.png",Widget::TextureResType::LOCAL);
			}
			else
			{
				m_btnSignUp->loadTextureNormal("match/btn_signUp.png",Widget::TextureResType::LOCAL);
				m_btnSignUp->loadTexturePressed("match/btn_signUp_on.png",Widget::TextureResType::LOCAL);
			}
		}else if (info->getsignUpStatus() == SignUpStatus::SignUp)
		{
			m_btnSignUp->loadTextureNormal("match/btn_unSignUp.png",Widget::TextureResType::LOCAL);
			m_btnSignUp->loadTexturePressed("match/btn_unSignUp_on.png",Widget::TextureResType::LOCAL);
		}
		m_btnSignUp->setPosition(Vec2(830,getSize().height/2 ));
		m_btnSignUp->addTouchEventListener(CC_CALLBACK_2(GameMatchItem::onClickSignUp, this));
		addChild(m_btnSignUp);

	}


	return true;
}
void GameMatchItem::onClickSignUp(Ref* pSender,ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (mData->getsignUpStatus() == SignUpStatus::NoSignUp)
		{

			ModalViewManager::sharedInstance()->showWidget(GameMatchEnterWidget::create(mData));
			//Director::sharedDirector()->getEventDispatcher()->dispatchCustomEvent(toSignUpNotice,mData);

		}else if(mData->getsignUpStatus() == SignUpStatus::SignUp)
		{
			Director::sharedDirector()->getEventDispatcher()->dispatchCustomEvent(tounSignUpNotice,mData);
		}
	
	}
}

void GameMatchItem::refreshData(MatchInfoModel* info)
{
	if(mData)
		mData->release();
	mData = info;
	mData->retain();

	__String* signNumber = nullptr;
	if (mData->getSerialModel()->getMatchType() != 4)
	{
		signNumber = __String::createWithFormat("%d%s",mData->getSignUpPlayerNum(),CommonFunction::GBKToUTF8("���ѱ���").c_str());
	}
	else
	{
		signNumber = __String::createWithFormat("%d%s",mData->getSignUpPlayerNum(),CommonFunction::GBKToUTF8("���Ѳ���").c_str());
	}
	m_signUpPlayers->setText(signNumber->getCString());

	if (info->getsignUpStatus() == SignUpStatus::NoSignUp)
	{
		if(mData->getSignUpTicket() == 0 && mData->getSignUpScore()== 0)
		{
			m_btnSignUp->loadTextureNormal("match/btn_free.png",Widget::TextureResType::LOCAL);
			m_btnSignUp->loadTexturePressed("match/btn_free_on.png",Widget::TextureResType::LOCAL);
		}
		else
		{
			m_btnSignUp->loadTextureNormal("match/btn_signUp.png",Widget::TextureResType::LOCAL);
			m_btnSignUp->loadTexturePressed("match/btn_signUp_on.png",Widget::TextureResType::LOCAL);
		}
	}else if (info->getsignUpStatus() == SignUpStatus::SignUp)
	{
		m_btnSignUp->loadTextureNormal("match/btn_unSignUp.png",Widget::TextureResType::LOCAL);
		m_btnSignUp->loadTexturePressed("match/btn_unSignUp_on.png",Widget::TextureResType::LOCAL);
	}
}

void GameMatchItem::refreshSignUpplayer()
{
	__String* signNumber = nullptr;
	if (mData->getSerialModel()->getMatchType() != 4)
	{
		signNumber = __String::createWithFormat("%d%s",mData->getSignUpPlayerNum(),CommonFunction::GBKToUTF8("���ѱ���").c_str());
	}
	else
	{
		signNumber = __String::createWithFormat("%d%s",mData->getSignUpPlayerNum(),CommonFunction::GBKToUTF8("���Ѳ���").c_str());
	}
	m_signUpPlayers->setText(signNumber->getCString());
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*GameMatchWidget::GameMatchWidget()
{
}

GameMatchWidget::~GameMatchWidget()
{

}

std::string GameMatchWidget::getWidgetJsonName()
{
	return "matchWiget";
}

void GameMatchWidget::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);
	unschedule(schedule_selector(GameMatchWidget::updateSignUpPlayers));
	TNWidget::onExit();
}

void GameMatchWidget::onEnter()
{
	TNWidget::onEnter();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(deleteMatchRoomMsg, CC_CALLBACK_1(GameMatchWidget::DeleteMatchRoomMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(refreshMatchListMsg, CC_CALLBACK_1(GameMatchWidget::receiveMatchRoomListMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(updateRoomSignUpPlayersMsg, CC_CALLBACK_1(GameMatchWidget::updateRoomInfoMsg, this)), this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(signUpSuccessMsg, CC_CALLBACK_1(GameMatchWidget::receiveSignUpSuccessMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(signUpFaildMsg, CC_CALLBACK_1(GameMatchWidget::receiveSignUpFaildMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(unSignUpSuccessMsg, CC_CALLBACK_1(GameMatchWidget::receiveUnSignUpSuccessMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(unSignUpFaildMsg, CC_CALLBACK_1(GameMatchWidget::receiveUnSignUpFaildMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(matchStartMsg, CC_CALLBACK_1(GameMatchWidget::receiveMatchStartMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(matchCountDownMsg, CC_CALLBACK_1(GameMatchWidget::receiveMatchCountDownMsg, this)), this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(loginRealRoomSuccess, CC_CALLBACK_1(GameMatchWidget::loginMatchRoomSuccessRsp, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(loginRealRoomFailure, CC_CALLBACK_1(GameMatchWidget::loginMatchRoomFailureRsp, this)), this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(toSignUpNotice, CC_CALLBACK_1(GameMatchWidget::toSendSignUpRequest, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(tounSignUpNotice, CC_CALLBACK_1(GameMatchWidget::toSendunSignUpRequest, this)), this);
	//��ʱ��ÿ����ˢ�±�������
	schedule(schedule_selector(GameMatchWidget::updateSignUpPlayers),3.0);
}

void GameMatchWidget::updateSignUpPlayers(float dt)
{
	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	c->sendRefrshMatchPlayers();
}

bool GameMatchWidget::init( )
{
	if (!TNWidget::init())
	{
		return false;
	}

	return true;
}
void GameMatchWidget::loadUI()
{

	TNWidget::loadUI();

	//������¼�
	 ImageView* bg = static_cast<ImageView*>(m_mainWidget->getChildByTag(imageBgTag));
	
	 ImageView* listBg = static_cast<ImageView*>(bg->getChildByTag(ListViewBgTag));

	 mMatchList = static_cast<ListView*>(listBg->getChildByTag(ListViewTag));
	 mMatchList->setBounceEnabled(true);
	 mMatchList->removeAllItems();

	//����
	 SessionManager::shareInstance()->sortMatchRooms();
	 __Array* matchRooms = SessionManager::shareInstance()->getMatchRooms();

	  GameMatchItem* pMatchItem = nullptr;
	 bool nHasMatch = SessionManager::shareInstance()->isHastheMatch(FULLPLAYERMATCH);
	 if (nHasMatch)//��Ӹ��ڵ�
	 {
		 GameMatchItem* pFullRoot = GameMatchItem::create(true,nullptr,FULLPLAYERMATCH);
		 mMatchList->pushBackCustomItem(pFullRoot);

		 for ( int i = 0 ; i < matchRooms->count();i++)
		 {
			 MatchInfoModel* pInfoModel = (MatchInfoModel*)matchRooms->getObjectAtIndex(i);
			 if (pInfoModel->getSerialModel()->getMatchType() == FULLPLAYERMATCH )
			 {
				 pMatchItem = GameMatchItem::create(false,pInfoModel);
				 mMatchList->pushBackCustomItem(pMatchItem);
			 }
		 }
	 }

	 //����ѭ����
	 nHasMatch = SessionManager::shareInstance()->isHastheMatch(BUYUFOREVERMATCH);
	 if (nHasMatch)//��Ӹ��ڵ�
	 {
		 GameMatchItem* pFullRoot = GameMatchItem::create(true,nullptr,BUYUFOREVERMATCH);
		 mMatchList->pushBackCustomItem(pFullRoot);

		 for ( int i = 0 ; i < matchRooms->count();i++)
		 {
			 MatchInfoModel* pInfoModel = (MatchInfoModel*)matchRooms->getObjectAtIndex(i);
			 if (pInfoModel->getSerialModel()->getMatchType() == BUYUFOREVERMATCH )
			 {
				 pMatchItem = GameMatchItem::create(false,pInfoModel);
				 mMatchList->pushBackCustomItem(pMatchItem);
			 }
		 }
	 }

	 //���㶨ʱ��
	 nHasMatch = SessionManager::shareInstance()->isHastheMatch(BUYUTIMEMATCH);
	 if (nHasMatch)//��Ӹ��ڵ�
	 {
		 GameMatchItem* pFullRoot = GameMatchItem::create(true,nullptr,BUYUTIMEMATCH);
		 mMatchList->pushBackCustomItem(pFullRoot);

		 for ( int i = 0 ; i < matchRooms->count();i++)
		 {
			 MatchInfoModel* pInfoModel = (MatchInfoModel*)matchRooms->getObjectAtIndex(i);
			 if (pInfoModel->getSerialModel()->getMatchType() == BUYUTIMEMATCH )
			 {
				 pMatchItem = GameMatchItem::create(false,pInfoModel);
				 mMatchList->pushBackCustomItem(pMatchItem);
			 }
		 }
	 }

	 //�������
	 nHasMatch = SessionManager::shareInstance()->isHastheMatch(BUYUBIGAWARDMATCH);
	 if (nHasMatch)//��Ӹ��ڵ�
	 {
		 GameMatchItem* pFullRoot = GameMatchItem::create(true,nullptr,BUYUBIGAWARDMATCH);
		 mMatchList->pushBackCustomItem(pFullRoot);

		 for ( int i = 0 ; i < matchRooms->count();i++)
		 {
			 MatchInfoModel* pInfoModel = (MatchInfoModel*)matchRooms->getObjectAtIndex(i);
			 if (pInfoModel->getSerialModel()->getMatchType() == BUYUBIGAWARDMATCH )
			 {
				 pMatchItem = GameMatchItem::create(false,pInfoModel);
				 mMatchList->pushBackCustomItem(pMatchItem);
			 }
		 }
	 }

	 //exit btn
	 Button* btn_exit = Button::create();
	 btn_exit->loadTextureNormal("common_Alert_btn_close.png",Widget::TextureResType::LOCAL);
	 btn_exit->loadTexturePressed("common_Alert_btn_close_on.png",Widget::TextureResType::LOCAL);
	 btn_exit->setPosition(Vec2(bg->getContentSize().width - btn_exit->getContentSize().width/2,bg->getContentSize().height - btn_exit->getContentSize().height/2));
	 btn_exit->addTouchEventListener(CC_CALLBACK_2(GameMatchWidget::onBack, this));
	 bg->addChild(btn_exit);
}

void GameMatchWidget::onBack(Ref* pSender,ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		removeFromParent();
	}
}



void GameMatchWidget::DeleteMatchRoomMsg(EventCustom* evt)
{
	MatchSerialModel* pModel = (MatchSerialModel*)evt->getUserData();
	Vector<Widget*> roomItems = mMatchList->getItems();
	for (int i = 0 ; i < roomItems.capacity();i++)
	{
		GameMatchItem* pMatchItem = (GameMatchItem*)roomItems.at(i);
		if (pMatchItem->isRoot())//��������
		{
			continue;
		}
		MatchInfoModel* pData = pMatchItem->getMatchInfo();
		if (pData->getSerialModel()->getMatchInfoID() == pModel->getMatchInfoID())//�ҵ�����
		{
			mMatchList->removeItem(i);
			break;
		}
	}

}

int GameMatchWidget::getMatchRoomCountByType(int type)
{
	int cnt = 0;
	Vector<Widget*> roomItems = mMatchList->getItems();
	for (int i = 0 ; i < roomItems.capacity();i++)
	{
		GameMatchItem* pMatchItem = (GameMatchItem*)roomItems.at(i);
		if (pMatchItem->isRoot())//��������
			continue;
		MatchInfoModel* pData = pMatchItem->getMatchInfo();
		if (pData->getSerialModel()->getMatchType() == type)//�ҵ�ͬ���͵ĳ�û�޳�
		{
			cnt++;
		}
	}
	return cnt;
}

void GameMatchWidget::receiveMatchRoomListMsg(EventCustom* evt)
{
	__Dictionary* dic = (__Dictionary*)evt->getUserData();
	bool isNewMatch = ((__Bool*)dic->objectForKey("isNewMatch"))->getValue();
	MatchInfoModel* pModel = (MatchInfoModel*)dic->objectForKey("matchInfo");
	bool isLastItemFlag = true;//�ڸñ��������Ҳ����������SORTID 
	Vector<Widget*> roomItems = mMatchList->getItems();
	for (int i = 0 ; i < roomItems.capacity();i++)
	{
		GameMatchItem* pMatchItem = (GameMatchItem*)roomItems.at(i);
		if (pMatchItem->isRoot())//��������
		{
			int roomType =  pModel->getSerialModel()->getMatchType();
			if (pMatchItem->getMatchType() == roomType && getMatchRoomCountByType(roomType) == 0)
			{
				if(isNewMatch)//�ڸ��ڵ��������ӽڵ�
				{
					pMatchItem = GameMatchItem::create(false,pModel);
					mMatchList->insertCustomItem(pMatchItem,i+1);
					isLastItemFlag = false ;
					break;
				}
			}
			else
			{
				continue;
			}
		}
		MatchInfoModel* pData = pMatchItem->getMatchInfo();
		if (pData->getSerialModel()->getMatchType() == pModel->getSerialModel()->getMatchType())//�ҵ�ͬ���͵ĳ�û�޳�
		{
			if (isNewMatch)
			{
				//�ҵ������
				if (pData->getSerialModel()->getSortId() > pModel->getSerialModel()->getSortId())
				{
					pMatchItem = GameMatchItem::create(false,pModel);
					mMatchList->insertCustomItem(pMatchItem,i);
					isLastItemFlag = false;
					break;
				}

			}
			else
			{
				if (pData->getSerialModel()->getMatchInfoID() == pModel->getSerialModel()->getMatchInfoID())
				{
					pMatchItem->refreshData(pModel);
				}
			}
		}
	}

	if (isNewMatch && isLastItemFlag)
	{

	}
}


//ˢ�·�����Ϣ
void GameMatchWidget::updateRoomInfoMsg(EventCustom* evt)
{
	__Array* pArray = (__Array*)evt->getUserData();
	for (int i=0; i < pArray->count(); i ++)
	{
		__Dictionary* infoDic = (__Dictionary*)pArray->getObjectAtIndex(i);
		MatchSerialModel* pSerialModel = (MatchSerialModel*)infoDic->objectForKey("serialModel");
		int signUpNum =  ((__Integer*)infoDic->objectForKey("signUpNum"))->getValue();
		int groupCnt =  ((__Integer*)infoDic->objectForKey("groupCount"))->getValue();
		MatchInfoModel* pMatchInfo = SessionManager::shareInstance()->getMatchInfoByID(pSerialModel->getMatchInfoID());
		if (pMatchInfo)
		{
			pMatchInfo->setSignUpPlayerNum(signUpNum);
			pMatchInfo->setCurGroupCount(groupCnt);
		}
	}

	//ˢ��UI
	Vector<Widget*> roomItems = mMatchList->getItems();
	for (int i = 0 ; i < roomItems.capacity();i++)
	{
		GameMatchItem* pMatchItem = (GameMatchItem*)roomItems.at(i);
		if (pMatchItem->isRoot())//��������
		{
			continue;
		}
		pMatchItem->refreshSignUpplayer();
	}
}


//�����ɹ����ش���
void GameMatchWidget::receiveSignUpSuccessMsg(EventCustom* evt)
{
	removeLoading();
	CMD_GL_SignUpSuccess * MatchID=(CMD_GL_SignUpSuccess *)evt->getUserData();
	if (MatchID->dwSignUpScore > 0)
	{
		//֪ͨ������ˢ�½��
		OnlineUserModel* pUser = SessionManager::shareInstance()->getUser();
		pUser->setUserScore(pUser->getUserScore() - MatchID->dwSignUpScore);
		Director::sharedDirector()->getEventDispatcher()->dispatchCustomEvent(updateUserInfoMsg);
	}
	//ˢ��״̬
	Vector<Widget*> roomItems = mMatchList->getItems();
	for (int i = 0 ; i < roomItems.capacity();i++)
	{
		GameMatchItem* pMatchItem = (GameMatchItem*)roomItems.at(i);
		if (pMatchItem->isRoot()) continue;//��������
		MatchInfoModel* pData = pMatchItem->getMatchInfo();
	
		if (pData->getSerialModel()->getMatchInfoID() == MatchID->MatchSerial.dwMatchInfoID)
		{
			pData->setsignUpStatus(SignUpStatus::SignUp);
			pMatchItem->refreshData(pData);
		}
	}
	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(nullptr,"",CommonFunction::GBKToUTF8(MatchID->szDescribeString)));
}

//����ʧ�ܷ��ش���
void GameMatchWidget::receiveSignUpFaildMsg(EventCustom* evt)
{
	removeLoading();
	CMD_GL_SignUpFailure * pOperateFailure=(CMD_GL_SignUpFailure *)evt->getUserData();
	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(nullptr,"",CommonFunction::GBKToUTF8(pOperateFailure->szDescribeString)));
}

//�����ɹ����ش���
void GameMatchWidget::receiveUnSignUpSuccessMsg(EventCustom* evt)
{
	removeLoading();

	CMD_GL_SignUpSuccess * MatchID=(CMD_GL_SignUpSuccess *)evt->getUserData();
	if (MatchID->dwSignUpScore > 0)
	{
		//֪ͨ������ˢ�½��
		OnlineUserModel* pUser = SessionManager::shareInstance()->getUser();
		pUser->setUserScore(pUser->getUserScore() + MatchID->dwSignUpScore);
		Director::sharedDirector()->getEventDispatcher()->dispatchCustomEvent(updateUserInfoMsg);
	}
	//ˢ��״̬
	Vector<Widget*> roomItems = mMatchList->getItems();
	for (int i = 0 ; i < roomItems.capacity();i++)
	{
		GameMatchItem* pMatchItem = (GameMatchItem*)roomItems.at(i);
		if (pMatchItem->isRoot()) continue;//��������
		MatchInfoModel* pData = pMatchItem->getMatchInfo();
		
		if (pData->getSerialModel()->getMatchInfoID() == MatchID->MatchSerial.dwMatchInfoID)
		{
			pData->setsignUpStatus(SignUpStatus::NoSignUp);
			pMatchItem->refreshData(pData);
		}
	}

	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(nullptr,"",CommonFunction::GBKToUTF8(MatchID->szDescribeString)));
}

//����ʧ�ܷ��ش���
void GameMatchWidget::receiveUnSignUpFaildMsg(EventCustom* evt)
{
	removeLoading();
	CMD_GL_SignUpFailure * pOperateFailure=(CMD_GL_SignUpFailure *)evt->getUserData();
	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(nullptr,"",CommonFunction::GBKToUTF8(pOperateFailure->szDescribeString)));
}

//������ʼ���ش���
void GameMatchWidget::receiveMatchStartMsg(EventCustom* evt)
{
	removeLoading();
	CMD_GL_MatchServer * pMatchServer =(CMD_GL_MatchServer *)evt->getUserData();
	//����SORKET
	createGameSorket();
	//���ӷ�����
	connectGameServer(pMatchServer->szServerIP,pMatchServer->dwServerPort);

}

void GameMatchWidget::createGameSorket()
{
	//��ʼ��SOCKET
	GameServiceClientManager *m = GameServiceClientManager::sharedInstance();
	GameServiceClient* c = m->serviceClientForName(XwZoneDntg);
	if(c == NULL)
	{
		m->registerServiceClient(XwZoneDntg, false,GAMEROOM_SORKET_INDEX);
		GameServiceClient* c = m->serviceClientForName(XwZoneDntg);
	}
}

void GameMatchWidget::connectGameServer(const char* ip ,int port)
{
	GameServiceClientManager *m = GameServiceClientManager::sharedInstance();
	GameServiceClient* c = m->serviceClientForName(XwZoneDntg);

	bool ret = c->Connect(ip,port);
	//���ӳɹ�
	if(ret)
	{
		showLoading();
		c->loginMatchRoom();
	}
	else
	{
		ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(nullptr,"",CommonFunction::GBKToUTF8("��Ϸ�������쳣������ϵ�ͷ�!")));
	}
}

//����ʱ���ش���
void GameMatchWidget::receiveMatchCountDownMsg(EventCustom* evt)
{

}

void GameMatchWidget::loginMatchRoomSuccessRsp(EventCustom* evt)
{
	removeLoading();
	SessionManager::shareInstance()->setGameKind(GameKindDntg);
	//������Ϸ֮ǰ����������߶�����������������
	ResourcesManager::getInstance()->loadResourceFile(GameKindDntg);
	ResourcesManager::getInstance()->loadGuideFile(GameKindDntg);
	SessionManager::shareInstance()->setInGame(true);

	removeFromParent();
	Director::sharedDirector()->replaceScene(GameScene::create(RoomLevel_2,GameKindDntg,true));
}

void GameMatchWidget::loginMatchRoomFailureRsp(EventCustom* evt)
{
	removeLoading();
	CMD_GR_LogonFailure* errorCode = (CMD_GR_LogonFailure*)evt->getUserData();
	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(nullptr,"",CommonFunction::GBKToUTF8(errorCode->szDescribeString)));
}

//���ͱ�������
void GameMatchWidget::toSendSignUpRequest(EventCustom* evt)
{
	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	//����
	MatchInfoModel* pData = (MatchInfoModel*)evt->getUserData();
	c->sendSignUpRequest(pData);
	showLoading();
}

//������������
void GameMatchWidget::toSendunSignUpRequest(EventCustom* evt)
{
	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	//����
	MatchInfoModel* pData = (MatchInfoModel*)evt->getUserData();
	c->sendUnSignUpRequest(pData);
	showLoading();
}


void GameMatchWidget::showLoading()
{
	if (!getChildByTag(COMMON_LOADING_TAG))
	{
		CommonLoadingWidget* loading = CommonLoadingWidget::create(Size(TNVisibleRect::getVisibleRect().size.width, TNVisibleRect::getVisibleRect().size.height));
		loading->setAnchorPoint(Vec2(0.5,0.5));
		loading->setPosition(TNVisibleRect::center());
		addChild(loading, 5);
	}
}

void GameMatchWidget::removeLoading()
{
	if (getChildByTag(COMMON_LOADING_TAG))
	{
		getChildByTag(COMMON_LOADING_TAG)->removeFromParentAndCleanup(false);
	}
}*/