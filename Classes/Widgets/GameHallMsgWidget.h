/**
 * @file GameHallMsgWidget
 * @brief  ��Ϸ������Ϣ����
 * @author tjl
 * @date 15-5-31
 */

#include "cocos2d.h"
#include "Common/TNWidget.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
USING_NS_CC;

class GameHallMsgWidget :public TNWidget
{
public:
	GameHallMsgWidget();
	~GameHallMsgWidget();
	virtual bool init();
	CREATE_FUNC(GameHallMsgWidget);
	virtual std::string getWidgetJsonName();

	void onEnter();
	void onExit();

	virtual void loadUI();
protected:
	void showLoading();
	void removeLoading();
	void refreshMsgList(EventCustom* event);
	void onClickSystem(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickPrivate(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onBack(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickItem(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void refreshData(int type);
	int calMsgCountByType(__Array* pArray,int type);
private:
	ListView* mMsgList;//��Ϣ�б�
	int		  mPageIndex;//��ǰҳ������
	ImageView*  mTabSystem;//ϵͳ�б�
	ImageView*  mTabPrivate;
	ImageView*  mTextSystem;
	ImageView*  mTextPrivate;
};
