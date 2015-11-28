/**
 * @file Message
 * @brief ȫ����Ϣ����
 * @author TJL
 * @date
 */

#ifndef __Message_H_
#define __Message_H_

//��Ϸ�����Ϣ����
#define  ExchangeFishScoreMsg  "ExchangeFishScoreMsg" //����Ϸ���Ϣ
#define  UserFireMsg           "UserFireMsg"//��ҷ����ڵ�����Ϣ
#define  CreateNewFishMsg	   "CreateNewFishMsg"//�����µ�������Ϣ
#define  CatchFishGroupMsg	   "CatchFishGroupMsg"//��Ҳ�׽�������Ϣ
#define  BulletDoubleTimeoutMsg   "BulletDoubleTimeoutMsg"//�������γ�ʱ��Ϣ
#define  ChangeSceneMsg			"ChangeSceneMsg"//�л���������Ϣ
#define  CatchChainMsg          "CatchChainMsg"
#define  CreateSceneFishMsg		"CreateSceneFishMsg"//�������������Ϣ
#define  SceneBulletsMsg		"SceneBulletsMsg"
#define  ForceTimerSyncMsg		"ForceTimerSyncMsg"//ǿ��ͬ����Ϣ
#define  TimerSyncMsg			"TimerSyncMsg"
#define  SubSceneFishMsg		"SubSceneFishMsg"
#define  StockOperateResultMsg	"StockOperateResultMsg"
#define  AdminControlMsg		"AdminControlMsg"

//for lk
#define  ModifyLkMulriple        "ModifyLkMulriple"

//��������Ҫ�������Ϣ����
#define  LoginSuccessMsg		"LoginSuccessMsg"//��¼�ɹ�������Ϣ
#define  QucikLoginRspMsg    "QucikLoginRspMsg"
#define  LoginFaildMsg          "LoginFaildMsg"
#define  GetRoomListMsg			"GetRoomListMsg"
#define  GetUserStatusMsg	    "GetUserStatusMsg"
#define  PlayerToSeperaterMsg   "PlayerToSeperaterMsg" //��ұ��Թ�����Ϣ
#define RemoveGameSoketMsg   "RemoveGameSoketMsg"

//frame
#define GameStatusMsg			 "GameStatusMsg"
#define GameSceneMsg			 "GameSceneMsg"

//ϵͳ��Ϣ
#define SystemMessage             "SystemMessage"    

//��Ϸ��, zone����һ����Ϸ
#define XwZoneName      "XwCompilations"
#define XwZoneDntg		"XwFishingTalent"

//chain ���
#define  FishArriveMsg  "FishArriveMsg"
#define  DealBingoEffectMsg "DealBingoEffectMsg"
#define  DealJettonEffectMsg "DealJettonEffectMsg"

//����¯���
#define  dealBgLuEffectMsg "dealBgLuEffectMsg"


//��Ʒ���
#define  GetShopListFromServerMessage "GetShopListFromServerMessage"//ˢ����Ʒ�б���Ϣ
#define  buyGifRspMsg        "buyGifRspMsg"

//�������
#define  getAuctionList   "getAuctionList"					//��ȡ�ϼ���Ʒ�б�
#define  getAuctoinRecord "getAuctoinRecord"				//��ȡ�����м�¼
#define  getMyAuctionRecord "getMyAuctionRecord"			//��ȡ�ҵ�����
#define  getAuctionHistoryRecord "getAuctionHistoryRecord"	//��ȡ������ʷ��¼
#define  sellAuctionResultMsg  "sellAuctionResultMsg"       //�ϼ���Ʒ������Ϣ
#define  buyAuctionResultMsg   "buyAuctionResultMsg"        //������Ʒ������Ϣ
#define  cancelAuctionResultMsg "cancelAuctionResultMsg"    //��������������Ϣ
#define  treasureInfoMsg        "treasureInfoMsg"           //�Ƹ�
#define  converAuctionScoreMsg  "converAuctionScoreMsg"     //��ȡ����������

//�������
#define  getBagListMsg      "getBagListMsg"
#define  receiveKnapsackLogMsg "receiveKnapsackLogMsg"
#define  useBagMsg           "useBagMsg"
#define  userKnapsackMsg     "userKnapsackMsg"

#define toUserKnascapMsg     "toUserKnascapMsg"//֪ͨ��������
#define toUserGiftMsg     "toUserGiftMsg"//֪ͨ�̳ǽ���
#define toBuyAuctionMsg   "toBuyAuctionMsg" //֪ͨ��������
//vip power
#define  getVipPowerInfo     "getVipPowerInfo"
#define  vipAwardResultMsg   "vipAwardResultMsg"
//task ���
#define  getTaskListMsg      "getTaskListMsg"
#define  getTaskAwardMsg     "getTaskAwardMsg"
//�������
#define  queryInsureInfoMsg  "QueryInsureInfoMsg"
#define  insureSuccessMsg        "insureSuccessMsg"
#define  insureFailureMsg        "insureFailureMsg"
//��¼���
#define  RequestFastLoginNotification "RequestLoginNotification" //������ٵ�¼
#define  RequestRegisterNotification "RequestRegisterNotification" //����ע��

//�����ɹ���ʧ�ܷ��ض���
#define  operateSuccessMsg "operateSuccessMsg"
#define  operateFailureMsg "operateFailureMsg"

//���Ե�¼�������������Ϣ
#define loginTaskServerMsg "loginTaskServerMsg"
//��Ϣ������Ϣ����
#define refreshMsgListMsg "refreshMsgListMsg"
//ǩ�����
#define  getAssignListMsg  "getAssignListMsg"
#define  userAssignMsg     "userAssignMsg"

//�������
#define  switchBagItemMsg "switchBagItemMsg" //�л�����ѡ��֪ͨ

