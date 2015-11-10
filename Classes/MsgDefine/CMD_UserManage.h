#ifndef CMD_USERMANAGE_HEAD_FILE
#define CMD_USERMANAGE_HEAD_FILE

#include "GameGlobalSetting.h"
#include "GolbalDefine/Define.h"

#pragma pack(1)

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#define  MAX_SERVERID		    500										//��������id
//�û����������
//I D ��¼
#define  MDM_UM_LOGIN			10										//�����������¼��UM
#define  MDM_UM_USER			11										//�û���һЩ��Ϣ
#define  MDM_UM_S_USER			12		
//������
#define  MDM_UM_ANDROID			13										//������

#define  MDM_UM_MB_DATA			14										//�ֻ�����

#define  MAX_LOG				256										//��־����
//����䴫��
								//����������
#define  SUB_UM_S_SERVERLOGIN    		100								//��������¼
#define	 SUB_UM_S_USER_ENTER	   		101								//�û����뷿��
#define  SUB_UM_S_USER_LEAVE	   		102								//�û��˳�����
#define	 SUB_UM_S_USER_SCORE	   		103								//�û��÷� 
#define  SUB_UM_S_USER_GAME_SET			104								//�����û�����
#define  SUB_UM_S_SYS_SET				105								//������Ϸ����
#define  SUB_UM_S_TRANSFER_SCORE		106								//ת��
#define	 SUB_UM_S_SYNC_USER				107								//����ʱ��ͬ�����û�������->UM��
#define  SUB_UM_S_GET_STORAGE			108								//��ȡ���
#define  SUB_UM_S_TRANSFER_GAME_SCORE	109								//��Ϸת��
#define  SUB_UM_S_USER_LOGIN			110								//������¼
#define  SUB_UM_S_UPDATE_SCORE			111								//���±�
#define  SUB_UM_S_KICKUSER				112								//�߳�������û�
#define	 SUB_UM_S_USER_TEMP_SCORE	   	113								//��ʱ�仯����
#define	 SUB_UM_S_MAXANDROIDCOUNT	   	114								//�������˸���
#define	 SUB_UM_S_STOPANDROIDIN	   		115								//�����˽���ֹͣ

//������
#define  SUB_UM_S_ATTRIB_OPTION			200								//��������,����
#define  SUB_UM_S_ANDROIDLOGIN			201								//����
#define  SUB_UM_S_ANDROIDLOGOUT			202								//�˳�
#define  SUB_UM_S_SYNC_ANDROID			203								//����ʱ��ͬ��������
#define  SUB_UM_S_USERCOUNT				204								//�������



	
//�ͻ���
#define	 SUB_UM_USER_ENTER	   			200								//�û����뷿��
#define  SUB_UM_USER_LEAVE	   			201								//�û��˳�����
#define	 SUB_UM_USER_SCORE	   			202								//�û��÷� 
#define  SUB_UM_USER_INFO				203								//�û���Ϣ
#define  SUB_UM_GET_USER_GAME_SET		204								//��ȡ�û�����
#define  SUB_UM_GET_SYS_SET				205								//��ȡ��Ϸ����
#define  SUB_UM_SET_USER_GAME_SET		206								//�����û�����
#define  SUB_UM_SET_SYS_SET				207								//������Ϸ����
#define  SUB_UM_SET_USER_SCORE			208								//�û���Ӯ
#define  SUB_UM_GET_USER_SCORE			209								//�û���Ӯ
#define  SUB_UM_SET_USER_VIP			210								//vip�û�
#define  SUB_UM_DELETE_USER_VIP			211								//ɾ��vip�û�
#define  SUB_UM_GET_STORAGE				212								//��ȡ���
#define  SUB_UM_HEART_BEAT				213                             //socket����
#define  SUB_UM_SET_DEFAULT				214                             //�ָ�Ĭ��
#define  SUB_UM_GET_ALL_STORAGE			215								//��ȡ���п��
#define  SUB_UM_SET_ALL_STORAGE			216								//�������п��
#define  SUB_UM_ADMIN					217								//����Ա�б�
#define  SUB_UM_LOG						218								//�����ռ�
#define  SUB_UM_LTANKING				219								//��ˮ
#define  SUB_UM_SET_SYS_SET_LTANKING	220								//���÷�ˮ
#define  SUB_UM_GET_USER				221								//��ȡ�û�
#define  SUB_UM_GET_OFFLINE				222								//��ȡ�����û����ù����û�
#define  SUB_UM_GET_USER_EX				223								//��ȡ�û�
#define  SUB_UM_TRANSFERSCORE			224								//ת��
#define  SUB_UM_ANDROIDCOUNT			225								//�����˸���
#define  SUB_UM_GAMESCORE				226								//��ѯ����
#define  SUB_UM_FORZENUSER				227								//�����û�

