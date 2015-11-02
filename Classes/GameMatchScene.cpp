#include "GameServiceClientManager.h"
#include "Model/LoginUserModel.h"
#include "SessionManager.h"
#include "GameMatchScene.h"
#include "Common/AlertWidget.h"
#include "CommonFunction.h"
#include "Common/ModalViewManager.h"
#include "Common/CommonLoadingWidget.h"
#include "MsgDefine/CMD_GameServer.h"
#include "MsgDefine/CMD_LogonServer.h"
#include "GameScene.h"
#include "GameMainScene.h"
#include "Message.h"
#include "SoundManager.h"
#include "Common/TNVisibleRect.h"
#include "Widgets/GameMatchWidget.h"
#include "Widgets/GameBindPhoneWidget.h"
#include "LoginScene.h"

#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmatureAnimation.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;

#define  imageBgTag 42
#define  ListViewBgTag 12548
#define ListViewTag  12488


GameMatchScene::GameMatchScene()
{
	mNeedBind = false;
	mbContinueMatch = false;
	mShowWait = false;
}

GameMatchScene::~GameMatchScene()
{
}

 GameMatchScene* GameMatchScene::create(bool isBcontinue)
{
	GameMatchScene* pScene = new GameMatchScene();
	if (pScene && pScene->init(isBcontinue))
	{
		pScene->autorelease();
		return pScene;
	}
	else
	{
		delete pScene;
		pScene = nullptr;
		return nullptr;
	}
}

bool GameMatchScene::init(bool isBcontinue)
{
	if (!GameBaseScene::init()) {
		return false;
	}
	mbContinueMatch = isBcontinue;
	return true;
}

