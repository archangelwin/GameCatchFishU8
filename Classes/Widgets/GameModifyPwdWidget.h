#ifndef __GameModifyPwdWidget_H_H_
#define __GameModifyPwdWidget_H_H_

/**
 * @file GameModifyPwdWidget
 * @brief  �޸��û���¼�������
 * @author tjl
 * @date 15-6-24
 */


#include "cocos2d.h"
#include "Common/TNWidget.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MsgDefine/CMD_LogonServer.h"

using namespace cocos2d::ui;
USING_NS_CC;

//��������
enum PwdType
{
	PwdType_Login = 0,
	PwdType_Bank,
	PwdType_MAXCOUNT

};

class GameModifyPwdWidget : public TNWidget
{
public:
	GameModifyPwdWidget();
	~GameModifyPwdWidget();
	virtual bool init(PwdType type);
	void onEnter();
	void onExit();
	std::string getWidgetJsonName();
	void loadUI();
	static GameModifyPwdWidget* create(PwdType type);
	void showLoading();
	void removeLoading();
private:
	void receiveOperateSuccessMsg(EventCustom* evt);
	void receiveOperateFailureMsg(EventCustom* evt);
	void onBack(Ref* pSender,ui::Widget::TouchEventType type);
	void onOk(Ref* pSender,ui::Widget::TouchEventType type);
protected:
	TextField* mOldPwdText;//����
	TextField* mNewPwdText;//����
	TextField* mPwdAgainText;//ȷ������
	PwdType    mType;
	ui::EditBox* mOldPwdEdit;//������
	ui::EditBox* mNewPwdEdit;//������
	ui::EditBox* mEnsureEdit;//����ȷ��
};


#endif//__GameModifyPwdWidget_H_H_