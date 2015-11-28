/**
 * @file UserModel.h
 * @brief  �û�����ģ��
 * @author TJL
 * @date 15-4-27
 */

#ifndef __UserModel_H_H_
#define __UserModel_H_H_

#include "cocos2d.h"
#include "GameGlobalSetting.h"
USING_NS_CC;

class UserModel : public Ref
{
public:
	UserModel();
	~UserModel();
	bool init();
	CREATE_FUNC(UserModel);
	void setUserId(int usrId){mUserId = usrId;}
	int  getUserId() const {return mUserId;}
	void setChairId(int id){mChairID = id;}
	int  getChairId() const {return mChairID;}
	void setTableId(int id){mTableID = id;}
	int  getTableId() const {return mTableID;}
	void setUserStatus(unsigned char isValue ) {mUserStatus = isValue;}
	unsigned char getUserStatus(){return mUserStatus;}
	void setUserScore(SCORE score) { mUserScore = score;}
	SCORE getUserScore() const {return mUserScore;}
private:
	SCORE mUserScore;							//�û������
	int  mTableID;								//��������
	int  mChairID;								//��������
	unsigned char mUserStatus;						//�û�״̬
	bool mUserSex;							//�û��Ա�
	unsigned long	mUserId;					//�û�ID

};





#endif //__UserModel_H_H_
