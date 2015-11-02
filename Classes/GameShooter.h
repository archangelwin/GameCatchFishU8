//��������
#ifndef _GAME_SHOOTER_H_H_
#define _GAME_SHOOTER_H_H_

#include "cocos2d.h"
#include "GameGlobalSetting.h"
#include "GameAnimation.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class GameShooter : public cocos2d::Layer 
{
public:
	enum SHootGrade
	{
		Grade_100= 0,
		Grade_1000,
		Grade_10000,
		Grade_Max
	};
	GameShooter();
	virtual ~GameShooter();
	static GameShooter* create(WORD myView_chair_id,BulletKind bKind,float angle,DWORD bulletMulriple,bool isMe =false);
	bool init(WORD myView_chair_id,BulletKind bKind,float angle,DWORD bulletMulriple,bool isMe);
	void setAngle(float angle);
	void fire();
	float getAngle() {return mAnger;}
	void dealFire(cocos2d::Node* pNode);//���ſ��𶯻�
	void switchGun(BulletKind kind);//���ڽ��
	BulletKind getKind() const {return mBulletKind;}
	void setScore(SCORE score);
	SCORE getScore() const {return mScore;}
	void addScore(SCORE score,bool coin_effect = false ,bool bingo_effect = false);
	void dealBingoEffect(SCORE score);
	void setBulletMulriple(int power);
	int  getBulletMulriple() const {return mBulletMulriple;}
	void setShootGrade(int roomLevel);//�����ڵĵȼ�
	void setMulripleArea(int min,int max);//�����ڵı���������
protected:
	void removeBingo(Node* pSender);
	void FireDealOver(Node* pSender);
	std::string getResDir();
	void onClickPlus(Ref *pSender, ui::Widget::TouchEventType eventType);
	void onClickSub(Ref *pSender, ui::Widget::TouchEventType eventType);
private:
	WORD mViewChairId;
	float mAnger;//��ǰ�Ƕ�ֵ
	BulletKind mBulletKind;//
	Sprite* mGunSp;//�ڵľ���
	Sprite* mFireSp;//��ľ���
	GameAnimation* mFireAnima;
	LabelAtlas* mScoreLable; //����
	LabelAtlas* mMulripleLable; //�ڵı���
	SCORE  mScore;
	Sprite*  mScoreBg;
	int    mBulletMulriple;
	SHootGrade    mShootGrade;//�ڵĵȼ� 0 ��ʾ���ڷ���1��ʾ ǧ�ڷ� ��2 ��ʾ���ڷ�
	Button*   mBtnPlus;
	Button*  mBtnSub;
	int          mMinMulriple;
	int          mMaxMulriple;

	bool        mIsMatchRoom;
};




#endif //_GAME_SHOOTER_H_H_
