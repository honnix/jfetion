#include <libfetion/libfetion.h>

#include "FetionImpl.h"

JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_intit
(JNIEnv* env, jobject jobj)
{
    return fx_init();
}

JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_login
(JNIEnv* env, jobject jobj, jstring juid, jstring jpassword)
{
    jboolean isCopy;
    const char* uid = (*env)->GetStringUTFChars(env, juid, &isCopy);
    const char* password = (*env)->GetStringUTFChars(env, jpassword, &isCopy);

    return fs_login(uid, password);
}

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    logout
 * Signature: ()Z
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_logout
(JNIEnv* env, jobject jobj)
{
    fx_loginout();
}

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    sendSmsToSelf
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSmsToSelf
(JNIEnv* env, jobject jobj, jstring jmessage)
{
    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);

    return fs_send_sms_to_self(message);
}

JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_terminate
(JNIEnv* env, jobject jobj)
{
    fx_terminate();
}
