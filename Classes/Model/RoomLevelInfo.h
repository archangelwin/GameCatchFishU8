/**
 * @file RoomLevelInfo.h
 * @brief  
 * @author TJL
 * @date 15-4-10
 */
#ifndef __RoomLevelInfo_H_
#define __RoomLevelInfo_H_

#include "cocos2d.h"

USING_NS_CC;

enum RoomType
{
	RoomTypeNormal = 0,
	RoomTypeNew,
	RoomTypeHot,
	RoomType_MAXCOUNT
};

class RoomLevelInfo : public Ref {
public:
    RoomLevelInfo ();
    virtual ~RoomLevelInfo ();

    static RoomLevelInfo *create();
    virtual bool init();

    //��������
    void setKindIndex(int index);
    int getKindIndex()const;

    //�ڵ�����
    void setNodeIndex(int index);
    int getNodeIndex()const;

    //��������
    void setSortIndex(int index);
    int getSortIndex()const;

    //��������
    void setRoomName(std::string name);
    std::string getRoomName()const;

	//����ID
	void setRoomId(int id);
	int getRoomId()const;

	//����SERVER PORT
	void setServerPort(int port);
	int  getServerPort() const;

	//��������
	void setOnlineCount(int cnt);
	int  getOnlineCount() const;

	//��������
	void setRoomMax(int max);
	int  getRoomMax() const;

	//�����������ַ
	void setRoomServerAddr(std::string addr);
	std::string getRoomServerAddr() const;

	//����
	void setRoomLevel(std::string name);
	std::string getRoomLevel() const;

	//��������
	void setRoomDesc(std::string desc);
	std::string getRoomDesc() const;

	//��������
	void setRoomType(RoomType type);
	RoomType getRoomType() const;
private:
	int mKindIndex;
	int mNodeIndex;
	int mSortIndex;
	int mServerId;
	int mServerPort;
	int mOnlineCount;
	RoomType mRoomType;
	int mRoomLimit;

	std::string mServerAddr;
	std::string mServerName;
	std::string mLevelName;
	std::string mRoomDesc;

  
};

#endif //__RoomLevelInfo_H_