//���ֻ����
#define  bindPhoneRspMsg   "bindPhoneRspMsg"

//�һ��������
#define  checkAccountRspMsg  "checkAccountRspMsg"
#define  setPassRspMsg       "setPassRspMsg"
#define  setInsurePassRspMsg  "setInsurePassRspMsg"

//��ֵ���
#define  exchangeIngotRspMsg  "exchangeIngotRspMsg"
#define  IngotCovertScoreMsg  "IngotCovertScoreMsg"
#define  RechargeOrderRspMsg  "RechargeOrderRspMsg"
#define  toGetRechargeOrderMsg  "toGetRechargeOrderMsg"
#define  RechargeSuccessMsg  " RechargeSuccessMsg"
#define  hasFirstRechargeMsg    "hasFirstRechargeMsg"

//��¼��Ϸ�������
#define  loginRealRoomSuccess "loginRealRoomSuccess"
#define  loginRealRoomFailure "loginRealRoomFailure"

//ˢ���û�����
#define  updateUserInfoMsg "updateUserInfoMsg"
#define  updateHeadMsg      "updateHeadMsg"//ˢ��ͷ��
#define  updateUserInfoFromAuciontMsg "updateUserInfoFromAuciontMsg"
#define  updateVipLevelMsg "updateVipLevelMsg"
//QQ��¼
#define  qqLoginMsg  "qqLoginMsg"
#define  accountLoginMsg "accountLoginMsg"
#define  accountRegisterMsg "accountRegisterMsg"
#define  qucikLoginByAccount "qucikLoginByAccount"//�Ѿ���������ٵ��ʺź������ֱ�ӵ�¼
#define  loginAtOtherPlace "loginAtOtherPlace"//��ص�¼

//���ӳɹ����
#define  connectHallSuccessMsg        "connectHallSuccessMsg" //���ӵ�¼����������
#define  connectGameServerSuccessMsg  "connectGameServerSuccessMsg"//������Ϸ����������
#define  connectGameServerFaildMsg    "connectGameServerFaildMsg"//�߽���Ϸ������ʧ�ܷ���
#define  connectTaskServerSuccessMsg  "connectTaskServerSuccessMsg"//�����������������

//�����������Ϸ
#define  feedBackMsg "feedBackMsg"
#define  moreGameMsg "moreGameMsg"

//VIP��Ȩ
#define  VipPowerToShopMsg "VipPowerToShopMsg"
#define  VipPowerToChargeMsg "VipPowerToChargeMsg"
#define  ToSendGetAwardMsg "ToSendGetAwardMsg"
#define  DealVipTipsMsg           "DealVipTipsMsg"//����VIP tipsЧ��
//�˳���Ϸ
#define ExitGameMsg "ExitGameMsg"
#define GameSorketCloseMsg "GameSorketCloseMsg"
#define TaskSorketCloseMsg "TaskSorketCloseMsg"

//�������
#define  loginTaskServerSuccessMsg "loginTaskServerSuccessMsg"

//�������
#define  downLoadReponseMsg "downLoadReponseMsg"//���ط���
//����һ�
#define  giftConvertRspMsg  "giftConvertRspMsg"
//redpoint
#define  unReadMessageMsg "unReadMessageMsg"
#define  unGetTaskAwardMsg "unGetTaskAwardMsg"
#define  updateTaskRedPointMsg "updateTaskRedPointMsg"

#define  updateRedPointMsg     "updateRedPointMsg"
//��ȡ��֤�뷵��
#define  getCaptchaRspMsg "getCaptchaRspMsg"
//�������
#define  UpdateMsg "UpdateMsg"
#define  CancelUpdateMsg "CancelUpdateMsg"

#define  KeyEscapeMsg "KeyEscapeMsg"

#define  netWorkValidMsg "netWorkValidMsg" //�������Ӳ�������Ϣ

//�������
#define  refreshMatchListMsg "refreshMatchListMsg"//���Ӻ�ˢ�±����б���Ϣ
#define  deleteMatchRoomMsg "deleteMatchRoomMsg" //ɾ�����ڱ���������Ϣ
#define  updateRoomSignUpPlayersMsg  "updateRoomSignUpPlayersMsg" //ˢ�·���������Ϣ
#define  signUpSuccessMsg "signUpSuccessMsg"
#define  signUpFaildMsg        "signUpFaildMsg"
#define  unSignUpSuccessMsg "unSignUpSuccessMsg"
#define  unSignUpFaildMsg        "unSignUpFaildMsg"
#define  matchCountDownMsg  "matchCountDownMsg" //ˢ�·��䵹��ʱ
#define  matchStartMsg               "matchStartMsg" //������ʼ��Ϣ
#define  toSignUpNotice              "toSignUpNotice" //
#define  tounSignUpNotice              "tounSignUpNotice" //

#define  updateMatchStatusMsg       "updateMatchStatusMsg" //ˢ�·������״̬��Ϣ
#define  updateMatchInfoMsg	         "updateMatchInfoMsg"    //ˢ�·��������Ϣ��Ϣ
#define  matchAwardMsg                   "matchAwardMsg"             //����������Ϣ
#define  MatchTryAgainMsg              "MatchTryAgainMsg"        //�ٴ���ս��Ϣ
#define  showMatchTryMsg               "showMatchTryMsg"
#define  updateMatchRankMsg          "updateMatchRankMsg"
#define  MatchIsBeingStartMsg         "MatchIsBeingStartMsg"
#define  EnterMatchRoomMsg			 "EnterMatchRoomMsg"

#define  MatchPlayCountIsMaxMsg     "MatchPlayCountIsMaxMsg"

#define  closeLoginDialogMsg "closeLoginDialogMsg"
#endif    