//�ֻ����
#define  SUB_UM_MD_COUNT				100								//����





#define  UM_MAX_ANDROID					MAX_ANDROID*20					//��������

enum SetType
{
	MAXWIN = 0,						//Ӯ
	MAXLOSE,						//��
	SYSMAXWIN,						//ϵͳӮ
	SYSMAXLOSE,						//ϵͳ��
	MAXNOTIFYWIN,					//Ԥ��Ӯ
	MAXNOTIFYLOSE,					//Ԥ����
	MAXDEFAULT,						//ϵͳĬ��
	OPFINISH						//�������
};

enum LogType
{
	OPLOG = 1,						//����
	ERRORLOG						//����
};
//���������Ϣ
struct tabUMServerRoomInfo
{
	tabUMServerRoomInfo()
	{
		memset(this, 0, sizeof(tabUMServerRoomInfo));
	}
	DWORD							dwServerID;							//server I D
	TCHAR							szMachineID[LEN_MACHINE_ID];		//��������
	CHAR							szServerName[LEN_SERVER];			//��������
	DWORD							dwMinEnterScore;					//�볡����
	WORD							wKindID;							//��������
};

struct tagUMServerRoomLogin
{
	tagUMServerRoomLogin()
	{
		memset(this, 0, sizeof(tagUMServerRoomLogin));
	}
	//��¼��Ϣ
	DWORD							dwServerID;							//server I D
	TCHAR							szPassword[LEN_MD5];				//��¼����
	TCHAR							szMachineID[LEN_MACHINE_ID];		//��������
	CHAR							szServerName[LEN_SERVER];			//��������
	DWORD							dwMinEnterScore;					//�볡����
	WORD							wKindID;							//��������
};

//�û�������Ϣ
struct tagUMUserInfo
{
	tagUMUserInfo()
	{
		memset(this, 0, sizeof(tagUMUserInfo));
	}
	DWORD						dwUserID;
	DWORD						dwServerID;
	TCHAR						szNickName[LEN_ACCOUNTS];			//�û��ǳ�	
	DWORD						dwBeginTime;						//��Ϸ��ʼʱ��
	DWORD						dwEndTime;												
	//������Ϣ
	SCORE						lScore;								//�û�����
	SCORE						lInsure;							//�û�����
};

//�û�������Ϣ
struct tagUMUserScoreSet
{
	tagUMUserScoreSet()
	{
		memset(this, 0, sizeof(tagUMUserScoreSet));
		dwType = MAXDEFAULT; 
	}
	DWORD						dwUserID;
	DWORD						dwGameID;		
	DWORD						dwKindID;							//��Ϸ����
	DWORD						dwServerID;							//����id
	DWORD						dwTableID;							//����
	DWORD						dwIsSet;							//�Ƿ���Կ���
	WORD						wOnline;							//0�����ߣ�1������
	TCHAR						szNickName[LEN_ACCOUNTS];			//�û��ǳ�	

	DWORD						dwBeginTime;						//��Ϸ��ʼʱ��

	DWORD						dwWinCount;							//Ӯ��
	DWORD						dwLoseCount;						//���

