#include "CommonFunction.h"
#include "U8sdkFunction.h"
#include "cocostudio/CCSGUIReader.h"
#include "Message.h"
#include "GameServiceClientManager.h"
#include "SessionManager.h"
#include "LoginScene.h"

CU8sdkFunction::CU8sdkFunction()
{
}


CU8sdkFunction::~CU8sdkFunction()
{
}


void CU8sdkFunction::OnInitSuc()
{
	//һ�㲻��Ҫ��ʲô����
}

void CU8sdkFunction::OnLoginSuc(U8LoginResult* result)
{
	log("SDK��¼����֤�ɹ�...%s", result->userId.c_str());
	//this->labelUsername->setString(result->sdkUsername);

	if (result->isSwitchAccount)
	{
		//TODO:�����˻ص���¼���棬����SDK���Ѿ���¼�ɹ�״̬�������ٵ���SDK�ĵ�¼����
		log("U8----result->isSwitchAccount");
	}
	else
	{
		//TODO:��¼��֤�ɹ�����ȡ�������б�������Ϸ��...
		log("U8----loginresult");
		std::string umid = result->sdkUserId;
		std::string username = result->sdkUsername;
		std::string token = result->token;
		std::string userid = result->userId;
		channelID = result->channelID.c_str();

		log("channelID = %s", channelID.c_str());
		log("umid = %s", umid.c_str());
		log("username = %s", username.c_str());
		log("token = %s", token.c_str());

		__Dictionary*  dic = __Dictionary::create();
		dic->setObject(__String::create(umid), "umid");
		dic->setObject(__String::create(username), "username");
		dic->setObject(__String::create(token), "token");
		dic->setObject(__String::create(userid), "userid");
		Director::sharedDirector()->getEventDispatcher()->dispatchCustomEvent(u8LoginMsg, dic);
	}
}

void CU8sdkFunction::OnSwitchLogin()
{
	std::string name = GameServiceClientManager::sharedInstance()->getCurrentServiceClientName();
	GameServiceClientManager::sharedInstance()->removeServiceClient(name.c_str());
	SessionManager::shareInstance()->clearMsgArray();
	SessionManager::shareInstance()->clearHornMsg();
	//�Ͽ�����SORKET
	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	c->closeSoket();

	LoginUserModel *userModel = SessionManager::shareInstance()->getLoginModel();
	//�ϴ���QQ ��¼���л��ʺź���ջ�����ʺŵ���Ϣ
	if (userModel->getAccountType() == accountType::accountQQ)
	{
		userModel->setAccount("");
		userModel->setPassword("");
	}
	//removeFromParent();
	Director::sharedDirector()->replaceScene(LoginScene::create());

	U8SDKInterface::getInstance()->login();
}

void CU8sdkFunction::OnLogout()
{
	CCLOG("SDK�ʺ��˳��ɹ�...");
	//this->labelUsername->setString("U8SDK");
	//TODO:�˻ص���¼���棬������SDK��¼����(����U8SDKInterface::getInstance()->login())
	std::string name = GameServiceClientManager::sharedInstance()->getCurrentServiceClientName();
	GameServiceClientManager::sharedInstance()->removeServiceClient(name.c_str());
	SessionManager::shareInstance()->clearMsgArray();
	SessionManager::shareInstance()->clearHornMsg();
	//�Ͽ�����SORKET
	GameServiceClient* c = GameServiceClientManager::sharedInstance()->serviceClientForName(taskClient);
	c->closeSoket();

	LoginUserModel *userModel = SessionManager::shareInstance()->getLoginModel();
	//�ϴ���QQ ��¼���л��ʺź���ջ�����ʺŵ���Ϣ
	if (userModel->getAccountType() == accountType::accountQQ)
	{
		userModel->setAccount("");
		userModel->setPassword("");
	}
	//removeFromParent();
	Director::sharedDirector()->replaceScene(LoginScene::create());

	U8SDKInterface::getInstance()->login();
}

void CU8sdkFunction::OnU8sdkInit()
{
	log("SDKinit�ɹ�...111");
	U8SDKInterface::getInstance()->initSDK(this);
}

void CU8sdkFunction::OnU8sdkLogin()
{
	log("OnU8sdkLogin");
	U8SDKInterface::getInstance()->login();
}

std::string CU8sdkFunction::OnGetChannelid()
{
	std::string channelid = U8SDKInterface::getInstance()->getchannelId();
	channelID = channelid;
	log("OnU8sdkLogin%s", channelid.c_str());

	return channelid;
}

void CU8sdkFunction::OnU8sdkPay(std::string strName, std::string strDesc, int price, std::string tradeNo)
{
	U8PayParams* params = U8PayParams::create();

	params->productId = "1";
	params->productName = strName;
	params->productDesc = strDesc;
	params->price = price;
	params->buyNum = 1;
	params->coinNum = 0;
	params->serverId = "1";
	params->serverName = "";
	params->roleId = tradeNo;
	params->roleName = "";
	params->roleLevel = 0;
	params->vip = "";

	//ȥ��������ȡ��Ϸ����Ʒ�Ķ������Լ���չ����,�������
	params->orderID = tradeNo;
	params->extension = "";

	log("CU8sdkFunction::OnU8sdkPay productName==%s,productDesc==%s,price==%d,orderID==%s",params->productName.c_str()
		, params->productDesc.c_str()
		,params->price
		,params->orderID.c_str());

	U8SDKInterface::getInstance()->pay(params);
}