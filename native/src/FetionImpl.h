/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_honnix_jfetion_impl_FetionImpl */

#ifndef _Included_com_honnix_jfetion_impl_FetionImpl
#define _Included_com_honnix_jfetion_impl_FetionImpl
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncAddBuddyById
 * Signature: (Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddBuddyById
  (JNIEnv *, jobject, jstring, jstring, jint, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncAddBuddyByMobileNumber
 * Signature: (Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddBuddyByMobileNumber
  (JNIEnv *, jobject, jstring, jstring, jint, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncAddBuddyList
 * Signature: (Ljava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddBuddyList
  (JNIEnv *, jobject, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncAddToBlacklistByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddToBlacklistByAccount
  (JNIEnv *, jobject, jobject, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncAddToBlacklistById
 * Signature: (JLcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddToBlacklistById
  (JNIEnv *, jobject, jlong, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncAddToBlacklistByUri
 * Signature: (Ljava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddToBlacklistByUri
  (JNIEnv *, jobject, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncBeginDialog
 * Signature: (JLcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncBeginDialog
  (JNIEnv *, jobject, jlong, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncDeleteBuddyByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDeleteBuddyByAccount
  (JNIEnv *, jobject, jobject, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncDeleteBuddyById
 * Signature: (JLcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDeleteBuddyById
  (JNIEnv *, jobject, jlong, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncDeleteBuddyList
 * Signature: (ILcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDeleteBuddyList
  (JNIEnv *, jobject, jint, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncDialogSend
 * Signature: (JLjava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDialogSend
  (JNIEnv *, jobject, jlong, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncEndDialog
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncEndDialog
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncLogin
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncLogin
  (JNIEnv *, jobject, jstring, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncMoveGroupBuddyByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;ILcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncMoveGroupBuddyByAccount
  (JNIEnv *, jobject, jobject, jint, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncMoveGroupBuddyById
 * Signature: (JILcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncMoveGroupBuddyById
  (JNIEnv *, jobject, jlong, jint, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncReLogin
 * Signature: (Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncReLogin
  (JNIEnv *, jobject, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncRemoveFromBlacklistByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncRemoveFromBlacklistByAccount
  (JNIEnv *, jobject, jobject, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncRemoveFromBlacklistById
 * Signature: (JLcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncRemoveFromBlacklistById
  (JNIEnv *, jobject, jlong, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncRemoveFromBlacklistByUri
 * Signature: (Ljava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncRemoveFromBlacklistByUri
  (JNIEnv *, jobject, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncRenameBuddyList
 * Signature: (ILjava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncRenameBuddyList
  (JNIEnv *, jobject, jint, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncSendSms
 * Signature: (JLjava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSendSms
  (JNIEnv *, jobject, jlong, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncSendSmsByMobileNumber
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSendSmsByMobileNumber
  (JNIEnv *, jobject, jstring, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncSendSmsToSelf
 * Signature: (Ljava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSendSmsToSelf
  (JNIEnv *, jobject, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncSetBuddyInfo
 * Signature: (JLjava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSetBuddyInfo
  (JNIEnv *, jobject, jlong, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncSetUerNickname
 * Signature: (Ljava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSetUerNickname
  (JNIEnv *, jobject, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncSetUserImpresa
 * Signature: (Ljava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSetUserImpresa
  (JNIEnv *, jobject, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncSetUserRefuseSmsDayCount
 * Signature: (ILcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSetUserRefuseSmsDayCount
  (JNIEnv *, jobject, jint, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncSetUserStatus
 * Signature: (ILjava/lang/String;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSetUserStatus
  (JNIEnv *, jobject, jint, jstring, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    asyncTestNetwork
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionProxyInfo;Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncTestNetwork
  (JNIEnv *, jobject, jobject, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    beginDialog
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_beginDialog
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    closeNetwork
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_closeNetwork
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    deleteBuddyList
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_deleteBuddyList
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    dialogSend
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_dialogSend
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    endDialog
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_endDialog
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getAccountById
 * Signature: (J)Lcom/honnix/jfetion/impl/data/FetionAccount;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getAccountById
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getAccountGroupId
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getAccountGroupId
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getAccountList
 * Signature: ()Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getAccountList
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getAccountShowName
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;Z)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getAccountShowName
  (JNIEnv *, jobject, jobject, jboolean);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getBlacklist
 * Signature: ()Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getBlacklist
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getExpireTime
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getExpireTime
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getGangById
 * Signature: (J)Lcom/honnix/jfetion/impl/data/FetionGang;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getGangById
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getGangList
 * Signature: ()Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getGangList
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getGangShowName
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionGang;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getGangShowName
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getGroupList
 * Signature: ()Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getGroupList
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getMessage
 * Signature: (J)Lcom/honnix/jfetion/impl/data/FetionMessage;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getMessage
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getOnlineStatusByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getOnlineStatusByAccount
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getOriginalId
 * Signature: (J)I
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getOriginalId
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getOnlineStatusById
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getOnlineStatusById
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getPersonalInfo
 * Signature: ()Lcom/honnix/jfetion/impl/data/FetionPersonalInfo;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getPersonalInfo
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getProxy
 * Signature: ()Lcom/honnix/jfetion/impl/data/FetionProxyInfo;
 */
JNIEXPORT jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getProxy
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getServerAddress
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getServerAddress
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserId
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserMobileNumber
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserMobileNumber
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserPassword
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserPassword
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserRefuseSmsDayCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserRefuseSmsDayCount
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserRefuseSmsDayCountByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserRefuseSmsDayCountByAccount
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserScore
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserScore
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserShowName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserShowName
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserStatus
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserStatus
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    getUserUri
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserUri
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    handleContactRequest
 * Signature: (Ljava/lang/String;IILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_handleContactRequest
  (JNIEnv *, jobject, jstring, jint, jint, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    init
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_init
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isAuthorizedByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isAuthorizedByAccount
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isAuthorizedById
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isAuthorizedById
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isGangById
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isGangById
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isInBlacklistByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isInBlacklistByAccount
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isInBlacklistById
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isInBlacklistById
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isOnlineByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isOnlineByAccount
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isOnlineById
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isOnlineById
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isPCUserByAccount
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionAccount;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isPCUserByAccount
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isPCUserById
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isPCUserById
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    isProxyEnabled
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isProxyEnabled
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    login
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_login
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    logout
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_logout
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    removeFontTag
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_removeFontTag
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    renameBuddyList
 * Signature: (ILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_renameBuddyList
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    sendNudge
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendNudge
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    sendSms
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSms
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    sendSmsByMobileNumber
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSmsByMobileNumber
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    sendSmsToSelf
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSmsToSelf
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    setBuddyInfo
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setBuddyInfo
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    setLongSmsEnabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setLongSmsEnabled
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    setLoginStatus
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setLoginStatus
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    setProxy
 * Signature: (Lcom/honnix/jfetion/impl/data/FetionProxyInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setProxy
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    setProxyEnabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setProxyEnabled
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    setServerAddress
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setServerAddress
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    setSystemMessageEventListener
 * Signature: (Lcom/honnix/jfetion/EventListener;[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setSystemMessageEventListener
  (JNIEnv *, jobject, jobject, jobjectArray);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    setUnknownServerAddress
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setUnknownServerAddress
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    terminate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_terminate
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    updateAccountInfoAll
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_updateAccountInfoAll
  (JNIEnv *, jobject);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    updateAccountInfoById
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_updateAccountInfoById
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
