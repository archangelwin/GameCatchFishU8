/**
 * @file GameHallAboutWidget
 * @brief  ��Ϸ�������ڽ���
 * @author tjl
 * @date 15-8-3
 */

#ifndef _GameHallAboutWidget_H_H_
#define _GameHallAboutWidget_H_H_


#include "cocos2d.h"
#include "Common/TNWidget.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
USING_NS_CC;


class GameHallAboutWidget : public TNWidget
{
public:
	GameHallAboutWidget();
	~GameHallAboutWidget();
	virtual bool init();
	std::string getWidgetJsonName();
	void loadUI();
	CREATE_FUNC(GameHallAboutWidget);
private:
	
	void onClose(Ref* pSender,ui::Widget::TouchEventType type);
	void onSendGood(Ref* pSender,ui::Widget::TouchEventType type);//���͸�������

	void onSwitchPanel(Ref* pSender,ui::Widget::TouchEventType type);//�л�����

	void changeText();
protected:
	int mPageIndex;
	LabelTTF* mContentText;
	ImageView* m_popBg;
	ImageView* m_tab1;
	ImageView* m_tab2;
	ImageView* m_tab3;
};








#endif //_GameHallAboutWidget_H_H_
