#ifndef FETIONHELPER_H
#define FETIONHELPER_H

#include <jni.h>
#include <libfetion/libfetion.h>

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
 * Build common jobject.
 */
jobject buildObject(JNIEnv* env, jclass* objectClass, const char* objectClassPath, 
                    const char* classNotFoundMessage);

/*
 * Build FetionMessage object.
 */
jobject buildFetionMessage(JNIEnv* env, Fetion_MSG* message);

/*
 * Build FetionPersonalInfo object.
 */
jobject buildFetionPersonalInfo(JNIEnv* env, Fetion_Personal* personalInfo);

/*
 * Build FetionGroup object.
 */
jobject buildFetionGroup(JNIEnv* env, Fetion_Group* group);

/*
 * Build FetionAccount object.
 */
jobject buildFetionAccount(JNIEnv* env, Fetion_Account* account);

/*
 * Build Fetion_Account structure.
 */
Fetion_Account* buildFetionAccountStruct(JNIEnv* env, Fetion_Account* account,
                                         jobject jaccount);

/*
 * Build FetionBlacklistItem objct.
 */
jobject buildFetionBlacklistItem(JNIEnv* env, Fetion_Black* blacklistItem);

/*
 * Build FetionGang object.
 */
jobject buildFetionGang(JNIEnv* env, Fetion_Qun* gang);

/*
 * Build FetionGangInfo object.
 */
jobject buildFetionGangInfo(JNIEnv* env, Fetion_QunInfo* gangInfo);

/*
 * Build FetionGangMember object.
 */
jobject buildFetionGangMember(JNIEnv* env, Fetion_QunMember* gangMember);

/*
 * Build ArrayList object.
 */
jobject buildArrayList(JNIEnv* env);

/*
 * Insert element to ArrayList object.
 */
jboolean insertToArrayList(JNIEnv* env, jobject jarrayList, jobject jelement);

#endif
