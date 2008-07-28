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

#include <stdlib.h>
#include <string.h>
#include <libfetion/libfetion.h>

#include "FetionImpl.h"
#include "FetionHelper.h"

#ifdef DEBUG
#define DEBUG_INFO(message) fprintf(stderr, message)
#define DEBUG_INFO_A(message, a) fprintf(stderr, message, (a))
#else
#define DEBUG_INFO(message)
#define DEBUG_INFO_A(message, a)
#endif

#define OBJECT_CLASS "java/lang/Object"
#define ARRAY_LIST_CLASS "java/util/ArrayList"
#define CLASS_NOT_FOUND_EXCEPTION_CLASS "java/lang/ClassNotFoundException"
#define NULL_POINTER_EXCEPTION_CLASS "java/lang/NullPointerException"

#define FETION_MESSAGE_CLASS "com/honnix/jfetion/impl/data/FetionMessage"
#define FETION_MESSAGE_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionMessage not found."

#define FETION_PERSONAL_INFO_CLASS "com/honnix/jfetion/impl/data/FetionPersonalInfo"
#define FETION_PERSONAL_INFO_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionPersonalInfo not found."

#define FETION_GROUP_CLASS "com/honnix/jfetion/impl/data/FetionGroup"
#define FETION_GROUP_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionGroup not found."

#define FETION_ACCOUNT_CLASS "com/honnix/jfetion/impl/data/FetionAccount"
#define FETION_ACCOUNT_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionAccount not found."

#define FETION_BLACKLIST_ITEM_CLASS "com/honnix/jfetion/impl/data/FetionBlacklistItem"
#define FETION_BLACKLIST_ITEM_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionBlacklistItem not found."

#define FETION_GANG_CLASS "com/honnix/jfetion/impl/data/FetionGang"
#define FETION_GANG_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionGang not found."

#define FETION_GANG_INFO_CLASS "com/honnix/jfetion/impl/data/FetionGangInfo"
#define FETION_GANG_INFO_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionGangInfo not found."

#define FETION_GANG_MEMBER_CLASS "com/honnix/jfetion/impl/data/FetionGangMember"
#define FETION_GANG_MEMBER_CLASS_NOT_FOUND \
    "Class com/honnix/jfetion/impl/data/FetionGangMember not found."

#define STRING_CLASS_SIG "Ljava/lang/String;"
#define ARRAY_LIST_CLASS_SIG "Ljava/util/ArrayList;"
#define FETION_PERSONAL_INFO_CLASS_SIG "Lcom/honnix/jfetion/impl/data/FetionPersonalInfo;"
#define FETION_GANG_INFO_CLASS_SIG "Lcom/honnix/jfetion/impl/data/FetionGangInfo;"

JavaVM* theVM = NULL;

BOOL checkNullPointer(JNIEnv* env, void* pointer)
{
    BOOL isNull = FALSE;

    if (pointer == NULL)
    {
        isNull = TRUE;
        jclass exceptionClass = (*env)->FindClass(env, NULL_POINTER_EXCEPTION_CLASS);

        (*env)->ThrowNew(env, exceptionClass, "Null pointer exception for some argument.");
    }

    return isNull;
}

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
                                                   "callback", "(IJJ[Ljava/lang/Object;)V");
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

    (*env)->CallVoidMethod(env, jobj, callbackMethod, message, (jlong) wparam, (jlong) lparam, array);
    if ((*env)->ExceptionOccurred(env))
    {
        (*env)->ExceptionDescribe(env);
    }

    (*env)->DeleteGlobalRef(env, jargs);
}

jobject buildObject(JNIEnv* env, jclass* objectClass, const char* objectClassPath, 
                    const char* classNotFoundMessage)
{
    (*objectClass)  = (*env)->FindClass(env, objectClassPath);

    if ((*objectClass) == NULL)
    {
        jclass exceptionClass = (*env)->FindClass(env, CLASS_NOT_FOUND_EXCEPTION_CLASS);

        (*env)->ThrowNew(env, exceptionClass, classNotFoundMessage);
    }

    jmethodID constructor = (*env)->GetMethodID(env, (*objectClass),
                                                   "<init>", "()V");
    jobject jobj = (*env)->NewObject(env, (*objectClass), constructor);

    return jobj;
}

jobject buildFetionMessage(JNIEnv* env, Fetion_MSG* message)
{
    jclass messageClass = NULL;
    jobject jmessage = buildObject(env, &messageClass, FETION_MESSAGE_CLASS,
                                   FETION_MESSAGE_CLASS_NOT_FOUND);

    jfieldID jidField = (*env)->GetFieldID(env, messageClass, "id", "J");
    (*env)->SetLongField(env, jmessage, jidField, message->uid);

    if (message->message != NULL)
    {
        jstring jrealMessage = (*env)->NewStringUTF(env, message->message);
        jfieldID jrealMessageField = (*env)->GetFieldID(env, messageClass, "message", 
                                                        STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jmessage, jrealMessageField, jrealMessage);
    }

    if (message->msgformat != NULL)
    {
        jstring jmessageFormat = (*env)->NewStringUTF(env, message->msgformat);
        jfieldID jmessageFormatField = (*env)->GetFieldID(env, messageClass, "messageFormat", 
                                                          STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jmessage, jmessageFormatField, jmessageFormat);
    }

    return jmessage;
}

