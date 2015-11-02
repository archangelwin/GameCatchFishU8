/**
 * @file GameHallBuyAlertWidget
 * @brief  ��Ϸ�������򣬶һ�����ȷ�Ͽ�
 * @author tjl
 * @date 15-7-3
 */

#ifndef _GameHallBuyAlertWidget_H_H_
#define _GameHallBuyAlertWidget_H_H_

#include "cocos2d.h"
#include "Common/TNWidget.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MsgDefine/CMD_LogonServer.h"
#include "Model/GiftModel.h"


#define KnapsackTypeUse 2//ʹ��
#define KnapsackTypeCovert 3//�һ�
#define KnapsackTypeUserQQ 6 //Q��
#define knapsackTypeUserPhone 5//����

using namespace cocos2d::ui;
USING_NS_CC;

enum proType //��Ʒ����
{
	proType_shop = 0,//���̳ǵ������
	proType_bag,//�ӱ����������
	proType_Auction,//�������������
	proType_MaxCount

};

class GameHallBuyAlertWidget : public TNWidget,public ui::EditBoxDelegate
{
public:
	GameHallBuyAlertWidget();
	~GameHallBuyAlertWidget();
	virtual bool init(proType type,GiftModel* info);
	bool initWithDic(proType type,__Dictionary* info);
	void onEnter();
	void onExit();
	std::string getWidgetJsonName();
	void loadUI();
	static GameHallBuyAlertWidget* create(proType type,GiftModel* info);
	static GameHallBuyAlertWidget* createWithDic(proType type,__Dictionary* info);
	void showLoading();
	void removeLoading();

	//---------------------------------��ӱ༭��  
	virtual void editBoxEditingDidBegin(ui::EditBox* editBox);  
	virtual void editBoxEditingDidEnd(ui::EditBox* editBox);  
	virtual void editBoxTextChanged(ui::EditBox* editBox,const std::string &text);  
	virtual void editBoxReturn(ui::EditBox *editBox);  

protected:
	void onBack(Ref* pSender,ui::Widget::TouchEventType eventtype); 
	void onOK(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onGotoVip(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickMax(Ref* pSender,ui::Widget::TouchEventType eventtype);
private:
	Layout* mShopPanel;
	Layout* mBagPanel;
	Layout* mPhonePanel;
	Layout* mQQPanle;
	Layout* mAuctionPanel;
	Text*   mProTitle;//��Ʒ����
	Text*   mShopProCost;//�̳������Ʒ�۸�
	GiftModel* mData;
	ImageView*  mOkImage;
	ui::EditBox* mShopInputEdit;//�̳������������
	proType mProType;
	ui::EditBox* mQQEdit;//qq����
	ui::EditBox* mPhoneEdit;//�ֻ�����
	ui::EditBox* mBagCovertEdit;//����ת������
	Text* mBagDesc;//�����һ�����

	//�������
	__Dictionary* mInfoDic;
	ui::EditBox*  mAuctionEdit;
	Text*         mAuctionCost;

	int           mSingleCost;
protected:

};




#endif //_GameHallBuyAlertWidget_H_H_