	//������Ϣ
	SCORE						lScore;								//�û�����
	SCORE						lInsure;							//�û�����

	//ת��
	SCORE						lOutScore;							//ת��
	SCORE						lInScore;							//ת��
	TCHAR						szLastOut[64];						//���һ��ת����ϸ
	TCHAR						szLastIn[64];						//���һ��ת����ϸ

	SCORE						lAllOutScore;						//��ת��
	SCORE						lAllInScore;						//��ת��
	SCORE						lDifference;						//��ֵ		

	SCORE						lWinScore;							//��Ӯ����

	SCORE						lTempScore;							//���ú���Ӯ����

	SCORE						lMaxWin;							//Ӯ����
	SCORE						lMaxLose;							//�����

	SCORE						lTobayWin;							//������Ӯ���
	SCORE						lMoney;								//��ֵ

	SCORE						lSetWinOrLose;						//������Ӯ����

	SCORE						lNotifyMaxWin;						//Ԥ��Ӯ����
	SCORE						lNotifyMaxLost	;					//Ԥ�������

	SetType						dwType;								//����
	DWORD						dwWinOrLostRate;					//���Ʊ��ʣ��ٷֱȣ�
	DWORD						dwChannel;							//������1������վ��0������
	int							nVipType;							//�û����� ����vip��
	DWORD						dwClientAddr;						//IP
	TCHAR						szMachineID[LEN_MACHINE_ID];		//Ӳ����
	DWORD						dwSetTime;							//���õ�ʱ��
	TCHAR						szRemarks[256];						//��ע			
};

//ת��
struct tagUMTransferScore
{
	tagUMTransferScore()
	{
		memset(this, 0, sizeof(tagUMTransferScore));
	}
	DWORD						dwUserID;
	DWORD						dwTargetUserID;
	//ת��
	SCORE						lOutScore;							//ת��
};
//�û�����
struct tagUMGameScore
{
	tagUMGameScore()
	{
		memset(this, 0, sizeof(tagUMGameScore));
	}
	DWORD						dwServerID;							//server I D
	DWORD						dwTableID;
	DWORD						dwUserID;
	SetType						dwType;								//����
	DWORD						dwWinOrLostRate;					//���Ʊ��ʣ��ٷֱȣ�
	SCORE						lGameScore;							//�û��÷�
	SCORE						lScore;								//����
	SCORE						lInsure;							//�û�����
};
//�˳�����
struct tagUMUserLeave
{
	tagUMUserLeave()
	{
		memset(this, 0, sizeof(tagUMUserLeave));
	}
	DWORD						dwServerID;							//server I D
	DWORD						dwTableID;
	DWORD						dwAndroid;							//�Ƿ��ǻ�����
	DWORD						dwUserID;
};
struct tabServerID
{
	tabServerID()
	{
		dwServerID=0;
	}
	DWORD dwServerID;
};
//ϵͳ������Ϣ
struct tagUMUserGameSet
{
	tagUMUserGameSet()
	{
		memset(this, 0, sizeof(tagUMUserGameSet));
		bNullity = true;
	}
	DWORD						dwServerID;	
	DWORD						dwSetTime;							//����ʱ��
	DWORD						dwIsSet;							//�Ƿ���Կ���

	SCORE						lMaxWin;							//Ӯ����
	SCORE						lMaxLose;							//�����

	SCORE						lMaxWin1;							//Ӯ����(����)
	SCORE						lMaxLose1;							//�����(����)

	SCORE						lNotifyMaxWin;						//Ԥ��Ӯ����
	SCORE						lNotifyMaxLost	;					//Ԥ�������

	DWORD						dwWinOrLostRate;					//���Ʊ��ʣ��ٷֱȣ�
	DWORD						dwWinOrLostRate1;					//���Ʊ��ʣ��ٷֱȣ�������)
	TCHAR						szPhone[48];						//Ԥ��ʹ�õ��ֻ�
	TCHAR						szEmail[48];						//Ԥ��ʹ�õ�����

