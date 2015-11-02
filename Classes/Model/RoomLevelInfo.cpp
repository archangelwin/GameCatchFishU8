#include "RoomLevelInfo.h"


RoomLevelInfo::RoomLevelInfo()
{
	mKindIndex =0;
	mNodeIndex =0;
	mSortIndex =0;
	mServerId =0;
	mServerPort =0;
	mOnlineCount =0;
	mRoomType =RoomTypeNormal;
	mRoomLimit =0;

	mServerAddr ="";
	mServerName ="";
	mLevelName ="";
	mRoomDesc ="";
}

RoomLevelInfo::~RoomLevelInfo()
{

}

RoomLevelInfo* RoomLevelInfo::create()
{
	RoomLevelInfo* info = new RoomLevelInfo;
	if (info && info->init())
	{
		info->autorelease();
		return info;
	}
	CC_SAFE_DELETE(info);
	return nullptr;
}

bool RoomLevelInfo::init()
{
	return true;
}


//��������
void RoomLevelInfo::setKindIndex(int index)
{
	mKindIndex = index;
}

int RoomLevelInfo::getKindIndex()const
{
	return mKindIndex;
}

//�ڵ�����
void RoomLevelInfo::setNodeIndex(int index)
{
	mNodeIndex = index;
}

int RoomLevelInfo::getNodeIndex()const
{
	return mNodeIndex;
}

//��������
void RoomLevelInfo::setSortIndex(int index)
{
	mSortIndex = index;
}

int RoomLevelInfo::getSortIndex()const
{
	return mSortIndex;
}

//��������
void RoomLevelInfo::setRoomName(std::string name)
{
	mServerName = name;
}

std::string RoomLevelInfo::getRoomName()const
{
	return mServerName;
}
//����ID
void RoomLevelInfo::setRoomId(int id)
{
	mServerId = id;
}
int RoomLevelInfo::getRoomId()const
{
	return mServerId;
}

//����SERVER PORT
void RoomLevelInfo::setServerPort(int port)
{
	mServerPort = port;
}

int  RoomLevelInfo::getServerPort() const
{
	return mServerPort;
}

//��������
void RoomLevelInfo::setOnlineCount(int cnt)
{
	mOnlineCount = cnt;
}

int  RoomLevelInfo::getOnlineCount() const
{
	return mOnlineCount;
}

//��������
void RoomLevelInfo::setRoomMax(int max)
{
	mRoomLimit = max;
}

int  RoomLevelInfo::getRoomMax() const
{
	return mRoomLimit;
}

//�����������ַ
void RoomLevelInfo::setRoomServerAddr(std::string addr)
{
	mServerAddr = addr;
}

std::string RoomLevelInfo::getRoomServerAddr() const
{
	return mServerAddr;
}

//����
void RoomLevelInfo::setRoomLevel(std::string name)
{
	mLevelName = name;
}

std::string RoomLevelInfo::getRoomLevel() const
{
	return mLevelName;
}

//��������
void RoomLevelInfo::setRoomDesc(std::string desc)
{
	mRoomDesc = desc;
}
std::string RoomLevelInfo::getRoomDesc() const
{
	return mRoomDesc;
}

//��������
void RoomLevelInfo::setRoomType(RoomType type)
{
	mRoomType = type;
}

RoomType RoomLevelInfo::getRoomType() const
{
	return mRoomType;
}