jobject buildFetionPersonalInfo(JNIEnv* env, Fetion_Personal* personalInfo)
{
    jclass personalInfoClass = NULL;
    jobject jpersonalInfo = buildObject(env, &personalInfoClass, FETION_PERSONAL_INFO_CLASS,
                                        FETION_PERSONAL_INFO_CLASS_NOT_FOUND);

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
    
    jfieldID jportraitCrcField = (*env)->GetFieldID(env, personalInfoClass, "portraitCrc", "I");
    (*env)->SetIntField(env, jpersonalInfo, jportraitCrcField, personalInfo->portrait_crc);

    jfieldID jprovisioningField = (*env)->GetFieldID(env, personalInfoClass, "provisioning", "I");
    (*env)->SetIntField(env, jpersonalInfo, jprovisioningField, personalInfo->provisioning);

    if (personalInfo->mobile_no != NULL)
    {
        jstring jmobileNumber = (*env)->NewStringUTF(env, personalInfo->mobile_no);
        jfieldID jmobileNumberField = (*env)->GetFieldID(env, personalInfoClass, "mobileNumber", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jmobileNumberField, jmobileNumber);
    }

    if (personalInfo->name != NULL)
    {
        jstring jname = (*env)->NewStringUTF(env, personalInfo->name);
        jfieldID jnameField = (*env)->GetFieldID(env, personalInfoClass, "name", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jnameField, jname);
    }

    if (personalInfo->birth_date != NULL)
    {
        jstring jbirthday = (*env)->NewStringUTF(env, personalInfo->birth_date);
        jfieldID jbirthdayField = (*env)->GetFieldID(env, personalInfoClass, "birthday", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jbirthdayField, jbirthday);
    }

    jfieldID jbirthdayValidField = (*env)->GetFieldID(env, personalInfoClass, "birthdayValid", "I");
    (*env)->SetIntField(env, jpersonalInfo, jbirthdayValidField, personalInfo->birthday_valid);

    jfieldID jlunarAnimalField = (*env)->GetFieldID(env, personalInfoClass, "lunarAnimal", "I");
    (*env)->SetIntField(env, jpersonalInfo, jlunarAnimalField, personalInfo->lunar_animal);

    jfieldID jhoroscopeField = (*env)->GetFieldID(env, personalInfoClass, "horoscope", "I");
    (*env)->SetIntField(env, jpersonalInfo, jhoroscopeField, personalInfo->horoscope);

    if (personalInfo->profile != NULL)
    {
        jstring jprofile = (*env)->NewStringUTF(env, personalInfo->profile);
        jfieldID jprofileField = (*env)->GetFieldID(env, personalInfoClass, "profile", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jprofileField, jprofile);
    }

    jfieldID jbloodTypeField = (*env)->GetFieldID(env, personalInfoClass, "bloodType", "I");
    (*env)->SetIntField(env, jpersonalInfo, jbloodTypeField, personalInfo->blood_type);

    if (personalInfo->occupation != NULL)
    {
        jstring joccupation = (*env)->NewStringUTF(env, personalInfo->occupation);
        jfieldID joccupationField = (*env)->GetFieldID(env, personalInfoClass, "occupation", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, joccupationField, joccupation);
    }

    if (personalInfo->hobby != NULL)
    {
        jstring jhobby = (*env)->NewStringUTF(env, personalInfo->hobby);
        jfieldID jhobbyField = (*env)->GetFieldID(env, personalInfoClass, "hobby", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jhobbyField, jhobby);
    }

    if (personalInfo->personal_email != NULL)
    {
        jstring jpersonalEmail = (*env)->NewStringUTF(env, personalInfo->personal_email);
        jfieldID jpersonalEmailField = (*env)->GetFieldID(env, personalInfoClass, "personalEmail", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jpersonalEmailField, jpersonalEmail);
    }

    if (personalInfo->work_email != NULL)
    {
        jstring jworkEmail = (*env)->NewStringUTF(env, personalInfo->work_email);
        jfieldID jworkEmailField = (*env)->GetFieldID(env, personalInfoClass, "workEmail", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jworkEmailField, jworkEmail);
    }

    if (personalInfo->other_email != NULL)
    {
        jstring jotherEmail = (*env)->NewStringUTF(env, personalInfo->other_email);
        jfieldID jotherEmailField = (*env)->GetFieldID(env, personalInfoClass, "otherEmail", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jotherEmailField, jotherEmail);
    }

    jfieldID jprimaryEmailField = (*env)->GetFieldID(env, personalInfoClass, "primaryEmail", "I");
    (*env)->SetIntField(env, jpersonalInfo, jprimaryEmailField, personalInfo->primary_email);

    if (personalInfo->job_title != NULL)
    {
        jstring jjobTitle = (*env)->NewStringUTF(env, personalInfo->job_title);
        jfieldID jjobTitleField = (*env)->GetFieldID(env, personalInfoClass, "jobTitle", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jjobTitleField, jjobTitle);
    }

    if (personalInfo->home_phone != NULL)
    {
        jstring jhomePhone = (*env)->NewStringUTF(env, personalInfo->home_phone);
        jfieldID jhomePhoneField = (*env)->GetFieldID(env, personalInfoClass, "homePhone", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jhomePhoneField, jhomePhone);
    }

    if (personalInfo->work_phone != NULL)
    {
        jstring jworkPhone = (*env)->NewStringUTF(env, personalInfo->work_phone);
        jfieldID jworkPhoneField = (*env)->GetFieldID(env, personalInfoClass, "workPhone", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jworkPhoneField, jworkPhone);
    }

    if (personalInfo->other_phone != NULL)
    {
        jstring jotherPhone = (*env)->NewStringUTF(env, personalInfo->other_phone);
        jfieldID jotherPhoneField = (*env)->GetFieldID(env, personalInfoClass, "otherPhone", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jotherPhoneField, jotherPhone);
    }

    if (personalInfo->company != NULL)
    {
        jstring jcompany = (*env)->NewStringUTF(env, personalInfo->company);
        jfieldID jcompanyField = (*env)->GetFieldID(env, personalInfoClass, "company", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jcompanyField, jcompany);
    }

    if (personalInfo->company_website != NULL)
    {
        jstring jcompanyWebsite = (*env)->NewStringUTF(env, personalInfo->company_website);
        jfieldID jcompanyWebsiteField = (*env)->GetFieldID(env, personalInfoClass, "companyWebsite", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jpersonalInfo, jcompanyWebsiteField, jcompanyWebsite);
    }

    jfieldID jmatchEnabledField = (*env)->GetFieldID(env, personalInfoClass, "matchEnabled", "I");
    (*env)->SetIntField(env, jpersonalInfo, jmatchEnabledField, personalInfo->match_enabled);

    return jpersonalInfo;
}

jobject buildFetionGroup(JNIEnv* env, Fetion_Group* group)
{
    jclass groupClass;
    jobject jgroup = buildObject(env, &groupClass, FETION_GROUP_CLASS,
                                 FETION_GROUP_CLASS_NOT_FOUND);

    jfieldID jidField = (*env)->GetFieldID(env, groupClass, "id", "J");
    (*env)->SetLongField(env, jgroup, jidField, group->id);

    if (group->name != NULL)
    {
        jstring jname = (*env)->NewStringUTF(env, group->name);
        jfieldID jnameField = (*env)->GetFieldID(env, groupClass, "name", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgroup, jnameField, jname);
    }

    return jgroup;
}

