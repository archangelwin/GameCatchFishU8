#include "GameHallAboutWidget.h"
#include "CommonFunction.h"

#define  ImagePopBg 18
#define  BtnColseTag 42
#define  BtnSendGoodTag 55
#define  ImageTabTag 9756

#define  ImageTab1Tag 9758
#define  ImageTab2Tag 9760
#define  ImageTab3Tag 9762

#define bitWidth 115

GameHallAboutWidget::GameHallAboutWidget()
{
	mContentText = nullptr;
	mPageIndex =1;
	m_popBg = nullptr;
}

GameHallAboutWidget::~GameHallAboutWidget()
{

}


bool GameHallAboutWidget::init()
{
	if(!TNWidget::init())
		return false;

	return true;
}

std::string GameHallAboutWidget::getWidgetJsonName()
{
	return "aboutWidget";
}

void GameHallAboutWidget::loadUI()
{
	LayerColor*  shade = LayerColor::create();
	shade->setColor(ccc3(0,0,0));
	shade->setOpacity(180);
	shade->setPosition(Vec2(0,0));
	addChild(shade);

	TNWidget::loadUI();

	m_popBg = static_cast<ImageView*>(m_mainWidget->getChildByTag(ImagePopBg));

	Button* btn_close = static_cast<Button*>(m_popBg->getChildByTag(BtnColseTag));

	btn_close->addTouchEventListener(CC_CALLBACK_2(GameHallAboutWidget::onClose,this));



	//Button* btn_sendGood = static_cast<Button*>(m_popBg->getChildByTag(BtnSendGoodTag));

	//btn_sendGood->addTouchEventListener(CC_CALLBACK_2(GameHallAboutWidget::onSendGood,this));


	ImageView* image_tab = static_cast<ImageView*>(m_popBg->getChildByTag(ImageTabTag));
	image_tab->addTouchEventListener(CC_CALLBACK_2(GameHallAboutWidget::onSwitchPanel,this));

	m_tab1 = static_cast<ImageView*>(m_popBg->getChildByTag(ImageTab1Tag));

	m_tab2 = static_cast<ImageView*>(m_popBg->getChildByTag(ImageTab2Tag));
	m_tab2->setVisible(false);

	m_tab3 = static_cast<ImageView*>(m_popBg->getChildByTag(ImageTab3Tag));
	m_tab3->setVisible(false);

	/*mContentText =  LabelTTF::create(CommonFunction::GBKToUTF8("       �߲�ţ������Ϸ����������Ϊ�����Ҵ�����Ʒ�ʵ�������Ϸ�����Ƶļ���֧�����ۺ����ͨ�����û��ṩ�������Ͷ��˵�����������Ϸ���߼�������Ϸ����ҳ��Ϸ�ȶ�������������Ϸ��Ʒ�����������Ϸ�û����ձ���������\n\
															       ��ƽ̨Ϊ���ģ�������������ƽ̨С��Ϸ���������������ǿ�ҵ�������ɫ�������й��Ļ����̣����ṩ���ߵط���ɫ����Ϸ�����������ĵط����淨���ط��Է��������Լ�������ʤ��������Ϸ���䣬Ϊȫ�����������ṩһ����ص�����ζ����������ƽ̨��"),
																"΢���ź�",25,Size(m_popBg->getContentSize().width - 150,m_popBg->getContentSize().height -170),TextHAlignment::LEFT);
	mContentText->setColor(ccc3(96,34,0));
	mContentText->setAnchorPoint(Vec2(0.5,0.5));
	mContentText->setPosition(Vec2(m_popBg->getContentSize().width/2,m_popBg->getContentSize().height/2));
	m_popBg->addChild(mContentText);
*/
	Label* content = Label::createWithSystemFont(CommonFunction::GBKToUTF8("	�߲�ţ������Ϸ����������Ϊ�����Ҵ�����Ʒ�ʵ�������Ϸ�����Ƶļ���֧�����ۺ����ͨ�����û��ṩ�������Ͷ��˵�����������Ϸ���߼�������Ϸ����ҳ��Ϸ�ȶ�������������Ϸ��Ʒ�����������Ϸ�û����ձ���������\n	��ƽ̨Ϊ���ģ�������������ƽ̨С��Ϸ���������������ǿ�ҵ�������ɫ�������й��Ļ����̣����ṩ���ߵط���ɫ����Ϸ�����������ĵط����淨���ط��Է��������Լ�������ʤ��������Ϸ���䣬Ϊȫ�����������ṩһ����ص�����ζ����������ƽ̨��"),
												"΢���ź�",25,	Size(m_popBg->getContentSize().width - 150,m_popBg->getContentSize().height -170),TextHAlignment::LEFT);
	content->setLineBreakWithoutSpace(true);
	content->setColor(ccc3(96,34,0));
	content->setAnchorPoint(Vec2(0.5,0.5));
	content->setPosition(Vec2(m_popBg->getContentSize().width/2,m_popBg->getContentSize().height/2));
	m_popBg->addChild(content);
}

void GameHallAboutWidget::onClose(Ref* pSender,ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		removeFromParent();
	}
}

void GameHallAboutWidget::onSendGood(Ref* pSender,ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		removeFromParent();
	}
}

void GameHallAboutWidget::onSwitchPanel(Ref* pSender,ui::Widget::TouchEventType type)
{

	Vec2 touchPos;
	int index =0;
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		ImageView* pBit = (ImageView*)pSender;

		touchPos = pBit->getTouchEndPosition();
		Vec2 pos = pBit->getWorldPosition();
		Vec2 wordPos = convertToWorldSpace(touchPos);
		Vec2 delta ;
		Vec2::subtract(wordPos,pos,&delta);
		if ( (-1*bitWidth< delta.x &&delta.x < 0) || (delta.x <= bitWidth && delta.x > 0))
		{
			index = 2;
		}
		else if ( delta.x < -1*bitWidth)
		{
			index = 1;
		}
		else if (bitWidth< delta.x  )
		{
			index = 3;
		}

		if (mPageIndex != index)//�л��ı�����
		{
			mPageIndex = index;
			changeText();
			
		}
	}
}

void GameHallAboutWidget::changeText()
{
	switch (mPageIndex)
	{
	case 1:
		{
			mContentText->setString(CommonFunction::GBKToUTF8("����Э���ۿණ������ ����ԭ�����ԭ�����ԭ���ɶ��칤Ҫ���ɶ��칤����ԭ�����"));
			m_tab1->setVisible(true);
			m_tab2->setVisible(false);
			m_tab3->setVisible(false);
		}
		break;
	case 2:
		{
			mContentText->setString(CommonFunction::GBKToUTF8("��˽�����ۿණ������ ����ԭ�����ԭ�����ԭ���ɶ��칤Ҫ���ɶ��칤����ԭ�����"));
			m_tab1->setVisible(false);
			m_tab2->setVisible(true);
			m_tab3->setVisible(false);
		}
		break;
	case 3:
		{
			mContentText->setString(CommonFunction::GBKToUTF8("��������ۿණ������ ����ԭ�����ԭ�����ԭ���ɶ��칤Ҫ���ɶ��칤����ԭ�����"));
			m_tab1->setVisible(false);
			m_tab2->setVisible(false);
			m_tab3->setVisible(true);
		}
		break;
	}
}