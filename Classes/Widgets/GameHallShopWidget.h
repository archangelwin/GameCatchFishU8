/**
 * @file GameHallShopWidget
 * @brief  ��Ϸ����SHOP����
 * @author tjl
 * @date 15-5-29
 */

#include "cocos2d.h"
#include "Common/TNWidget.h"

USING_NS_CC;

class GameHallShopWidget :public TNWidget
{
public:
	GameHallShopWidget();
	~GameHallShopWidget();
	virtual bool init();
	CREATE_FUNC(GameHallShopWidget);
	virtual std::string getWidgetJsonName();

	void onEnter();
	void onExit();

	virtual void loadUI();
protected:
	void showLoading();
	void removeLoading();
	void refreshGiftList(EventCustom* event);
	void refreshTreasure(EventCustom* evt);
	void onClickGift(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickTool(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickVip(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onBack(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickBag(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void refreshData(int type);
	void refreashList(__Array* pArray,int type);
	void sendUserGiftRequset(EventCustom* evt);
	void receiveBuyGiftRsp(EventCustom* evt);
private:
	int		  mPageIndex;//��ǰҳ������
	ImageView*  mTabGift;
	ImageView*  mTabTool;
	ImageView*  mTabVip;
	ImageView*  mTextGift;
	ImageView*  mTextTool;
	ImageView*  mTextVip;
	ListView*   mToolList;

	Text*      mInsureText;//���д��
	Text*      mIngotText;//Ԫ��
	Text*      mLotteryText;//��ȯ
};