void GameMatchScene::onEnter()
{
	GameBaseScene::onEnter();
	SoundManager::playMusicBackground("room_bgmusic.m4a",true);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(deleteMatchRoomMsg, CC_CALLBACK_1(GameMatchScene::DeleteMatchRoomMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(refreshMatchListMsg, CC_CALLBACK_1(GameMatchScene::receiveMatchRoomListMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(updateRoomSignUpPlayersMsg, CC_CALLBACK_1(GameMatchScene::updateRoomInfoMsg, this)), this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(signUpSuccessMsg, CC_CALLBACK_1(GameMatchScene::receiveSignUpSuccessMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(signUpFaildMsg, CC_CALLBACK_1(GameMatchScene::receiveSignUpFaildMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(unSignUpSuccessMsg, CC_CALLBACK_1(GameMatchScene::receiveUnSignUpSuccessMsg, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(unSignUpFaildMsg, CC_CALLBACK_1(GameMatchScene::receiveUnSignUpFaildMsg, this)), this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(matchCountDownMsg, CC_CALLBACK_1(GameMatchScene::receiveMatchCountDownMsg, this)), this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(toSignUpNotice, CC_CALLBACK_1(GameMatchScene::toSendSignUpRequest, this)), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(tounSignUpNotice, CC_CALLBACK_1(GameMatchScene::toSendunSignUpRequest, this)), this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(MatchPlayCountIsMaxMsg, CC_CALLBACK_1(GameMatchScene::ReceiveMatchPlayCountIsMaxMsg, this)), this);
	
	//�����Ͽ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(TaskSorketCloseMsg,CC_CALLBACK_1(GameMatchScene::taskSorketConnetFail,this)),this);
	//��ʱ��ÿ����ˢ�±�������
	schedule(schedule_selector(GameMatchScene::updateSignUpPlayers),3.0);

	loadUI();

	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	if(!c->isConnect())
	{
		SessionManager::shareInstance()->clearMatchRooms();
		//���µ�¼
		c->loginTaskServer();
	}

}

//����������ɺ󣬼���Ƿ�Ҫ��������
void GameMatchScene::onEnterTransitionDidFinish()
{
	if (mbContinueMatch)
	{
		//�ձ�������ǳ�������Ϣ
		MatchSerialModel* pCurRoomSerial = SessionManager::shareInstance()->getRoomSerial();
		//ͨ��SORT ID �ҵ��³�������Ϣ������
		__Array* matchRooms = SessionManager::shareInstance()->getMatchRooms();
		GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
		for (int i = 0 ; i < matchRooms->count();i++)
		{
			MatchInfoModel* pMatchInfo = (MatchInfoModel*)matchRooms->getObjectAtIndex(i);
			if (pMatchInfo->getSerialModel()->getSortId() == pCurRoomSerial->getSortId())
			{
				log("sign room matine id %lld",pMatchInfo->getSerialModel()->getMatchInfoID());
				c->sendSignUpRequest(pMatchInfo);
				showLoading();
				break;
			}
		}
	}

	if (mShowWait)
	{
		showLoading();
		((CommonLoadingWidget*)getChildByTag(COMMON_LOADING_TAG))->setTips(CommonFunction::GBKToUTF8("���ڽ���������䣬���Ժ�..."));
		Director::sharedDirector()->getEventDispatcher()->dispatchCustomEvent(EnterMatchRoomMsg);
	}
}

void GameMatchScene::updateSignUpPlayers(float dt)
{
	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	c->sendRefrshMatchPlayers();
}

void GameMatchScene::onExit()
{
	_eventDispatcher->resumeEventListenersForTarget(this);
	unschedule(schedule_selector(GameMatchScene::updateSignUpPlayers));
	GameBaseScene::onExit();	
}

char* GameMatchScene::getWidgetJsonName()
{
	return "matchWiget";
}

void GameMatchScene::loadUI()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ؽ���
	m_mainWidget = CommonFunction::getWidgetFromCocostudioFile(getWidgetJsonName());
	m_mainWidget->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	m_mainWidget->setAnchorPoint(Vec2(0.5,0.5));
	addChild(m_mainWidget);

	ArmatureDataManager::getInstance()->addArmatureFileInfo("Splash/AnimationTitleLogon.ExportJson");  
	Armature* armature = Armature::create("AnimationTitleLogon");
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->setPosition(Vec2(kScreenWidth/2, kScreenHeight- 60));
	armature->getAnimation()->play("Animation1",1.5f,1);
	this->addChild(armature);

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
	ImageView* imageBack = ImageView::create();
	imageBack->setTouchEnabled(true);
	imageBack->loadTexture("back.png");
	imageBack->setPosition(Vec2( imageBack->getContentSize().width/2 + 50, kScreenHeight - imageBack->getContentSize().height/2 - 50));
	imageBack->setTouchSize(Size(100,100));
	addChild(imageBack);

	Sprite* qipaoSp = Sprite::create();
	qipaoSp->setPosition(Vec2(35,30));
	imageBack->addChild(qipaoSp);
	std::vector<std::string> imageNames;
	std::string path = "";
	for (int i = 0 ; i < 6;i++)
	{
		if (i < 4)
			path = "qipao"+numberToString(i+1)+".png";
		else
			path = "qipao"+numberToString(4-i%3)+".png";

		imageNames.push_back(path);
	}

	Animate* pAnima = CommonFunction::createFrameAnimate(imageNames,0.2);
	qipaoSp->runAction(RepeatForever::create(pAnima));

	imageBack->addTouchEventListener(CC_CALLBACK_2(GameMatchScene::onClickBack,this));

}

void GameMatchScene::onClickBack(Ref* pSender,ui::Widget::TouchEventType type)
{
	if(type == ui::Widget::TouchEventType::BEGAN)
	{
		playScaleAnimation(true,pSender);
	}
	else
	{
		playScaleAnimation(false,pSender);

	}
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		Director::sharedDirector()->replaceScene(MainScene::create());
	}
}



void GameMatchScene::DeleteMatchRoomMsg(EventCustom* evt)
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

int GameMatchScene::getMatchRoomCountByType(int type)
{
	int cnt = 0;
	Vector<Widget*> roomItems = mMatchList->getItems();
	for (int i = 0 ; i < roomItems.capacity();i++)
	{
		GameMatchItem* pMatchItem = (GameMatchItem*)roomItems.at(i);
		if (pMatchItem->isRoot())//��������
			continue;
		MatchInfoModel* pData = pMatchItem->getMatchInfo();
		if (pData->getSerialModel()->getMatchType() == type)//�ҵ�ͬ���͵�
		{
			cnt++;
		}
	}
	return cnt;
}

void GameMatchScene::receiveMatchRoomListMsg(EventCustom* evt)
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

	//to do���������
	if (isNewMatch && isLastItemFlag)
	{
		int roomType =  pModel->getSerialModel()->getMatchType();
		int cnt = getMatchRoomCountByType(roomType);
		for (int i = 0 ; i < roomItems.capacity();i++)
		{
			GameMatchItem* pMatchItem = (GameMatchItem*)roomItems.at(i);
			if (pMatchItem->isRoot() && pMatchItem->getMatchType() == roomType )//��������
			{
				pMatchItem = GameMatchItem::create(false,pModel);
				mMatchList->insertCustomItem(pMatchItem,cnt+i);
			}
		}
	}
}


//ˢ�·�����Ϣ
void GameMatchScene::updateRoomInfoMsg(EventCustom* evt)
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
void GameMatchScene::receiveSignUpSuccessMsg(EventCustom* evt)
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
void GameMatchScene::receiveSignUpFaildMsg(EventCustom* evt)
{
	removeLoading();
	CMD_GL_SignUpFailure * pOperateFailure=(CMD_GL_SignUpFailure *)evt->getUserData();
	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(this,"",CommonFunction::GBKToUTF8(pOperateFailure->szDescribeString)));
	if (pOperateFailure->lResultCode ==2)//����ֻ�
	{
		mNeedBind = true;
	}
}

void GameMatchScene::okCallback()
{
	if (mNeedBind)
	{
		ModalViewManager::sharedInstance()->showWidget(GameBindPhoneWidget::create());
	}
	if (bNeedRelogin)
	{
		GameServiceClientManager::sharedInstance()->removeServiceClient(taskClient);
		ModalViewManager::sharedInstance()->removeAllWidgets();
		SessionManager::shareInstance()->setInGame(false);
		Director::sharedDirector()->replaceScene(LoginScene::create());
	}

}
//�����ɹ����ش���
void GameMatchScene::receiveUnSignUpSuccessMsg(EventCustom* evt)
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
void GameMatchScene::receiveUnSignUpFaildMsg(EventCustom* evt)
{
	removeLoading();
	CMD_GL_SignUpFailure * pOperateFailure=(CMD_GL_SignUpFailure *)evt->getUserData();
	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(nullptr,"",CommonFunction::GBKToUTF8(pOperateFailure->szDescribeString)));
}

////������ʼ���ش���
//void GameMatchScene::receiveMatchStartMsg(EventCustom* evt)
//{
//	removeLoading();
//	if (SessionManager::shareInstance()->isInGame())
//	{
//
//	}
//	else
//	{
//		CMD_GL_MatchServer * pMatchServer =(CMD_GL_MatchServer *)evt->getUserData();
//		//����SORKET
//		createGameSorket();
//		//���ӷ�����
//		connectGameServer(pMatchServer->szServerIP,pMatchServer->dwServerPort);
//	}
//}



//����ʱ���ش���
void GameMatchScene::receiveMatchCountDownMsg(EventCustom* evt)
{

}

//���ͱ�������
void GameMatchScene::toSendSignUpRequest(EventCustom* evt)
{
	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	//����
	MatchInfoModel* pData = (MatchInfoModel*)evt->getUserData();
	c->sendSignUpRequest(pData);
	showLoading();
}

//������������
void GameMatchScene::toSendunSignUpRequest(EventCustom* evt)
{
	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	//����
	MatchInfoModel* pData = (MatchInfoModel*)evt->getUserData();
	c->sendUnSignUpRequest(pData);
	showLoading();
}


void GameMatchScene::showLoading()
{
	if (!getChildByTag(COMMON_LOADING_TAG))
	{
		CommonLoadingWidget* loading = CommonLoadingWidget::create(Size(TNVisibleRect::getVisibleRect().size.width, TNVisibleRect::getVisibleRect().size.height));
		loading->setAnchorPoint(Vec2(0.5,0.5));
		loading->setPosition(TNVisibleRect::center());
		addChild(loading, 5);
	}
}

void GameMatchScene::removeLoading()
{
	if (getChildByTag(COMMON_LOADING_TAG))
	{
		getChildByTag(COMMON_LOADING_TAG)->removeFromParentAndCleanup(false);
	}
}

void GameMatchScene::playScaleAnimation(bool less, Ref* pSender) {
	float scale = less ? 0.9f : 1.0f;
	CCScaleTo *scaleTo = CCScaleTo::create(0.2f, scale);
	Node* pNode = (Node*)pSender;
	pNode->runAction(scaleTo);
}

void GameMatchScene::ReceiveMatchPlayCountIsMaxMsg(EventCustom* evt)
{
	removeLoading();
	//�Ͽ���ϷSOKET
	GameServiceClientManager *m = GameServiceClientManager::sharedInstance();
	GameServiceClient* c = m->serviceClientForName(XwZoneDntg);
	if(c)
	{
		GameServiceClientManager::sharedInstance()->removeServiceClient(XwZoneDntg);
	}
	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(nullptr,"",CommonFunction::GBKToUTF8("������Ϸ�����Ѵﵽ���ޣ���ȴ���������������������")));
}

void GameMatchScene::taskSorketConnetFail(EventCustom* evt)
{
	//����б�
	mMatchList->removeAllItems();
	ModalViewManager::sharedInstance()->showWidget(AlertWidget::create(this,"",CommonFunction::GBKToUTF8("���������ж�,������!")));
}




