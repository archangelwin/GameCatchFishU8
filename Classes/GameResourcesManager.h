#ifndef _GAME_RESOURCES_MANAGER_H_H_
#define _GAME_RESOURCES_MANAGER_H_H_

#include "cocos2d.h"
#include <vector>
#include <map>
#include"GameGlobalSetting.h"
USING_NS_CC;

class AnimationInfo : public Ref
{
public:
	AnimationInfo();
	static AnimationInfo* create();
	virtual ~AnimationInfo ();
	virtual bool init();
public:
	FishKind getKind(){return mFishKind;}
	void     setKind(FishKind kind) {mFishKind = kind;}
	float    getFps() const { return mFps;}
	void     setFps(float fps) { mFps = fps;}
	int		 getFrames() const { return mFrames;}
	void     setFrames(int cnt)  { mFrames = cnt;}
	bool     isLoop() const { return mLoop;}
	void     setLoop(bool bValue)  { mLoop = bValue;}
	bool     isWalk() const { return mWalk;}
	void     setWalk(bool bValue)  { mWalk = bValue;}
	Vec2     getCenterPt() const { return mCentrePt;}
	void     setCenterPt(Vec2 pt)  { mCentrePt = pt;}
	int      getFrameWidth() const { return mFrameWidth;}
	void     setFrameWidth(int imgW)  { mFrameWidth = imgW;}
	int      getFrameHeight() const { return mFrameHeight;}
	void     setFrameHeight(int imgH) { mFrameHeight = imgH;}
	void     setImageName(std::string name) {mImageName = name;}
	std::string getImageName() const {return mImageName;}
	void     setResId(int id){mResId = id;}
	int      getResId() const{return mResId;}

protected:
		FishKind mFishKind;//�������
		float    mFps;//1/fps =���ƶ����ٶ�
		int      mFrames;//��������֡��
		bool     mLoop;//�Ƿ�ѭ�����Ŷ���
		bool     mWalk;//�Ƿ�������
		Vec2     mCentrePt;//���ĵ�ê������
		int      mFrameWidth;//֡��
		int      mFrameHeight;//֡��
		std::string mImageName;//��Ե���ͼƬ�ر���
		int      mResId;//��Դ���࣬0Ϊ�㣬1ΪPlayer 2
};

class ResourcesManager : public Ref
{
public:
	ResourcesManager();
	~ResourcesManager();
public:
	static ResourcesManager* getInstance();
	static void purgeInstance();
	bool loadResourceFile(int gameId);
	void loadGuideFile(int gameId);
	AnimationInfo* getAnimationInfoByKind(FishKind kind,bool isWalk = true);//Ĭ��ȡ���߶�������֮ȡ��������
	AnimationInfo* getAnimationInfoByName(const char* name);
	bool ContainsKey(FishKind kind);
	Vec2 stringToPoint(std::string str);
	void clearAllResource();
	__Array* getGuideInfo() const {return mGuideInfos;}
private:
	__Array* mAnimationInfos;
	__Array* mGuideInfos;
};

















#endif