	DWORD						dwAndroidMinScore;					//��������С��
	DWORD						dwAndroidMaxScore;					//����������

	bool						bNullity;							//�Ƿ���Ч
};
//������������
struct tagUMSysGameSet
{
	tagUMSysGameSet()
	{
		memset(this, 0, sizeof(tagUMSysGameSet));
		//strcpy(szItem0, TEXT("[ %s ]��ׯ�ˣ������Ǹ�������ɫ����"));
		//strcpy(szItem1, "[ %s ]��ׯ�ˣ�������ӭ");
		//strcpy(szItem2, "[ %s ]��ׯ�ˣ���Ҿ�����Ϸ��");
	}
	DWORD  dwServerID;									//serverid
	DWORD  bValid;										//�����Ƿ���Ч

	bool   bStorag;										//����Ƿ�ˢ��
	LONGLONG  dwStoragStart;							//(�����ʼֵ��	
	DWORD  dwStorageDeduct;								//��˥��ֵ��

	//��ͻ���û�д�����֧��
	//DWORD  dwFreeTime;									//����ʱ��
	//DWORD  dwCallBanker;								//��ׯʱ��	
	//DWORD  dwBetTime;									//��עʱ��	
	//DWORD  dwEndTime;									//����ʱ��	
	//int  dwTimeParameters1;								//����1
	//int  dwTimeParameters2;								//����2
	//int  dwTimeParameters3;								//����3
	//int  dwTimeParameters4;								//����4

	////Ŀǰͨ��ţţʹ��
	//DWORD dwUsuallyChangePercent;						//ͨ������£����ưٷֱ�
	//DWORD dwRobotWinScorePercent;						// ( > RobotDefineTanking) �۳�������Ӯ�ķ����İٷֱ� 

	//int	  dwRealBankerRobotLoseMax;						//��: һ�֣�*���������������и��ʻ���(ţţ�������� *����)
	//int	  dwRealBankerRobotLoseChangePercent;			//��: һ�֣�*�����������ưٷֱȣ�*RealBankerRobotLoseMax ��
	//int	  dwRealBankerRobotLoseMaxChange;				//��: һ�֣�*����������ʼ����,�ٷְٻ��ƣ�2500001 ���ϣ�ûʹ�ã�

	//SCORE dwRobotLoseMax;								//��:�������и��ʻ���
	//DWORD dwRobotLoseChangePercent; 					//��:���ưٷֱ�(*RobotLoseMax)
	//SCORE dwRobotLoseMaxChange;							//��:����ʼ����,�ٷְٻ���

	//DWORD dwRobotProbabilityTanking;					//Ӯ:�������и��ʷ�ˮ
	//DWORD dwRobotTankingPercent;						//Ӯ:�ٷְٷ�ˮ��*RobotProbabilityTanking��
	//DWORD dwRobotDefineTanking;							//Ӯ:�ٷְٷ�ˮ
	//////////////////////////////////////////////////////////////////

	//SCORE dwRobotResultScore;							//�ۼƷ���
	//SCORE dwRobotWinChiefScore;


	////�����˴��ȡ��
	//DWORD dwRobotScoreMin;								//�����˵ķ���С�ڸ�ֵʱִ��ȡ��
	//DWORD dwRobotScoreMax;								//�����˵ķ������ڸ�ֵʱִ�д��
	//DWORD dwRobotBankGet;								//ȡ����С����(ȡ�����Ǹ�ֵ���ϵ�һ�������)
	//DWORD dwRobotBankGetBanker;							//ȡ���������(����ֵһ��Ҫ����RobotBankGet)
	//DWORD dwRobotBankStoMul;							//������

	////������Ϸ
	//DWORD dwScore;										//��ׯ�����(���ڴ����ſ���ׯ)
	//DWORD dwTime;										//��ׯ����
	//DWORD dwTimeAdd;									//��ׯ���Ӵ���(�����Time��ׯ�������Ҵ��������������,�ٿ�������)
	//DWORD dwBankerScore;								//������ׯ�����(���ڴ˽�Һ������Ƿ��д������������ң����ɼ���)
	//DWORD dwBankerAdd;									//�������(��ҴﵽBankerScore��,Time����ׯ���ٶ������ӵ���ׯ����)
	//DWORD dwEnableSysBanker;							//ϵͳ��ׯ