jobject buildFetionAccount(JNIEnv* env, Fetion_Account* account)
{
    jclass accountClass = NULL;
    jobject jaccount = buildObject(env, &accountClass, FETION_ACCOUNT_CLASS,
                                   FETION_ACCOUNT_CLASS_NOT_FOUND);

    jfieldID jidField = (*env)->GetFieldID(env, accountClass, "id", "J");
    (*env)->SetLongField(env, jaccount, jidField, account->id);

    if (account->uri != NULL)
    {
        jstring juri = (*env)->NewStringUTF(env, account->uri);
        jfieldID juriField = (*env)->GetFieldID(env, accountClass, "uri", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jaccount, juriField, juri);
    }

    if (account->local_name != NULL)
    {
        jstring jlocalName = (*env)->NewStringUTF(env, account->local_name);
        jfieldID jlocalNameField = (*env)->GetFieldID(env, accountClass, "localName", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jaccount, jlocalNameField, jlocalName);
    }

    if (account->buddy_lists != NULL)
    {
        jstring jbuddyList = (*env)->NewStringUTF(env, account->buddy_lists);
        jfieldID jbuddyListField = (*env)->GetFieldID(env, accountClass, "buddyList", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jaccount, jbuddyListField, jbuddyList);
    }

    jfieldID jgroupIdField = (*env)->GetFieldID(env, accountClass, "groupId", "I");
    (*env)->SetIntField(env, jaccount, jgroupIdField, account->group_id);

    jfieldID jrelationStatusField = (*env)->GetFieldID(env, accountClass, "relationStatus", "I");
    (*env)->SetIntField(env, jaccount, jrelationStatusField, account->relation_status);

    jfieldID jonlineNotifyField = (*env)->GetFieldID(env, accountClass, "onlineNotify", "I");
    (*env)->SetIntField(env, jaccount, jonlineNotifyField, account->online_notify);

    jfieldID jstatusCodeField = (*env)->GetFieldID(env, accountClass, "statusCode", "I");
    (*env)->SetIntField(env, jaccount, jstatusCodeField, account->status_code);

    jfieldID jonlineStatusField = (*env)->GetFieldID(env, accountClass, "onlineStatus", "I");
    (*env)->SetIntField(env, jaccount, jonlineStatusField, account->online_status);

    jfieldID jportraitCrcField = (*env)->GetFieldID(env, accountClass, "portraitCrc", "J");
    (*env)->SetLongField(env, jaccount, jportraitCrcField, account->portrait_crc);

    if (account->personal != NULL)
    {
        jfieldID jpersonalInfoField = (*env)->GetFieldID(env, accountClass, "personalInfo", 
                                                         FETION_PERSONAL_INFO_CLASS_SIG);
        jobject jpersonalInfo = buildFetionPersonalInfo(env, account->personal);
        (*env)->SetObjectField(env, jaccount, jpersonalInfoField, jpersonalInfo);
    }

    jfieldID juserTypeField = (*env)->GetFieldID(env, accountClass, "userType", "I");
    (*env)->SetIntField(env, jaccount, juserTypeField, account->usr_type);

    return jaccount;
}

Fetion_Account* buildFetionAccountStruct(JNIEnv* env, Fetion_Account* account,
                                         jobject jaccount)
{
    jclass accountClass = (*env)->GetObjectClass(env, jaccount);

    jfieldID jidField = (*env)->GetFieldID(env, accountClass, "id", "J");
    account->id = (*env)->GetLongField(env, jaccount, jidField);

    jboolean isCopy;

    jfieldID juriField = (*env)->GetFieldID(env, accountClass, "uri", STRING_CLASS_SIG);
    jstring juri = (*env)->GetObjectField(env, jaccount, juriField);
    account->uri = NULL;
    if (juri != NULL)
    {
        const char* src = (*env)->GetStringUTFChars(env, juri, &isCopy);
        char* dest = (char*) malloc(strlen(src) + 1);

        account->uri = strcpy(dest, src);
        (*env)->ReleaseStringUTFChars(env, juri, src);
    }

    jfieldID jlocalNameField = (*env)->GetFieldID(env, accountClass, "localName", STRING_CLASS_SIG);
    jstring jlocalName = (*env)->GetObjectField(env, jaccount, jlocalNameField);
    account->local_name = NULL;
    if (jlocalName != NULL)
    {
        const char* src = (*env)->GetStringUTFChars(env, jlocalName, &isCopy);
        char* dest = (char*) malloc(strlen(src) + 1);

        account->local_name = strcpy(dest, src);
        (*env)->ReleaseStringUTFChars(env, jlocalName, src);
    }

    jfieldID jbuddyListField = (*env)->GetFieldID(env, accountClass, "buddyList", STRING_CLASS_SIG);
    jstring jbuddyList = (*env)->GetObjectField(env, jaccount, jbuddyListField);
    account->buddy_lists = NULL;
    if (jbuddyList != NULL)
    {
        const char* src = (*env)->GetStringUTFChars(env, jbuddyList, &isCopy);
        char* dest = (char*) malloc(strlen(src) + 1);

        account->buddy_lists = strcpy(dest, src);
        (*env)->ReleaseStringUTFChars(env, jbuddyList, src);
    }

    jfieldID jgroupIdField = (*env)->GetFieldID(env, accountClass, "groupId", "I");
    account->group_id = (*env)->GetIntField(env, jaccount, jgroupIdField);

    jfieldID jrelationStatusField = (*env)->GetFieldID(env, accountClass, "relationStatus", "I");
    account->relation_status = (*env)->GetIntField(env, jaccount, jrelationStatusField);

    jfieldID jonlineNotifyField = (*env)->GetFieldID(env, accountClass, "onlineNotify", "I");
    account->online_notify = (*env)->GetIntField(env, jaccount, jonlineNotifyField);

    jfieldID jstatusCodeField = (*env)->GetFieldID(env, accountClass, "statusCode", "I");
    account->status_code = (*env)->GetIntField(env, jaccount, jstatusCodeField);

    jfieldID jonlineStatusField = (*env)->GetFieldID(env, accountClass, "onlineStatus", "I");
    account->online_status = (*env)->GetIntField(env, jaccount, jonlineStatusField);

    jfieldID jportraitCrcField = (*env)->GetFieldID(env, accountClass, "portraitCrc", "J");
    account->portrait_crc = (*env)->GetLongField(env, jaccount, jportraitCrcField);

    /* 
     * I don't want to build personal info. 
     * It just sucks and seems not contain much useful information.
     */
    account->personal = NULL;

    jfieldID juserTypeField = (*env)->GetFieldID(env, accountClass, "userType", "I");
    account->usr_type = (*env)->GetIntField(env, jaccount, juserTypeField);

    return account;
}

