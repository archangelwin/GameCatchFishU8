
#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"
#include "GameBaseScene.h"
#include "MsgDefine/CMD_LogonServer.h"

#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmatureAnimation.h"
#include "cocostudio/CocoStudio.h"

#include "network/HttpRequest.h"
#include "network/HttpClient.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace network;

//������Ϣ
struct updateInfo
{
	//�Ƿ���ʾ����
	bool isShowUpdateTip;
	//����˵��
	std::string strUpdateContent;
	//�������ͣ�1ǿ�Ƹ��£�
	int iUpdateType;
	//���¶���(update:�����ڸ��� toUrl:��תurl����)
	std::string strUpdateAction;
	//url��ַ
	std::string strUpdateUrl;
};



class SplashScene : public GameBaseScene {
public:
	SplashScene();
	~SplashScene();
	CREATE_FUNC(SplashScene);
	virtual bool init(void);
	virtual void onEnter();
	virtual void onExit();
	void loadUI();

	void onAnimationEventOver(Armature *pArmature, MovementEventType movementType, const std::string& movementID);
	void onAnimationEventFrame(Bone *bone, const  std::string& evt, int originFrameIndex, int currentFrameIndex);

	void HttpRequestComplete(HttpClient* client , HttpResponse* response) ;
	void checkUpdate(const char* buf);
	void update(float dt);
protected:
	updateInfo uInfo;
	bool isCheckFinsh;
	__Dictionary* mUpdateInfo;
};

#endif
