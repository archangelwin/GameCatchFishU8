#ifndef WM_MSG_HEAD_FILE
#define WM_MSG_HEAD_FILE
#pragma pack(1)
//////////////////////////////////////////////////////////////////////////////////
//socket��Ϣ
#define WM_SOCKET_NOTIFY			    WM_USER+3000						//SOCKET ��Ϣ
#define WM_WEB_SOCKET_NOTIFY			WM_USER+3001						//��Ϣ��ʶ
//���̿���
#define WM_ASYNCHRONISM_DATA		   (WM_USER+3002)						//�첽����
//֪ͨ��Ϣ
#define WM_PLATFORM_EVENT			   (WM_USER+3003)						//ƽ̨�¼�

//�������(1-19)
#define WM_ITEM_STATUS_UPDATE		   (WM_USER+1)					       //״̬����
//��Ϸ����(20-39)
#define WM_GRAPHNOTIFY                 (WM_USER+20)

//��Ϸ���(100-699)
//��Ⱦ��Ϣ
#define WM_D3D_RENDER				(WM_USER+100)							//��Ⱦ��Ϣ
#define WM_CREADED					(WM_USER+101) 
#define WM_ADD_FRIEND				(WM_USER+102)						//��Ϊ����
#define WM_SET_DETEST				(WM_USER+103)						//��Ϊ���

//����ؼ���700-1000��
#define WM_BN_LIST_CLICK			(WM_USER+700)						//listctrl�ؼ���ť��Ϣ
#define WM_BN_HALL_MATCH_CLICK		(WM_USER+701)						//listctrl�ؼ���ť��Ϣ
#define WM_BN_HALL_LAST_CLICK		(WM_USER+702)						//listctrl�ؼ���ť��Ϣ



//����(1000-1680)
#define WM_UPDATE_RESOUCE           (WM_USER+700)                      //������Դ
#define WM_LOGIN_QQ                 (WM_USER+701)                      //QQ��¼
#define WM_SAFA_BIND                (WM_USER+702)                      //��

//��Ϸ�ؼ�(1680-2000)
#define WM_INSUREPLAZA_UPDATA       (WM_USER+1680)                      //���и�����Ϣ

//����ؼ�(2000+)
//�˵�����
#define IDM_CLEAR_ALL				(WM_USER+2001)						//ɾ����Ϣ
#define IDM_SELECT_ALL				(WM_USER+2002)						//ȫ��ѡ��
#define IDM_COPY_STRING				(WM_USER+2003)						//�����ַ�
#define IDM_DELETE_STRING			(WM_USER+2004)						//ɾ���ַ�
#define IDM_SAVE_STRING				(WM_USER+2005)						//������Ϣ

#define WM_SELECT_ROOM				(WM_USER+2006)						//ѡ�񷿼�


//////////////////////////////////////////////////////////////////////////////////
#pragma pack()
#endif