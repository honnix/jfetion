/*
 * FetionImpl.c
 * 
 * Copyright : (C) 2008 by Honnix
 * Email     : hxliang1982@gmail.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <libfetion/libfetion.h>

#include "FetionImpl.h"
#include "FetionHelper.h"

#define OBJECT_CLASS "java/lang/Object"
#define CLASS_NOT_FOUND_EXCEPTION_CLASS "java/lang/ClassNotFoundException"

#define FETION_MESSAGE_CLASS "com/honnix/jfetion/impl/data/FetionMessage"
#define FETION_MESSAGE_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionMessage not found."

#define FETION_PERSONAL_INFO_CLASS "com/honnix/jfetion/impl/data/FetionPersonalInfo"
#define FETION_PERSONAL_INFO_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionPersonalInfo not found."

#define STRING_CLASS_SIG "Ljava/lang/String;"

JavaVM* theVM = NULL;

jobjectArray buildCallBackArgs(JNIEnv* env, jobject jobj, jobjectArray jargs)
{
    jsize length = (*env)->GetArrayLength(env, jargs);
    jclass elementClass = (*env)->FindClass(env, OBJECT_CLASS);
    jobjectArray array = (*env)->NewGlobalRef(env,
                                              (*env)->NewObjectArray(env, length + 1,
                                                                     elementClass, NULL));

    (*env)->SetObjectArrayElement(env, array, 0, jobj);

    int index;
    for (index = 1; index < length + 1; ++index )
    {
        (*env)->SetObjectArrayElement(env, array, index,
                                      (*env)->GetObjectArrayElement(
                                          env, jargs, index - 1));
    }

    return array;
}

void callback(int message, unsigned int wparam, unsigned long lparam,
              void* args)
{
    JNIEnv* env = NULL;
    JavaVMAttachArgs vmAttachArgs;

    vmAttachArgs.version = JNI_VERSION_1_2;
    vmAttachArgs.name = "Callback thread";
    vmAttachArgs.group = NULL;

    if ((*theVM)->AttachCurrentThread(theVM, (void**) &env, &vmAttachArgs) != 0)
    {
        return;
    }
    
    jobjectArray jargs = (jobjectArray) args;
    jobject jobj = (*env)->GetObjectArrayElement(env, jargs, 0);
    jclass eventListenerClass = (*env)->GetObjectClass(env, jobj);
    jmethodID callbackMethod = (*env)->GetMethodID(env, eventListenerClass,
                                                   "callback", "([Ljava/lang/Object;)V");
    jsize length = (*env)->GetArrayLength(env, jargs);
    jclass elementClass = (*env)->FindClass(env, OBJECT_CLASS);
    jobjectArray array = (*env)->NewObjectArray(env, length - 1,
                                                elementClass, NULL);

    int index;
    for (index = 0; index < length - 1; ++index )
    {
        (*env)->SetObjectArrayElement(env, array, index,
                                      (*env)->GetObjectArrayElement(
                                          env, jargs, index + 1));
    }

    (*env)->CallVoidMethod(env, jobj, callbackMethod, array);

    (*env)->DeleteGlobalRef(env, jargs);
}

jobject buildFetionMessage(JNIEnv* env, Fetion_MSG* message)
{
    jclass messageClass = (*env)->FindClass(env, FETION_MESSAGE_CLASS);

    if (messageClass == NULL)
    {
        jclass exceptionClass = (*env)->FindClass(env, CLASS_NOT_FOUND_EXCEPTION_CLASS);

        (*env)->ThrowNew(env, exceptionClass, FETION_MESSAGE_CLASS_NOT_FOUND);
    }

    jmethodID constructor = (*env)->GetMethodID(env, messageClass,
                                                   "<init>", "()V");
    jobject jmessage = (*env)->NewObject(env, messageClass, constructor);

    jfieldID jidField = (*env)->GetFieldID(env, messageClass, "id", "J");
    (*env)->SetLongField(env, jmessage, jidField, message->uid);

    if (message->message != NULL)
    {
        jstring jrealMessage = (*env)->NewStringUTF(env, message->message);
        jfieldID jrealMessageField = (*env)->GetFieldID(env, messageClass, "message", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jmessage, jrealMessageField, jrealMessage);
    }

    if (message->msgformat != NULL)
    {
        jstring jmessageFormat = (*env)->NewStringUTF(env, message->msgformat);
        jfieldID jmessageFormatField = (*env)->GetFieldID(env, messageClass, "messageFormat", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jmessage, jmessageFormatField, jmessageFormat);
    }

    return jmessage;
}

jobject buildFetionPersonalInfo(JNIEnv* env, Fetion_Personal* personalInfo)
{
    jclass personalInfoClass = (*env)->FindClass(env, FETION_PERSONAL_INFO_CLASS);

    if (personalInfoClass == NULL)
    {
        jclass exceptionClass = (*env)->FindClass(env, CLASS_NOT_FOUND_EXCEPTION_CLASS);

        (*env)->ThrowNew(env, exceptionClass, FETION_PERSONAL_INFO_CLASS_NOT_FOUND);
    }

    jmethodID constructor = (*env)->GetMethodID(env, personalInfoClass,
                                                   "<init>", "()V");
    jobject jpersonalInfo = (*env)->NewObject(env, personalInfoClass, constructor);

    if (personalInfo->nickname != NULL)
    {
        jstring jnickname = (*env)->NewStringUTF(env, personalInfo->nickname);
        jfieldID jnicknameField = (*env)->GetFieldID(env, personalInfoClass, "nickname", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jnicknameField, jnickname);
    }

    if (personalInfo->impresa != NULL)
    {
        jstring jimpresa = (*env)->NewStringUTF(env, personalInfo->impresa);
        jfieldID jimpresaField = (*env)->GetFieldID(env, personalInfoClass, "impresa", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jimpresaField, jimpresa);
    }

    jfieldID jgenderField = (*env)->GetFieldID(env, personalInfoClass, "gender", "I");
    (*env)->SetIntField(env, jpersonalInfo, jgenderField, personalInfo->gender);

    if (personalInfo->nation != NULL)
    {
        jstring jnation = (*env)->NewStringUTF(env, personalInfo->nation);
        jfieldID jnationField = (*env)->GetFieldID(env, personalInfoClass, "nation", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jnationField, jnation);
    }

    if (personalInfo->province != NULL)
    {
        jstring jprovince = (*env)->NewStringUTF(env, personalInfo->province);
        jfieldID jprovinceField = (*env)->GetFieldID(env, personalInfoClass, "province", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jprovinceField, jprovince);
    }
    
    jfieldID jcityField = (*env)->GetFieldID(env, personalInfoClass, "city", "I");
    (*env)->SetIntField(env, jpersonalInfo, jcityField, personalInfo->city);

    jfieldID jivrEnabledField = (*env)->GetFieldID(env, personalInfoClass, "ivrEnabled", "I");
    (*env)->SetIntField(env, jpersonalInfo, jivrEnabledField, personalInfo->ivr_enabled);
    
    jfieldID jportraitCrc = (*env)->GetFieldID(env, personalInfoClass, "portraitCrc", "I");
    (*env)->SetIntField(env, jpersonalInfo, jportraitCrc, personalInfo->portrait_crc);

    jfieldID jprovisioning = (*env)->GetFieldID(env, personalInfoClass, "provisioning", "I");
    (*env)->SetIntField(env, jpersonalInfo, jprovisioning, personalInfo->provisioning);

    if (personalInfo->mobile_no != NULL)
    {
        jstring jmobileNumber = (*env)->NewStringUTF(env, personalInfo->mobile_no);
        jfieldID jmobileNumberField = (*env)->GetFieldID(env, personalInfoClass, "mobileNumber", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jmobileNumberField, jmobileNumber);
    }

    return jpersonalInfo;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    theVM = vm;

    return JNI_VERSION_1_2;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_init
(JNIEnv* env, jobject jobj)
{
    return fx_init();
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_terminate
(JNIEnv* env, jobject jobj)
{
    fx_terminate();
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_closeNetwork
(JNIEnv* env, jobject jobj)
{
    return fx_close_network();
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_login
(JNIEnv* env, jobject jobj, jstring juserId, jstring jpassword)
{
    jboolean isCopy;
    const char* userId = (*env)->GetStringUTFChars(env, juserId, &isCopy);
    const char* password = (*env)->GetStringUTFChars(env, jpassword, &isCopy);

    jboolean result = fs_login(userId, password);

    (*env)->ReleaseStringUTFChars(env, juserId, userId);
    (*env)->ReleaseStringUTFChars(env, jpassword, password);

    return result;
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setLoginStatus
(JNIEnv* env, jobject jobj, jint jstatus)
{
    fx_set_login_status(jstatus);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncLogin
(JNIEnv* env, jobject jobj, jstring juserId, jstring jpassword,
 jobject jeventListener, jobjectArray jargs)
{
    jboolean isCopy;
    const char* userId = (*env)->GetStringUTFChars(env, juserId, &isCopy);
    const char* password = (*env)->GetStringUTFChars(env, jpassword, &isCopy);

    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);

    jint result = fx_login(userId, password, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, juserId, userId);
    (*env)->ReleaseStringUTFChars(env, jpassword, password);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncReLogin
(JNIEnv* env, jobject jobj, jobject jeventListener, jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);

    return fx_relogin(callback, callbackArgs);
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_logout
(JNIEnv* env, jobject jobj)
{
    fx_loginout();
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setSystemMessageEventListener
(JNIEnv* env, jobject jobj, jobject jeventListener, jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);

    fx_set_system_msg_cb(callback, callbackArgs);
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getMessage
(JNIEnv* env, jobject jobj, jlong jid)
{
    Fetion_MSG* message = fx_get_msg(jid);
    jobject jmessage = buildFetionMessage(env, message);

    fx_destroy_msg(message);

    return jmessage;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSms
(JNIEnv* env, jobject jobj, jlong jwho, jstring jmessage)
{
    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);

    jboolean result = fs_send_sms(jwho, message);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSmsByMobileNumber
(JNIEnv* env, jobject job, jstring jmobileNumber, jstring jmessage)
{
    jboolean isCopy;
    const char* mobileNumber = (*env)->GetStringUTFChars(env, jmobileNumber, &isCopy);
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);

    jboolean result = fs_send_sms_by_mobile_no(mobileNumber, message);

    (*env)->ReleaseStringUTFChars(env, jmobileNumber, mobileNumber);
    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSmsToSelf
(JNIEnv* env, jobject jobj, jstring jmessage)
{
    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);

    jboolean result = fs_send_sms_to_self(message);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSendSms
(JNIEnv* env, jobject jobj, jlong jwho, jstring jmessage, 
 jobject jeventListener, jobjectArray jargs)
{
    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);
    
    jint result = fx_send_sms(jwho, message, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSendSmsToSelf
(JNIEnv* env, jobject jobj, jstring jmessage, 
 jobject jeventListener, jobjectArray jargs)
{
    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);

    jint result = fx_send_sms_to_self(message, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSendSmsByMobileNumber
(JNIEnv* env, jobject jobj, jstring jmobileNumber, jstring jmessage, 
 jobject jeventListener, jobjectArray jargs)
{
    jboolean isCopy;
    const char* mobileNumber = (*env)->GetStringUTFChars(env, jmobileNumber, &isCopy);
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);

    jint result = fx_send_sms_by_mobile_no(mobileNumber, message, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jmobileNumber, mobileNumber);
    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_beginDialog
(JNIEnv* env, jobject jobj, jlong jwho)
{
    return fs_begin_dialog(jwho);
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_dialogSend
(JNIEnv* env, jobject jobj, jlong jwho, jstring jmessage)
{
    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);

    jboolean result = fs_dialog_send(jwho, message);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_endDialog
(JNIEnv* env, jobject jobj, jlong jwho)
{
    fs_end_dialog(jwho);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncBeginDialog
(JNIEnv* env, jobject jobj, jlong jwho, 
 jobject jeventListener, jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);

    return fx_begin_dialog(jwho, callback, callbackArgs);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDialogSend
(JNIEnv* env, jobject jobj, jlong jwho, jstring jmessage, 
 jobject jeventListener, jobjectArray jargs)
{
    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);

    jint result = fx_dialog_send(jwho, message, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncEndDialog
(JNIEnv* env, jobject jobj, jlong jwho)
{
    fx_end_dialog(jwho);
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserId
(JNIEnv* env, jobject jobj)
{
    const char* userId = fx_get_usr_uid();

    return (*env)->NewStringUTF(env, userId);
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserPassword
(JNIEnv* env, jobject jobj)
{
    const char* password = fx_get_usr_passwd();

    return (*env)->NewStringUTF(env, password);
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserShowName
(JNIEnv* env, jobject jobj)
{
    const char* showName = fx_get_usr_show_name();

    return (*env)->NewStringUTF(env, showName);
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserUri
(JNIEnv* env, jobject jobj)
{
    const char* userUri = fx_get_usr_uri();

    return (*env)->NewStringUTF(env, userUri);
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserMobileNumber
(JNIEnv* env, jobject jobj)
{
    const char* userMobileNumber = fx_get_usr_mobilenum();

    return (*env)->NewStringUTF(env, userMobileNumber);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserScore
(JNIEnv* env, jobject jobj)
{
    return fx_get_usr_score();
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSetUserState
(JNIEnv* env, jobject jobj, jint jstate, jstring jdescription,
 jobject jeventListener, jobjectArray jargs)
{
    jboolean isCopy;
    const char* description = (*env)->GetStringUTFChars(env, jdescription, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);    

    int result = fx_set_user_state(jstate, (char*) description, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jdescription, description);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserState
(JNIEnv* env, jobject jobj)
{
    return fx_get_user_state();
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSetUserImpresa
(JNIEnv* env, jobject jobj, jstring jimpresa, 
 jobject jeventListener, jobjectArray jargs)
{
    jboolean isCopy;
    const char* impresa = (*env)->GetStringUTFChars(env, jimpresa, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jobj, jargs);    

    int result = fx_set_user_impresa(impresa, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jimpresa, impresa);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getExpireTime
(JNIEnv* env, jobject jobj)
{
    return fx_get_expirestime();
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getPersonalInfo
(JNIEnv* env, jobject obj)
{
    Fetion_Personal* personalInfo = fx_data_get_PersonalInfo();
}
