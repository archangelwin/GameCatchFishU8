/**
 * @file GameJettonManager
 * @brief  ��Ϸ�еĳ��������
 * @author tjl
 * @date 15-6-3
 */
#include "cocos2d.h"
#include "GameGlobalSetting.h"
#include "Widgets/GameJettonWidget.h"
USING_NS_CC;


class GameJettonManager : public Ref
{
public:
	GameJettonManager();
	~GameJettonManager();
	static GameJettonManager* shareInstance();
	virtual void purgeInstance();

	void addJetton(int view_chair_id,SCORE score);//��ӳ���
	void movJetton(int view_chair_id);//�ƶ�����

	void Update(float delta_time);
	void Render();

protected:
	Vec2 GetJettonPos(WORD chair_id, size_t size);
	__Array* jettonArray[GAME_PLAYER];
	Sprite* mJetton;

};