void destroyFetionAccountStruct(Fetion_Account* account)
{
    free(account->uri);
    free(account->local_name);
    free(account->buddy_lists);
}

jobject buildFetionBlacklistItem(JNIEnv* env, Fetion_Black* blacklistItem)
{
    jclass blacklistItemClass = NULL;
    jobject jblacklistItem = buildObject(env, &blacklistItemClass, FETION_BLACKLIST_ITEM_CLASS,
                                         FETION_BLACKLIST_ITEM_CLASS_NOT_FOUND);

    jfieldID jidField = (*env)->GetFieldID(env, blacklistItemClass, "id", "J");
    (*env)->SetLongField(env, jblacklistItem, jidField, blacklistItem->uid);

    if (blacklistItem->uri != NULL)
    {
        jstring juri = (*env)->NewStringUTF(env, blacklistItem->uri);
        jfieldID juriField = (*env)->GetFieldID(env, blacklistItemClass, "uri", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jblacklistItem, juriField, juri);
    }

    if (blacklistItem->local_name != NULL)
    {
        jstring jlocalName = (*env)->NewStringUTF(env, blacklistItem->local_name);
        jfieldID jlocalNameField = (*env)->GetFieldID(env, blacklistItemClass, "localName", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jblacklistItem, jlocalNameField, jlocalName);
    }

    return jblacklistItem;
}

jobject buildFetionGang(JNIEnv* env, Fetion_Qun* gang)
{
    jclass gangClass;
    jobject jgang = buildObject(env, &gangClass, FETION_GANG_CLASS,
                                FETION_GANG_CLASS_NOT_FOUND);

    jfieldID jidField = (*env)->GetFieldID(env, gangClass, "id", "J");
    (*env)->SetLongField(env, jgang, jidField, gang->id);

    if (gang->uri != NULL)
    {
        jstring juri = (*env)->NewStringUTF(env, gang->uri);
        jfieldID juriField = (*env)->GetFieldID(env, gangClass, "uri", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgang, juriField, juri);
    }

    jfieldID jidentityField = (*env)->GetFieldID(env, gangClass, "identity", "I");
    (*env)->SetIntField(env, jgang, jidentityField, gang->identity);

    if (gang->quninfo != NULL)
    {
        jfieldID jgangInfoField = (*env)->GetFieldID(env, gangClass, "gangInfo", 
                                                         FETION_GANG_INFO_CLASS_SIG);
        jobject jgangInfo = buildFetionGangInfo(env, gang->quninfo);
        (*env)->SetObjectField(env, jgang, jgangInfoField, jgangInfo);
    }

    return jgang;
}

Fetion_Qun* buildFetionGangStruct(JNIEnv* env, Fetion_Qun* gang, jobject jgang)
{
    jclass gangClass = (*env)->GetObjectClass(env, jgang);

    jfieldID jidField = (*env)->GetFieldID(env, gangClass, "id", "J");
    gang->id = (*env)->GetLongField(env, jgang, jidField);

    jboolean isCopy;

    jfieldID juriField = (*env)->GetFieldID(env, gangClass, "uri", STRING_CLASS_SIG);
    jstring juri = (*env)->GetObjectField(env, jgang, juriField);
    gang->uri = NULL;
    if (juri != NULL)
    {
        const char* src = (*env)->GetStringUTFChars(env, juri, &isCopy);
        char* dest = (char*) malloc(strlen(src) + 1);

        gang->uri = strcpy(dest, src);
        (*env)->ReleaseStringUTFChars(env, juri, src);
    }
    
    jfieldID jidentityField = (*env)->GetFieldID(env, gangClass, "identity", "I");
    gang->id = (*env)->GetIntField(env, jgang, jidentityField);

    /*
     * Why bother Fetion_QunInfo?
     */
    gang->quninfo = NULL;

    return gang;
}

void destroyFetionGangStruct(Fetion_Qun* gang)
{
    free(gang->uri);
}

jobject buildFetionGangInfo(JNIEnv* env, Fetion_QunInfo* gangInfo)
{
    jclass gangInfoClass = NULL;
    jobject jgangInfo = buildObject(env, &gangInfoClass, FETION_GANG_INFO_CLASS,
                                    FETION_GANG_INFO_CLASS_NOT_FOUND);

    if (gangInfo->uri != NULL)
    {
        jstring juri = (*env)->NewStringUTF(env, gangInfo->uri);
        jfieldID juriField = (*env)->GetFieldID(env, gangInfoClass, "uri", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangInfo, juriField, juri);
    }

    jfieldID jgroupAttributesVersionField = (*env)->GetFieldID(env, gangInfoClass, 
                                                               "groupAttributesVersion", "I");
    (*env)->SetIntField(env, jgangInfo, jgroupAttributesVersionField, 
                        gangInfo->group_attributes_version);

    if (gangInfo->name != NULL)
    {
        jstring jname = (*env)->NewStringUTF(env, gangInfo->name);
        jfieldID jnameField = (*env)->GetFieldID(env, gangInfoClass, "name", STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangInfo, jnameField, jname);
    }

    jfieldID jcategoryField = (*env)->GetFieldID(env, gangInfoClass, 
                                                 "category", "I");
    (*env)->SetIntField(env, jgangInfo, jcategoryField, gangInfo->category);

    if (gangInfo->introduce != NULL)
    {
        jstring jintroduction = (*env)->NewStringUTF(env, gangInfo->introduce);
        jfieldID jintroductionField = (*env)->GetFieldID(env, gangInfoClass, "introduction", 
                                                         STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangInfo, jintroductionField, jintroduction);
    }

    if (gangInfo->bulletin != NULL)
    {
        jstring jbulletin = (*env)->NewStringUTF(env, gangInfo->bulletin);
        jfieldID jbulletinField = (*env)->GetFieldID(env, gangInfoClass, "bulletin", 
                                                     STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangInfo, jbulletinField, jbulletin);
    }

    jfieldID jportraitCrcField = (*env)->GetFieldID(env, gangInfoClass, 
                                                    "portraitCrc", "I");
    (*env)->SetIntField(env, jgangInfo, jportraitCrcField, gangInfo->portrait_crc);

    jfieldID jsearchableField = (*env)->GetFieldID(env, gangInfoClass, 
                                                    "searchable", "I");
    (*env)->SetIntField(env, jgangInfo, jsearchableField, gangInfo->searchable);

    jfieldID jcurrentMemberCountField = (*env)->GetFieldID(env, gangInfoClass, 
                                                           "currentMemberCount", "I");
    (*env)->SetIntField(env, jgangInfo, jcurrentMemberCountField, 
                        gangInfo->current_member_count);

    jfieldID jlimitMemberCountField = (*env)->GetFieldID(env, gangInfoClass, 
                                                         "limitMemberCount", "I");
    (*env)->SetIntField(env, jgangInfo, jlimitMemberCountField, 
                        gangInfo->limit_member_count);

    if (gangInfo->group_activity != NULL)
    {
        jstring jgroupActivity = (*env)->NewStringUTF(env, gangInfo->group_activity);
        jfieldID jgroupActivityField = (*env)->GetFieldID(env, gangInfoClass, "groupActivity", 
                                                          STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangInfo, jgroupActivityField, jgroupActivity);
    }

    if (gangInfo->QunMember != NULL)
    {
        jobject jarrayList = buildArrayList(env);
        DList* gangMemberList = gangInfo->QunMember;

        while (gangMemberList)
        {
            Fetion_QunMember* gangMember = (Fetion_QunMember*) gangMemberList->data;

            if (gangMember)
            {
                jobject jgangMember = buildFetionGangMember(env, gangMember);

                insertToArrayList(env, jarrayList, jgangMember);
            }

            gangMemberList = d_list_next(gangMemberList);
        }

        jfieldID jgangMemberListField = (*env)->GetFieldID(env, gangInfoClass,
                                                           "gangMemberList",
                                                           ARRAY_LIST_CLASS_SIG);
        (*env)->SetObjectField(env, jgangInfo, jgangMemberListField,
            jarrayList);
    }

    return jgangInfo;
}