	//DWORD dwAreaLimitScore;								//��������(ÿ��ע������߷ⶥ����)
	//DWORD dwUserLimitScore;								//������ע����

	//DWORD dwMessageCount;								//��ׯ��Ϣ

 //	TCHAR szItem0[64];									//[ %s ]��ׯ�ˣ������Ǹ�������ɫ����
	//TCHAR szItem1[64];									//[ %s ]��ׯ�ˣ�������ӭ
	//TCHAR szItem2[64];									//[ %s ]��ׯ�ˣ���Ҿ�����Ϸ��


	//DWORD dwORDRobotMaxBetTime;							//��������ע��Χ(����)
	//DWORD dwRobotMinBetTime;							//��������ע��Χ(����)
	//DWORD dwRobotMaxJetton;								//�����˳��뷶Χ(����)
	//DWORD dwRobotMinJetton;								//�����˳��뷶Χ(����)
	//DWORD dwRobotBanker;								//�������Ƿ���ׯ��1ʱ�������˿���ׯ��0ʱ�����˲�����ׯ
	//DWORD dwRobotBankerCount;							//��������ׯ����	
	//DWORD dwRobotWaitBanker;							//�����˿ռ���֮��������ׯ
	//DWORD dwRobotApplyBanker;							//����������������
	//DWORD dwRobotBetCount;  							//�����������ע����
	//DWORD dwRobotAreaLimit;	     		    			//������������ע����
    /////////////////////////////////////////////////////////////////////////////

	SCORE AllScore;										//�����ۼ�
	SCORE MonthScore;									//�����ۼ�(��Ϊ����)
	SCORE WeekScore;									//�����ۼ�(��Ϊǰ��)
	SCORE TodayScore;									//�����ۼ�

	SCORE TodayTankingScore;							//�����ۼƷ�ˮ
	SCORE TankingScore;									//��ˮ
	SCORE CurTankingScore;								//��ǰ��ˮ
	DWORD dwServerRate;									//��ˮ����
};
struct tagStoragInfo
{
	tagStoragInfo()
	{
		memset(this, 0, sizeof(tagStoragInfo));
	}
	DWORD dwServerID;
	DWORD dwAll;									//�Ƿ����У�0��ֻ��һ����1�����У�
	DWORD dwSocket;									//ת�����õ�socket
	DWORD  bValid;									//�����Ƿ���Ч
	LONGLONG  lStoragStart;							//(�����ʼֵ��	
	DWORD  dwStorageDeduct;							//��˥��ֵ��
};
struct tabUserVip
{
	tabUserVip()
	{
		memset(this, 0, sizeof(tabUserVip));
	}
	DWORD dwUserID;
	int	  nType;
};
struct tabUMAndroid
{
	tabUMAndroid()
	{
		memset(this, 0, sizeof(tabUMAndroid));
	}
	DWORD dwUserID;
};

