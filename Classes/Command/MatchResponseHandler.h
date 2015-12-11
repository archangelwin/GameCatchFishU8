/**
 * @file MatchResponseHandler
 * @brief 
 * @author tjl
 * @date 15-10-15
 */
#ifndef __MatchResponseHandler_H_
#define __MatchResponseHandler_H_

#include "Command/BaseResponseHandler.h"
#include "cocos2d.h"


class MatchResponseHandler : public BaseResponseHandler
{
public:
	CREATE_FUNC(MatchResponseHandler);
	bool init();

	//����������Ϣ��ش���
	//��������Ϸ
	void OnSocketSubMatchGame(void* data, WORD data_size);
	//��������
	void OnSocketSubMatchType(void* data, WORD data_size);
	//�����б���ӣ����£��Ƿ�����
	void OnSocketSubMatchInfo(void* data, WORD data_size);
	//�ھ���
	void OnSocketSubAwardInfo(void* data, WORD data_size);
	//ɾ������
	void OnSocketSubMatchDelete(void* data, WORD data_size);
	//��������
	void OnSocketSubMatchNum(void* data, WORD data_size);
	//��������
	void OnSocketSubMatchSignUp(void * pData, WORD wDataSize);
	//��������
	void OnSocketSubMatchStart(void* data, WORD data_size);
	//�����ɹ�
	void OnSocketSubSignUpSuccess(void* data, WORD data_size);
	//����ʧ��
	void OnSocketSubSignUpFailure(void* data, WORD data_size);
	//�����ɹ�
	void OnSocketSubWithDrawSuccess(void * pData, WORD data_size);
	//����ʧ��
	void OnSocketSubWithDrawFailure(void * pData, WORD data_size);
	//����ʱ
	void OnSocketSubCountDown(void * pData, WORD data_size);
};



#endif // !MatchResponseHandler


