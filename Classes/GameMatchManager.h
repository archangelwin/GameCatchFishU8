
#ifndef GAME_MATHC_MANAGER_H_
#define GAME_MATHC_MANAGER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Model/MatchModel.h"
#include "GameGlobalSetting.h"
class GameScene;

using namespace ui;
USING_NS_CC;
USING_NS_CC_EXT;

enum enMatchStatus
{
	MG_NULL_STATUS=0,		//��״̬
	MG_SIGNUPING,			//������
	MG_MATCHING,			//û������Ԥ�� �ȴ�����
};

class GameMatchManager : public Node
{
 public:
  GameMatchManager();
  ~GameMatchManager();
  void onEnter();
  void onExit();
  bool init(GameScene* pDelegate);
  static GameMatchManager* create(GameScene* pDelegate);
  void updateMatchRoom(float dt);
 private:
	GameScene* mDelegate;
	Node*            mTimeNode;//����ʱ
	Node*            mTimeMatchNode; //��ʱ����Ϣ�ڵ�
	Node*            mForeverMatchNode;//ѭ������Ϣ�ڵ�
	GameMatchModel* mData;

	Text*            mRankText;
	Text*            mCurScoreText;
	Text*            mMaxScoreText;
	Text*            mTotalScoreText;
	Text*            mPalyCountText;
	Text*            mMatchTimeText;

	ImageView*  mStartOrEnd;
	LabelAtlas*   mStartOrEndTimeLable;
	LabelAtlas*   mRedTimeLable;
	SCORE           mTimeSpan;
};

#endif // COIN_MANAGER_H_
