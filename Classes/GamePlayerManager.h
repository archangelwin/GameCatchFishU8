#ifndef _GAME_PLAYER_MANAGER_H_H_
#define _GAME_PLAYER_MANAGER_H_H_

#include "cocos2d.h"
#include "GameGlobalSetting.h"
#include "GameShooter.h"

class GameScene;
class  GamePlayer : public Ref{
public:
	  GamePlayer();
	~ GamePlayer();

	static GamePlayer* create();
	bool init();
	void setShooter(GameShooter* pShooter);
	GameShooter* getShooter() const {return mShooter;}
	void setAngle(float angle);
	float getAngle();
	int   getChairID() const {return mChairId;}
	void  setChairID(int id) {mChairId = id;}
	void  switchGun(BulletKind kind);
	void  fire();//����
	void  setBulletMulriple(int power);//�ֵ��ı���
	int   getBulletMulriple();
	void  exchangeScore(SCORE score);
	void  AddScore(SCORE score,bool coin_effect,bool bingo_effect);
	bool  getInitUIFalg() const {return m_bInitUI;}
	void  setInitUIFalg(bool flag) { m_bInitUI = flag;}
private:
	int mChairId;//����ID
	BulletKind mBulletKind;//�ӵ�����
	GameShooter* mShooter;//��������
	float mTurrentAngle;//�ڵ���ת�Ƕȣ�����ֵ��
	int   mBulletMulriple;//����ӵ��ı���
	bool  m_bInitUI;// for enter a room with player, wait for ��������������ȥ��ʼ��������ҵ�UI
};


class GamePlayerManager : public Ref
{
public:
	GamePlayerManager();
	~GamePlayerManager();
	static GamePlayerManager* create(GameScene* pScene);
	bool init(GameScene* pScene);
	void addPlayer(int chairId);
	void removePlayer(int chairId);
	void fire(int chairId);
	bool playerIsExist(int chairId);
	GamePlayer* getPlayerByChairId(int chairId);
	void exchangeScore(int chairId ,SCORE score);
	void AddScore(int chairId, SCORE score, bool coin_effect, bool bingo_effect);
	void isAllPalyersIsOnSit();//����Ƿ����е���Ҷ��ѳ�ʼ��UI
private:
	//std::map<int, GamePlayer* > mPlayerMap;
	__Array* mPlayers;
	GameScene* mGameScene;
};















#endif//_GAME_PLAYER_MANAGER_H_H_