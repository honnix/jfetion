#ifndef FETIONHELPER_H
#define FETIONHELPER_H

#include <jni.h>

extern JavaVM* theVM;

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved);

/*
 * Build arguments for callback function.
 */
jobjectArray buildCallBackArgs(JNIEnv* env, jobject jobj, jobjectArray jargs);

/*
 * Callback function for EventListener.
 */
void callback(int message, unsigned int wparam, unsigned long lparam, void* args);

/*
 * Build FetionMessage object
 */
jobject buildFetionMessage(JNIEnv* env, Fetion_MSG* message);

/*
 * Build FetionPersonalInfo object
 */
jobject buildFetionPersonalInfo(JNIEnv* env, Fetion_Personal* personalInfo);

#endif
