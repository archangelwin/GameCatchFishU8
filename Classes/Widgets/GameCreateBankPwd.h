#ifndef __GameBankCreatePwd_H_H_
#define __GameBankCreatePwd_H_H_

/**
 * @file GameBankCreatePwd
 * @brief  ��Ϸ�������������������
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

class GameBankCreatePwdWidget : public TNWidget
{
public:
	GameBankCreatePwdWidget();
	~GameBankCreatePwdWidget();
	virtual bool init();
	void onEnter();
	void onExit();
	std::string getWidgetJsonName();
	void loadUI();
	CREATE_FUNC(GameBankCreatePwdWidget);
	void showLoading();
	void removeLoading();
private:
	void receiveOperateSuccessMsg(EventCustom* evt);
	void receiveOperateFailureMsg(EventCustom* evt);
	void onBack(Ref* pSender,ui::Widget::TouchEventType type);
	void onCreate(Ref* pSender,ui::Widget::TouchEventType type);
protected:
	TextField* mPwdText;//����
	TextField* mPwdAgainText;//ȷ������
	ui::EditBox* mPwdEdit;
	ui::EditBox* mEnsurePwdEdit;
};


#endif//__GameBankCreatePwd_H_H_