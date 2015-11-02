#ifndef PLATFORM_HEAD_FILE
#define PLATFORM_HEAD_FILE

//////////////////////////////////////////////////////////////////////////////////
//�����ļ�

//�����ļ�
#include "Macro.h"
#include "Define.h"

//�ṹ�ļ�
#include "Struct.h"
#include "Packet.h"
#include "Property.h"

//ģ���ļ�
#include "Array.h"
#include "Module.h"
#include "PacketAide.h"
#include "ServerRule.h"
#include "RightDefine.h"

//////////////////////////////////////////////////////////////////////////////////

//������Ŀ
#define MAX_SERVER_COUNT			5									//������Ŀ
//����汾
#define VERSION_FRAME				PROCESS_VERSION(0,0,1)				//��ܰ汾
#define VERSION_PLAZA				PROCESS_VERSION(7,0,1)				//�����汾
#define VERSION_MOBILE_ANDROID		PROCESS_VERSION(0,0,1)				//�ֻ��汾
#define VERSION_MOBILE_IOS			PROCESS_VERSION(0,0,1)				//�ֻ��汾

//�汾����
#define VERSION_EFFICACY			0									//Ч��汾
#define VERSION_FRAME_SDK			INTERFACE_VERSION(0,1)				//��ܰ汾

//////////////////////////////////////////////////////////////////////////////////
//�����汾

#ifndef _DEBUG

//ƽ̨����
const TCHAR	szProduct[]=TEXT("������");							//��Ʒ���֣���������ʾ�ģ�
const TCHAR szPlazaClass[]=TEXT("LMYGAME");					//�㳡����
const TCHAR szProductKey[]=TEXT("������");					//��Ʒ����

//��ַ����
const TCHAR szCookieUrl[]=TEXT("http://www.999qp.com");						//��¼��ַ
const TCHAR szLogonUrl[]=TEXT("www.999qp.com");						        //��¼��ַ
const TCHAR szPlatformUrl[]=TEXT("http://www.999qp.com");				    //ƽ̨��վ
const TCHAR szWebPostUrl[]=TEXT("www.999qp.com");						    //web��ַ
const TCHAR szPayUrl[]=TEXT("http://pay.999qp.com");						//��ֵ��ַ

#else

//////////////////////////////////////////////////////////////////////////////////
//�ڲ�汾

//ƽ̨����
const TCHAR	szProduct[]=TEXT("������");							//��Ʒ����
const TCHAR szPlazaClass[]=TEXT("LMYGAME");						//�㳡����
const TCHAR szProductKey[]=TEXT("������");					//��Ʒ����

//��ַ����
const TCHAR szCookieUrl[]=TEXT("http://www.999qp.com");						//��¼��ַ
const TCHAR szLogonUrl[]=TEXT("www.999qp.com");						//��¼��ַ
const TCHAR szPlatformUrl[]=TEXT("http://www.999qp.com");				//ƽ̨��վ
const TCHAR szWebPostUrl[]=TEXT("www.999qp.com");						//web��ַ
const TCHAR szPayUrl[]=TEXT("http://pay.999qp.com");						//��ֵ��ַ


#endif

//////////////////////////////////////////////////////////////////////////////////

//���ݿ���
const TCHAR szPlatformDB[]=TEXT("QPPlatformDB");						//ƽ̨���ݿ�
const TCHAR szAccountsDB[]=TEXT("QPAccountsDB");						//�û����ݿ�
const TCHAR	szTreasureDB[]=TEXT("QPTreasureDB");						//�Ƹ����ݿ�
const TCHAR	szExerciseDB[]=TEXT("QPExerciseDB");						//��ϰ���ݿ�

//////////////////////////////////////////////////////////////////////////////////

//��Ȩ��Ϣ
const TCHAR szCompilation[]=TEXT("9E0F66DC-C919-4413-8C83-8759EF60E563");

//////////////////////////////////////////////////////////////////////////////////

#endif