/**
 * @file CommonResponseHandler
 * @brief 
 * @author tjl
 * @date 15-4-10
 */
#ifndef __CommonResponseHandler_H_
#define __CommonResponseHandler_H_

#include "Command/BaseResponseHandler.h"
#include "cocos2d.h"


class CommonResponseHandler : public BaseResponseHandler
{
public:
	CREATE_FUNC(CommonResponseHandler);
	bool init();

	//�����Ϣ����
	void OnReceiveGameSceneMsg(void* data, WORD data_size);//��Ϸ����
	void OnReceiveSystemMsg(void* data, WORD data_size);//�յ�ϵͳ��Ϣ

	//�����������Ϣ����
	void OnReceiveMatchStatusMsg(void* data,WORD data_size);
	void OnReceiveMatchInfoMsg(void* data,WORD data_size);
	void OnReceiveMatchNextLevelMsg(void* data,WORD data_size);
	void OnReceiveMatchAwardResultMsg(void* data,WORD data_size);
};



#endif // !CommonResponseHandler