struct tabUMAndroidArray
{
	tabUMAndroidArray()
	{
		memset(this, 0, sizeof(tabUMAndroidArray));
	}
	DWORD dwServerID;
	DWORD dwCount;
	DWORD dwUserID[1];
};
struct tabOnLineCount
{
	tabOnLineCount()
	{
		memset(this, 0, sizeof(tabOnLineCount));
	}
	DWORD dwServerID;
	DWORD dwAllUserCount;
	DWORD dwUserCount;
};
struct tabUserID
{
	tabUserID()
	{
		memset(this, 0, sizeof(tabUserID));
	}
	DWORD dwUserID;
};
struct tabStoragStart
{
	tabStoragStart()
	{
		memset(this, 0, sizeof(tabStoragStart));
	}
	DWORD dwServerID;
	DWORD bValid;
	SCORE lStoragStart;
	DWORD dwStorageDeduct;
};
struct tabStoragStartArray
{
	tabStoragStartArray()
	{
		memset(this, 0, sizeof(tabStoragStartArray));
	}
	DWORD dwCount;
	tabStoragStart StoragStart[100];
};
//���߹���Ա
struct tagAdmin
{
	tagAdmin()
	{
		memset(this, 0, sizeof(tagAdmin));
	}
	DWORD						dwUserID;
	DWORD						dwGameID;		
	DWORD						dwType;								//0�����ߣ� 1������
	TCHAR						szNickName[LEN_ACCOUNTS];			//�û��ǳ�	
	DWORD						dwLastLoginTime;					//����¼ʱ��				
};
struct tagLog
{
	tagLog()
	{
		memset(this, 0, sizeof(tagLog));
	}
	DWORD						dwType;					
	TCHAR						szLog[MAX_LOG];
};
struct tagUserLogin
{
	tagUserLogin()
	{
		memset(this, 0, sizeof(tagUserLogin));
	}
	DWORD						dwUserID;
	DWORD						dwGameID;		
	TCHAR						szNickName[LEN_ACCOUNTS];			//�û��ǳ�	

	//������Ϣ
	SCORE						lScore;								//�û�����
	SCORE						lInsure;							//�û�����

	DWORD						dwClientAddr;						//IP
	TCHAR						szMachineID[LEN_MACHINE_ID];		//Ӳ����
};
struct tagUpdateScore
{
	tagUpdateScore()
	{
		memset(this, 0, sizeof(tagUpdateScore));
	}
	DWORD						dwUserID;
	//������Ϣ
	SCORE						lScore;								//�û�����
	SCORE						lInsure;							//�û�����
};
struct tagFindUser
{
	TCHAR						szText[LEN_ACCOUNTS];			//�Ҳ������ 
};
//�û�������Ϣ
struct tagTransferScore
{
	tagTransferScore()
	{
		memset(this, 0, sizeof(tagTransferScore));
	}
	DWORD						dwUserID;
	DWORD						dwGameID;					
	DWORD						dwTargetUserID;						
	DWORD						dwTargetGameID;		
	TCHAR						szNikeName[LEN_ACCOUNTS];
	TCHAR						szTargetNikeName[LEN_ACCOUNTS];	
	SCORE						lScore;
};

struct tagAndroidCount
{
	tagAndroidCount()
	{
		memset(this, 0, sizeof(tagAndroidCount));
	}
	DWORD   dwServerID;
	DWORD	dwBeginTime;
	DWORD	dwEndTime;
	int		nAndroidCount;
};

struct tagQueryGame
{
	tagQueryGame()
	{
		memset(this, 0, sizeof(tagQueryGame));
	}
	DWORD dwServerID;
	DWORD dwDay;
};
struct tagQueryGameScore
{
	tagQueryGameScore()
	{
		memset(this, 0, sizeof(tagQueryGameScore));
	}
	TCHAR						szNickName[LEN_ACCOUNTS];			//�û��ǳ�	
	DWORD						dwUserID;
	DWORD						dwGameID;		
	SCORE						lScore;
};
//����û������ŷֿ�
struct tagUserID
{
	tagUserID()
	{
		memset(this, 0, sizeof(tagUserID));
	}
	TCHAR							szUserID[256];						//�û�ID �� ��102��103��105��
	TCHAR							szForzen[64];						//ԭ��
};
//��������
struct tagMaxAndroidCount
{
	tagMaxAndroidCount()
	{
		memset(this, 0, sizeof(tagMaxAndroidCount));
	}
	DWORD						dwServerID;
	DWORD						dwMaxAndroidCount;
};
struct tagMDCount
{
	tagMDCount()
	{
		memset(this, 0, sizeof(tagMDCount));
	}
	DWORD						dwCount;
};
#pragma pack()

#endif //CMD_USERMANAGE_HEAD_FILE