/**
 * @file GameHallPaimaiWidget
 * @brief  ��Ϸ������Ϣ����
 * @author tjl
 * @date 15-5-31
 */

#include "cocos2d.h"
#include "Common/TNWidget.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Widgets/GameHallPaimaiItem.h"
#include "Common/AlertWidget.h"

using namespace cocos2d::ui;
USING_NS_CC;

enum BankDataType
{
	typePaiMaiInfo = 0,//����������Ϣ
	typeMyPaiMai,//�ҵ�������Ϣ
	typePaiMaiRecord,//������¼
	typeAuctionList,//�ϼ���Ʒ�б�
	TypeMaxCount
};

class  GameHallPaimaiWidget : public TNWidget,public ui::EditBoxDelegate,public AlertDelegate
{
public:
	GameHallPaimaiWidget();
	~GameHallPaimaiWidget();

	virtual bool init();
	CREATE_FUNC(GameHallPaimaiWidget);

	std::string getWidgetJsonName();
	void onEnter();
	void onExit();

	virtual void loadUI();
	void refreshData(BankDataType dataType,bool isMore = true);
	void showLoading();
	void removeLoading();

	//---------------------------------��ӱ༭��  
	virtual void editBoxEditingDidBegin(ui::EditBox* editBox);  
	virtual void editBoxEditingDidEnd(ui::EditBox* editBox);  
	virtual void editBoxTextChanged(ui::EditBox* editBox,const std::string &text);  
	virtual void editBoxReturn(ui::EditBox *editBox);  

	//��ʾ��ص�
	virtual void okCallback();
protected:
	void refreshAuctionList(EventCustom* evt);//ˢ������������Ϣ�б�
	void refreshMyAuctionList(EventCustom* evt);//ˢ���ҵ������б�
	void refreshAuctionHistoryList(EventCustom* evt);//ˢ��������¼�б�
	void refreshAuctionItemList(EventCustom* evt);//ˢ���ϼ���Ʒ�б�

	void receiveSellAuctionResult(EventCustom* evt);
	void receiveBuyAuctionResult(EventCustom* evt);
	void receiveCancelAuctionResult(EventCustom* evt);
	//��ȡ�Ƹ����ش���
	void receiveTreasureInfoMsg(EventCustom* evt);
	//��ȡ�������÷��ش���
	void receiveCoverAuctionScoreMsg(EventCustom* evt);
	//���͹�������Ʒ����
	void sendBuyAuctionRequset(EventCustom* evt);

	void onBack(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onPaimai(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onMybag(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onTakeOut(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onSearch(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickPaimaiRecord(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickMyRecord(Ref* pSender,ui::Widget::TouchEventType eventtype);
	void onClickHistory(Ref* pSender,ui::Widget::TouchEventType eventtype);
	//����ϼ���Ʒ��
	void onClickSellItem(Ref* pSender,ui::Widget::TouchEventType eventtype);

	void refreshSellData(__Dictionary*data);

	void onListViewScroll(Ref* pSender,ScrollviewEventType type);
protected:
	int mAuctionPageIndex;//��¼��ǰ������Ϣ�����ҳ��
	int mAuctionTotal;
	int mMyAuctionTotal;
	int mHistoryTotal;
	int mMyAuctionPageIndex;
	int mAuctionHistoryIndex;
	ListView* mPaimaiList;
	ListView* mAuctionItemList;
	Text*   mSellItemName;
	TextField*   mSellItemCount;
	ui::EditBox* mAccountEdit;//��������
	TextField*   mSellItemCost;
	ui::EditBox* mCoseEdit;//��������
	ImageView*   mSearchTextBg;
	TextField*   mSearchText;
	ui::EditBox* mSearchEdit;//��������
	Button*      mSearchBtn;
	Text*   mLablePaiGet;//��������
	Text*   mLableBank;//����Ԫ����
	Text*   mLableGold;//����Ԫ��

	Layout*  mTitlePanleInfo;
	Layout*  mTitlePanleMy;
	Layout*  mTitlePanleHistory;

	ImageView*  mTabInfo;
	ImageView*  mTabMy;
	ImageView*  mTabHistory;

	ImageView*  mTextInfo;
	ImageView*  mTextMy;
	ImageView*  mTextHistory;

	int   mPageIndex;
	int   mSearchPageIndex;
	int   mSearchTotal;
	bool  mBSearch;
	GameHallPaimaiSellItem* mCurSelectItem;

};