jobject buildFetionGangMember(JNIEnv* env, Fetion_QunMember* gangMember)
{
    jclass gangMemberClass = NULL;
    jobject jgangMember = buildObject(env, &gangMemberClass,
                                      FETION_GANG_MEMBER_CLASS,
                                      FETION_GANG_MEMBER_CLASS_NOT_FOUND);

    jfieldID jidField = (*env)->GetFieldID(env, gangMemberClass, "id", "J");
    (*env)->SetLongField(env, jgangMember, jidField, gangMember->id);

    if (gangMember->uri != NULL)
    {
        jstring juri = (*env)->NewStringUTF(env, gangMember->uri);
        jfieldID juriField = (*env)->GetFieldID(env, gangMemberClass, "uri", 
                                                STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangMember, juriField, juri);
    }

    if (gangMember->nickname != NULL)
    {
        jstring jnickname = (*env)->NewStringUTF(env, gangMember->nickname);
        jfieldID jnicknameField = (*env)->GetFieldID(env, gangMemberClass, "nickname", 
                                                STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangMember, jnicknameField, jnickname);
    }

    if (gangMember->iicnickname != NULL)
    {
        jstring jiicNickname = (*env)->NewStringUTF(env, gangMember->iicnickname);
        jfieldID jiicNicknameField = (*env)->GetFieldID(env, gangMemberClass, "iicNickname", 
                                                STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangMember, jiicNicknameField, jiicNickname);
    }

    jfieldID jidentityField = (*env)->GetFieldID(env, gangMemberClass, "identity", "I");
    (*env)->SetIntField(env, jgangMember, jidentityField, gangMember->identity);

    jfieldID jstateField = (*env)->GetFieldID(env, gangMemberClass, "state", "I");
    (*env)->SetIntField(env, jgangMember, jstateField, gangMember->state);

    if (gangMember->client_type != NULL)
    {
        jstring jclientType = (*env)->NewStringUTF(env, gangMember->client_type);
        jfieldID jclientTypeField = (*env)->GetFieldID(env, gangMemberClass, "clientType", 
                                                STRING_CLASS_SIG);

        (*env)->SetObjectField(env, jgangMember, jclientTypeField, jclientType);
    }

    return jgangMember;
}

jobject buildArrayList(JNIEnv* env)
{
    jclass arrayListClass = (*env)->FindClass(env, ARRAY_LIST_CLASS);
    jmethodID constructor = (*env)->GetMethodID(env, arrayListClass,
                                                   "<init>", "()V");
    jobject jarrayList = (*env)->NewObject(env, arrayListClass, constructor);

    return jarrayList;
}

