/*
 * FetionHelper.c
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
 
#ifndef FETIONHELPER_H
#define FETIONHELPER_H

#include <jni.h>
#include <libfetion/libfetion.h>

typedef struct _callback
{
    jobject jeventListener;
    jobjectArray jargs;
} Callback;

typedef enum _callbackFunctionIndex
{
    ASYNC_LOGIN = 0,
    ASYNC_RELOGIN,
    SET_SYSTEM_MESSAGE_EVENT_LISTENER,
    ASYNC_SEND_SMS,
    ASYNC_SEND_SMS_TO_SELF,
    ASYNC_SEND_SMS_BY_MOBILE_NUMBER,
    ASYNC_BEGIN_DIALOG,
    ASYNC_DIALOG_SEND,
    ASYNC_SET_USER_STATUS,
    ASYNC_SET_USER_IMPRESA,
    ASYNC_MOVE_GROUP_BUDDY_BY_ID,
    ASYNC_MOVE_GROUP_BUDDY_BY_ACCOUNT,
    ASYNC_RENAME_BUDDY_LIST,
    ASYNC_ADD_BUDDY_LIST,
    ASYNC_ADD_BUDDY_BY_USER_ID,
    ASYNC_ADD_BUDDY_BY_MOBILE_NUMBER,
    ASYNC_DELETE_BUDDY_LIST,
    ASYNC_SET_BUDDY_INFO,
    ASYNC_DELETE_BUDDY_BY_ID,
    ASYNC_DELETE_BUDDY_BY_ACCOUNT,
    ASYNC_ADD_TO_BLACKLIST_BY_ID,
    ASYNC_ADD_TO_BLACKLIST_BY_ACCOUNT,
    ASYNC_ADD_TO_BLACKLIST_BY_URI,
    ASYNC_REMOVE_FROM_BLACKLIST_BY_ID,
    ASYNC_REMOVE_FROM_BLACKLIST_BY_ACCOUNT,
    ASYNC_REMOVE_FROM_BLACKLIST_BY_URI
} CallbackFunctionIndex;

extern JavaVM* theVM;
extern Callback** callbackArray;
extern CallbackFunctionIndex callbackFunctionIndex;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved);

JNIEXPORT void JNICALL JNI_OnUnLoad(JavaVM* vm, void* reserved);

/*
 * Check whether the given is NULL, if it is, throw NullPointException.
 */
BOOL checkNullPointer(JNIEnv* env, int amount, ...);

/*
 * Build arguments for callback function.
 */
Callback* buildCallBackArgs(JNIEnv* env, jobject jobj, jobjectArray jargs,
    CallbackFunctionIndex index);

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
 * Free memory allocated in Fetion_Account structure.
 */
void destroyFetionAccountStruct(Fetion_Account* account);

/*
 * Build FetionBlacklistItem objct.
 */
jobject buildFetionBlacklistItem(JNIEnv* env, Fetion_Black* blacklistItem);

/*
 * Build FetionGang object.
 */
jobject buildFetionGang(JNIEnv* env, Fetion_Qun* gang);

/*
 * Build Fetion_Qun structure.
 */
Fetion_Qun* buildFetionGangStruct(JNIEnv* env, Fetion_Qun* gang,
                                  jobject jgang);

/*
 * Free memory allocated in Fetion_Qun structure.
 */
void destroyFetionGangStruct(Fetion_Qun* gang);

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
