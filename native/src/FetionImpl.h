/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_honnix_jfetion_impl_FetionImpl */

#ifndef _Included_com_honnix_jfetion_impl_FetionImpl
#define _Included_com_honnix_jfetion_impl_FetionImpl
#ifdef __cplusplus
extern "C"
{
#endif
/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    intit
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_intit
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
 * Method:    sendSmsToSelf
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSmsToSelf
(JNIEnv *, jobject, jstring);

/*
 * Class:     com_honnix_jfetion_impl_FetionImpl
 * Method:    terminate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_terminate
(JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