jboolean insertToArrayList(JNIEnv* env, jobject jarrayList, jobject jelement)
{
    jclass arrayListClass = (*env)->GetObjectClass(env, jarrayList);
    jmethodID addMethod = (*env)->GetMethodID(env, arrayListClass,
                                              "add", "(Ljava/lang/Object;)Z");

    return (*env)->CallBooleanMethod(env, jarrayList, addMethod, jelement);
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
    if (checkNullPointer(env, juserId))
    {
        return JNI_FALSE;
    }
    if (checkNullPointer(env, jpassword))
    {
        return JNI_FALSE;
    }

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
    if (checkNullPointer(env, juserId))
    {
        return 0;
    }
    if (checkNullPointer(env, jpassword))
    {
        return 0;
    }

    jboolean isCopy;
    const char* userId = (*env)->GetStringUTFChars(env, juserId, &isCopy);
    const char* password = (*env)->GetStringUTFChars(env, jpassword, &isCopy);

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jint result = fx_login(userId, password, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, juserId, userId);
    (*env)->ReleaseStringUTFChars(env, jpassword, password);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncReLogin
(JNIEnv* env, jobject jobj, jobject jeventListener, jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

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
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    fx_set_system_msg_cb(callback, callbackArgs);
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getMessage
(JNIEnv* env, jobject jobj, jlong jid)
{
    Fetion_MSG* message = fx_get_msg(jid);
    jobject jmessage = NULL;

    if (message != NULL)
    {
        jmessage = buildFetionMessage(env, message);
        fx_destroy_msg(message);
    }

    return jmessage;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSms
(JNIEnv* env, jobject jobj, jlong jwho, jstring jmessage)
{
    if (checkNullPointer(env, jmessage))
    {
        return JNI_FALSE;
    }

    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);

    jboolean result = fs_send_sms(jwho, message);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_sendSmsByMobileNumber
(JNIEnv* env, jobject job, jstring jmobileNumber, jstring jmessage)
{
    if (checkNullPointer(env, jmobileNumber))
    {
        return JNI_FALSE;
    }
    if (checkNullPointer(env, jmobileNumber))
    {
        return JNI_FALSE;
    }

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
    if (checkNullPointer(env, jmessage))
    {
        return JNI_FALSE;
    }

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
    if (checkNullPointer(env, jmessage))
    {
        return 0;
    }

    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);
    
    jint result = fx_send_sms(jwho, message, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSendSmsToSelf
(JNIEnv* env, jobject jobj, jstring jmessage, 
 jobject jeventListener, jobjectArray jargs)
{
    if (checkNullPointer(env, jmessage))
    {
        return 0;
    }

    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jint result = fx_send_sms_to_self(message, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSendSmsByMobileNumber
(JNIEnv* env, jobject jobj, jstring jmobileNumber, jstring jmessage, 
 jobject jeventListener, jobjectArray jargs)
{
    if (checkNullPointer(env, jmessage))
    {
        return 0;
    }

    jboolean isCopy;
    const char* mobileNumber = (*env)->GetStringUTFChars(env, jmobileNumber, &isCopy);
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

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
    if (checkNullPointer(env, jmessage))
    {
        return JNI_FALSE;
    }

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
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    return fx_begin_dialog(jwho, callback, callbackArgs);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDialogSend
(JNIEnv* env, jobject jobj, jlong jwho, jstring jmessage, 
 jobject jeventListener, jobjectArray jargs)
{
    if (checkNullPointer(env, jmessage))
    {
        return 0;
    }

    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

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
    jstring jusrId = NULL;
    const char* userId = fx_get_usr_uid();

    if (userId != NULL)
    {
        jusrId = (*env)->NewStringUTF(env, userId);
    }

    return jusrId;
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserPassword
(JNIEnv* env, jobject jobj)
{
    jstring jpassword = NULL;
    const char* password = fx_get_usr_passwd();

    if (password != NULL)
    {
        jpassword = (*env)->NewStringUTF(env, password);
    }

    return jpassword;
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserShowName
(JNIEnv* env, jobject jobj)
{
    jstring jshowName = NULL;
    const char* showName = fx_get_usr_show_name();

    if (showName != NULL)
    {
        jshowName = (*env)->NewStringUTF(env, showName);
    }

    return jshowName;
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserUri
(JNIEnv* env, jobject jobj)
{
    jstring juri = NULL;
    const char* uri = fx_get_usr_uri();

    if (uri != NULL)
    {
        juri = (*env)->NewStringUTF(env, uri);
    }

    return juri;
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getUserMobileNumber
(JNIEnv* env, jobject jobj)
{
    jstring jmobileNumber = NULL;
    const char* mobileNumber = fx_get_usr_mobilenum();

    if (mobileNumber != NULL)
    {
        jmobileNumber = (*env)->NewStringUTF(env, mobileNumber);
    }

    return jmobileNumber;
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
    const char* description = NULL;
    if (jdescription != NULL)
    {
        description = (*env)->GetStringUTFChars(env, jdescription, &isCopy);        
    }

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);    

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
    if (checkNullPointer(env, jimpresa))
    {
        return 0;
    }

    jboolean isCopy;
    const char* impresa = (*env)->GetStringUTFChars(env, jimpresa, &isCopy);
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);    

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
    jobject jpersonalInfo = NULL;

    if (personalInfo != NULL)
    {
        jpersonalInfo = buildFetionPersonalInfo(env, personalInfo);
    }

    return jpersonalInfo;
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getGroupList
(JNIEnv* env, jobject jobj)
{
    jobject jarrayList = buildArrayList(env);
    DList* groupList = fx_get_group();

    while (groupList)
    {
        Fetion_Group* group = (Fetion_Group*) groupList->data;

        if (group != NULL)
        {
            jobject jgroup = buildFetionGroup(env, group);

            insertToArrayList(env, jarrayList, jgroup);
        }

        groupList = d_list_next(groupList);
    }

    return jarrayList;
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getAccountList
(JNIEnv* env, jobject jobj)
{
    jobject jarrayList = buildArrayList(env);
    DList* accountList = fx_get_account();

    while (accountList)
    {
        Fetion_Account* account = (Fetion_Account*) accountList->data;

        if (account != NULL)
        {
            jobject jaccount = buildFetionAccount(env, account);

            insertToArrayList(env, jarrayList, jaccount);
        }

        accountList = d_list_next(accountList);
    }

    return jarrayList;
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getBlacklist
(JNIEnv* env, jobject jobj)
{
    jobject jarrayList = buildArrayList(env);
    DList* blacklist = fx_get_blacklist();

    while (blacklist)
    {
        Fetion_Black* blacklistItem = (Fetion_Black*) blacklist->data;

        if (blacklistItem != NULL)
        {
            jobject jblacklistItem = buildFetionBlacklistItem(env, blacklistItem);

            insertToArrayList(env, jarrayList, jblacklistItem);
        }

        blacklist = d_list_next(blacklist);
    }

    return jarrayList;
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getGangList
(JNIEnv* env, jobject jobj)
{
    jobject jarrayList = buildArrayList(env);
    DList* gangList = fx_get_qun();

    while (gangList)
    {
        Fetion_Qun* gang  = (Fetion_Qun*) gangList->data;

        if (gang != NULL)
        {
            jobject jgang = buildFetionGang(env, gang);

            insertToArrayList(env, jarrayList, jgang);
        }

        gangList = d_list_next(gangList);
    }

    return jarrayList;
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getAccountById
(JNIEnv* env, jobject jobj, jlong jid)
{
    Fetion_Account* account = fx_get_account_by_id(jid);
    jobject jaccount = NULL;

    if (account != NULL)
    {
        jaccount = buildFetionAccount(env, account);
    }

    return jaccount;
}

jobject JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getGangById
(JNIEnv* env, jobject jobj, jlong jid)
{
    Fetion_Qun* gang = fx_get_qun_by_id(jid);
    jobject jgang = NULL;

    if (gang != NULL)
    {
        jgang = buildFetionGang(env, gang);
    }

    return jgang;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isPCUserById
(JNIEnv* env, jobject jobj, jlong jid)
{
    return fx_is_pc_user_by_id(jid);
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isPCUserByAccount
(JNIEnv* env, jobject jobj, jobject jaccount)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jboolean result = fx_is_pc_user_by_account(&account);

    destroyFetionAccountStruct(&account);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isInBlacklistById
(JNIEnv* env, jobject jobj, jlong jid)
{
    return fx_is_InBlacklist_by_id(jid);
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isInBlacklistByAccount
(JNIEnv* env, jobject jobj, jobject jaccount)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jboolean result = fx_is_InBlacklist_by_account(&account);

    destroyFetionAccountStruct(&account);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncMoveGroupBuddyById
(JNIEnv* env, jobject jobj, jlong jid, jint jgroupId, jobject jeventListener,
 jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);
    
    return fx_move_group_buddy_by_id(jid, jgroupId, callback, callbackArgs);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncMoveGroupBuddyByAccount
(JNIEnv* env, jobject jobj, jobject jaccount, jint jgroupId, jobject jeventListener,
 jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jint result = fx_move_group_buddy(&account, jgroupId, callback, callbackArgs);

    destroyFetionAccountStruct(&account);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isOnlineById
(JNIEnv* env, jobject jobj, jlong jid)
{
    return fx_is_on_line_by_id(jid);
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_isOnlineByAccount
(JNIEnv* env, jobject jobj, jobject jaccount)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jboolean result = fx_is_on_line_by_account(&account);

    destroyFetionAccountStruct(&account);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getOnlineStatusById
(JNIEnv* env, jobject jobj, jlong jid)
{
    return fx_get_online_status_by_id(jid);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getOnlineStatusByAccount
(JNIEnv* env, jobject jobj, jobject jaccount)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jint result = fx_get_online_status_by_account(&account);

    destroyFetionAccountStruct(&account);

    return result;
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_updateAccountInfoById
(JNIEnv* env, jobject jobj, jlong jid)
{
    fx_updata_account_info_by_id(jid);
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_updateAccountInfoAll
(JNIEnv* env, jobject jobj)
{
    fx_updata_account_info_all();
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getAccountShowName
(JNIEnv* env, jobject jobj, jobject jaccount, jboolean jneedImpresa)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jstring jshowName = NULL;
    char* showName = fx_get_account_show_name(&account, jneedImpresa);

    if (showName != NULL)
    {
        jshowName = (*env)->NewStringUTF(env, showName);
    }

    return jshowName;
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getGangShowName
(JNIEnv* env, jobject jobj, jobject jgang)
{
    Fetion_Qun gang;
    buildFetionGangStruct(env, &gang, jgang);

    jstring jshowName = NULL;
    char* showName = fx_get_qun_show_name(&gang);

    if (showName != NULL)
    {
        jshowName = (*env)->NewStringUTF(env, showName);
    }

    destroyFetionGangStruct(&gang);

    return jshowName;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getAccountGroupId
(JNIEnv* env, jobject jobj, jobject jaccount)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jint result = fx_get_account_group_id(&account);

    destroyFetionAccountStruct(&account);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_renameBuddyList
(JNIEnv* env, jobject jobj, jint jid, jstring jname)
{
    jboolean isCopy;
    const char* name = (*env)->GetStringUTFChars(env, jname, &isCopy);

    jboolean result = fs_rename_buddylist(jid, name);

    (*env)->ReleaseStringUTFChars(env, jname, name);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_deleteBuddyList
(JNIEnv* env, jobject jobj, jint jid)
{
    return fs_delete_buddylist(jid);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncRenameBuddyList
(JNIEnv* env, jobject jobj, jint jid, jstring jname, jobject jeventListener,
 jobjectArray jargs)
{
    if (checkNullPointer(env, jname))
    {
        return 0;
    }

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jboolean isCopy;
    const char* name = (*env)->GetStringUTFChars(env, jname, &isCopy);

    jint result = fx_rename_buddylist(jid, name, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jname, name);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddBuddyList
(JNIEnv* env, jobject jobj, jstring jname, jobject jeventListener,
 jobjectArray jargs)
{
    if (checkNullPointer(env, jname))
    {
        return 0;
    }

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jboolean isCopy;
    const char* name = (*env)->GetStringUTFChars(env, jname, &isCopy);

    jint result = fx_add_buddylist(name, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jname, name);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddBuddyByUserId
(JNIEnv* env, jobject jobj, jstring juserId, jstring jlocalName,
 jint jgroupId, jstring jdescription, jobject jeventListener, jobjectArray jargs)
{
    if (checkNullPointer(env, juserId))
    {
        return 0;
    }

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jboolean isCopy;
    const char* userId = (*env)->GetStringUTFChars(env, juserId, &isCopy);
    const char* localName = NULL;
    if (jlocalName != NULL)
    {
        localName = (*env)->GetStringUTFChars(env, jlocalName, &isCopy);
    }
    const char* description = NULL;
    if (jdescription != NULL)
    {
        description = (*env)->GetStringUTFChars(env, jdescription, &isCopy);
    }

    jint result = fx_add_buddy_by_uid(userId, localName, jgroupId, description,
                                      callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, juserId, userId);
    if (jlocalName != NULL)
    {
        (*env)->ReleaseStringUTFChars(env, jlocalName, localName);
    }
    if (jdescription != NULL)
    {
        (*env)->ReleaseStringUTFChars(env, jdescription, description);
    }

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddBuddyByMobileNumber
(JNIEnv* env, jobject jobj, jstring jmobileNumber, 
 jstring jlocalName, jint jgroupId, jstring jdescription, jobject jeventListener,
 jobjectArray jargs)
{
    if (checkNullPointer(env, jmobileNumber))
    {
        return 0;
    }

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jboolean isCopy;
    const char* mobileNumber = (*env)->GetStringUTFChars(env, jmobileNumber, &isCopy);
    const char* localName = NULL;
    if (jlocalName != NULL)
    {
        localName = (*env)->GetStringUTFChars(env, jlocalName, &isCopy);
    }
    const char* description = NULL;
    if (jdescription != NULL)
    {
        description = (*env)->GetStringUTFChars(env, jdescription, &isCopy);
    }

    jint result = fx_add_buddy_by_uid(mobileNumber, localName, jgroupId, description,
                                      callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jmobileNumber, mobileNumber);
    if (jlocalName != NULL)
    {
        (*env)->ReleaseStringUTFChars(env, jlocalName, localName);
    }
    if (jdescription != NULL)
    {
        (*env)->ReleaseStringUTFChars(env, jdescription, description);
    }

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_handleContactRequest
(JNIEnv* env, jobject jobj, jstring juri, jint jisPassed, jint jgroupId, 
 jstring jlocalName)
{
    if (checkNullPointer(env, juri))
    {
        return 0;
    }

    jboolean isCopy;
    const char* uri = (*env)->GetStringUTFChars(env, juri, &isCopy);
    const char* localName = NULL;
    if (jlocalName != NULL)
    {
        localName = (*env)->GetStringUTFChars(env, jlocalName, &isCopy);
    }

    jint result = fx_handleContactRequest(uri, jisPassed, jgroupId, localName);

    (*env)->ReleaseStringUTFChars(env, juri, uri);
    if (jlocalName)
    {
        (*env)->ReleaseStringUTFChars(env, jlocalName, localName);
    }

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDeleteBuddyList
(JNIEnv* env, jobject jobj, jint jid, jobject jeventListener,
 jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    return fx_delete_buddylist(jid, callback, callbackArgs);
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setBuddyInfo
(JNIEnv* env, jobject jobj, jlong jid, jstring jlocalName)
{
    if (checkNullPointer(env, jlocalName))
    {
        return JNI_FALSE;
    }

    jboolean isCopy;
    const char* localName = (*env)->GetStringUTFChars(env, jlocalName, &isCopy);

    jboolean result = fs_set_buddyinfo(jid, localName);

    (*env)->ReleaseStringUTFChars(env, jlocalName, localName);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncSetBuddyInfo
(JNIEnv* env, jobject jobj, jlong jid, jstring jlocalName,
 jobject jeventListener, jobjectArray jargs)
{
    if (checkNullPointer(env, jlocalName))
    {
        return 0;
    }

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jboolean isCopy;
    const char* localName = (*env)->GetStringUTFChars(env, jlocalName, &isCopy);

    jint result = fx_set_buddyinfo(jid, localName, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, jlocalName, localName);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDeleteBuddyById
(JNIEnv* env, jobject jobj, jlong jid, jobject jeventListener, 
 jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    return fx_delete_buddy_by_id(jid, callback, callbackArgs);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncDeleteBuddyByAccount
(JNIEnv* env, jobject jobj, jobject jaccount, jobject jeventListener,
 jobjectArray jargs)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    int result = fx_delete_buddy_by_account(&account, callback, callbackArgs);

    destroyFetionAccountStruct(&account);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddToBlacklistById
(JNIEnv* env, jobject jobj, jlong jid, jobject jeventListener,
 jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    return fx_addto_blacklist_by_id(jid, callback, callbackArgs);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddToBlacklistByAccount
(JNIEnv* env, jobject jobj, jobject jaccount, jobject jeventListener,
 jobjectArray jargs)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    int result = fx_addto_blacklist_by_account(&account, callback, callbackArgs);

    destroyFetionAccountStruct(&account);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncAddToBlacklistByUri
(JNIEnv* env, jobject jobj, jstring juri, jobject jeventListener,
 jobjectArray jargs)
{
    if (checkNullPointer(env, juri))
    {
        return 0;
    }

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jboolean isCopy;
    const char* uri = (*env)->GetStringUTFChars(env, juri, &isCopy);

    jint result = fx_addto_blacklist_by_uri(uri, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, juri, uri);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncRemoveFromBlacklistById
(JNIEnv* env, jobject jobj, jlong jid, jobject jeventListener,
 jobjectArray jargs)
{
    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    return fx_removefrom_blacklist_by_id(jid, callback, callbackArgs);
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncRemoveFromBlacklistByAccount
(JNIEnv* env, jobject jobj, jobject jaccount, jobject jeventListener, 
 jobjectArray jargs)
{
    Fetion_Account account;
    buildFetionAccountStruct(env, &account, jaccount);

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    int result = fx_removefrom_blacklist_by_account(&account, callback, callbackArgs);

    destroyFetionAccountStruct(&account);

    return result;
}

jint JNICALL Java_com_honnix_jfetion_impl_FetionImpl_asyncRemoveFromBlacklistByUri
(JNIEnv* env, jobject jobj, jstring juri, jobject jeventListener,
 jobjectArray jargs)
{
    if (checkNullPointer(env, juri))
    {
        return 0;
    }

    jobjectArray callbackArgs = buildCallBackArgs(env, jeventListener, jargs);

    jboolean isCopy;
    const char* uri = (*env)->GetStringUTFChars(env, juri, &isCopy);

    jint result = fx_removefrom_blacklist_by_uri(uri, callback, callbackArgs);

    (*env)->ReleaseStringUTFChars(env, juri, uri);

    return result;
}

jboolean JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setProxy
(JNIEnv* env, jobject jobj, jstring jproxy)
{
    if (checkNullPointer(env, jproxy))
    {
        return JNI_FALSE;
    }

    jboolean isCopy;
    const char* proxy = (*env)->GetStringUTFChars(env, jproxy, &isCopy);

    jboolean result = fx_set_proxy(proxy);
    
    (*env)->ReleaseStringUTFChars(env, jproxy, proxy);

    return result;
}

void JNICALL Java_com_honnix_jfetion_impl_FetionImpl_setUnknownProxy
(JNIEnv* env, jobject jobj)
{
    fx_set_unknow_proxy();
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_getProxy
(JNIEnv* env, jobject jobj)
{
    jstring jproxy = NULL;
    char* proxy = fx_get_proxy();

    if (proxy != NULL)
    {
        jproxy = (*env)->NewStringUTF(env, proxy);
    }

    return jproxy;
}

jstring JNICALL Java_com_honnix_jfetion_impl_FetionImpl_removeFontTag
(JNIEnv* env, jobject jobj, jstring jmessage)
{
    if (checkNullPointer(env, jmessage))
    {
        return NULL;
    }

    jboolean isCopy;
    const char* message = (*env)->GetStringUTFChars(env, jmessage, &isCopy);

    jstring jnewMessage = NULL;
    char* newMessage = fx_simple_paser_msg(message);

    if (newMessage != NULL)
    {
        jnewMessage = (*env)->NewStringUTF(env, newMessage);
    }
    
    (*env)->ReleaseStringUTFChars(env, jmessage, message);

    return jnewMessage;
}
