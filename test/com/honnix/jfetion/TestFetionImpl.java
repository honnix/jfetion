package com.honnix.jfetion;

import java.util.List;

import junit.framework.TestCase;

import com.honnix.jfetion.impl.FetionFactory;
import com.honnix.jfetion.impl.data.FetionAccount;
import com.honnix.jfetion.impl.data.FetionBlacklistItem;
import com.honnix.jfetion.impl.data.FetionGang;
import com.honnix.jfetion.impl.data.FetionGroup;
import com.honnix.jfetion.impl.data.FetionPersonalInfo;
import com.honnix.jfetion.impl.data.FetionUserType;
import com.honnix.jfetion.impl.event.BeginDialogEventListener;
import com.honnix.jfetion.impl.event.DialogSendEventListener;
import com.honnix.jfetion.impl.event.EventConstant;
import com.honnix.jfetion.impl.event.LoginEventListener;
import com.honnix.jfetion.impl.event.SetStatusEventListener;
import com.honnix.jfetion.impl.event.SmsEventListener;
import com.honnix.jfetion.impl.event.SystemMessageEventListener;

public class TestFetionImpl
    extends TestCase
{

    private static final String MOBILE_NUMBER = "13761089478";

    private static final String PASSWORD = "honnix548";

    private static final String MESSAGE = "sent using JNI";

    private static final String URI = "honnix@honnix.com";

    private Checker checker;

    private FetionSessionControl fetionSession;

    private FetionAccountControl fetionAccount;

    private FetionMessageControl fetionMessage;

    private LoginEventListener loginEventListener;

    private SystemMessageEventListener systemMessageEventListener;

    private SetStatusEventListener setStatusEventListener;

    private SmsEventListener smsEventListener;

    private BeginDialogEventListener beginDialogEventListener;

    private DialogSendEventListener dialogSendEventListener;

    private void waitUntilCalledBack()
    {
        while (true)
        {
            if (checker.isCalled())
            {
                break;
            }

            try
            {
                Thread.sleep(100);
            }
            catch (InterruptedException e)
            {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    @Override
    protected void setUp()
        throws Exception
    {
        checker = new Checker();

        fetionSession = FetionFactory.getFetionSessionControl();
        fetionAccount = FetionFactory.getFetionAccountControl();
        fetionMessage = FetionFactory.getFetionMessageControl();

        loginEventListener = new LoginEventListener();
        systemMessageEventListener = new SystemMessageEventListener();
        setStatusEventListener = new SetStatusEventListener();
        smsEventListener = new SmsEventListener();
        beginDialogEventListener = new BeginDialogEventListener();
        dialogSendEventListener = new DialogSendEventListener();
    }

    @Override
    protected void tearDown()
        throws Exception
    {
        fetionSession.logout();
        fetionSession.closeNetwork();
        fetionSession.terminate();
    }

//    public void testAsyncDialog()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        String id = fetionAccount.getUserId();
//        assertNotNull("User ID is null?", id);
//
//        checker.setCalled(false);
//        assertEquals("begin dialog error?", 1, fetionMessage.asyncBeginDialog(
//                Long.parseLong(id), beginDialogEventListener, checker));
//
//        waitUntilCalledBack();
//
//        checker.setCalled(false);
//        assertEquals("dialog send error?", 1, fetionMessage.asyncDialogSend(
//                Long.parseLong(id), MESSAGE, dialogSendEventListener, checker));
//
//        waitUntilCalledBack();
//
//        fetionMessage.asyncEndDialog(Long.parseLong(id));
//    }

//    public void testAsyncLogin()
//    {
//        checker.setCalled(false);
//        assertTrue("init failed??", fetionSession.init());
//        assertEquals("wrong login status?", 1, fetionSession.asyncLogin(
//                MOBILE_NUMBER, PASSWORD, loginEventListener, checker));
//
//        waitUntilCalledBack();
//    }
//
//    public void testAsyncRelogin()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//        fetionSession.logout();
//
//        checker.setCalled(false);
//        assertEquals("wrong relogin status?", 1, fetionSession.asyncReLogin(
//                loginEventListener, checker));
//
//        waitUntilCalledBack();
//    }

//    public void testAsyncSendSms()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        String id = fetionAccount.getUserId();
//        assertNotNull("User ID is null?", id);
//
//        checker.setCalled(false);
//        assertEquals("send sms failed?", 1, fetionMessage.asyncSendSms(Long
//                .parseLong(id), MESSAGE, smsEventListener, checker));
//
//        waitUntilCalledBack();
//    }

//    public void testAsyncSendSmsByMobileNumber()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        checker.setCalled(false);
//        assertEquals("send sms failed?", 1, fetionMessage
//                .asyncSendSmsByMobileNumber("13816082319", MESSAGE,
//                        smsEventListener, checker));
//
//        waitUntilCalledBack();
//    }

//    public void testAsyncSendSmsToSelf()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        checker.setCalled(false);
//        assertEquals("send sms failed?", 1, fetionMessage.asyncSendSmsToSelf(
//                MESSAGE, smsEventListener, checker));
//
//        waitUntilCalledBack();
//    }
//
//    public void testAsyncSetUserState()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        checker.setCalled(false);
//        fetionAccount.asyncSetUserStatus(EventConstant.STATUS_AWAY, null,
//                setStatusEventListener, checker);
//
//        waitUntilCalledBack();
//
//        assertEquals("wrong status?", EventConstant.STATUS_AWAY, fetionAccount
//                .getUserStatus());
//    }
//
//    public void testDialog()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        String id = fetionAccount.getUserId();
//        assertNotNull("User ID is null?", id);
//
//        assertEquals("begin dialog error?", 1, fetionMessage.beginDialog(Long
//                .parseLong(id)));
//
//        checker.setCalled(false);
//        assertEquals("dialog send error?", 1, fetionMessage.dialogSend(Long
//                .parseLong(id), MESSAGE));
//
//        fetionMessage.endDialog(Long.parseLong(id));
//    }
//
//    public void testGangShowName()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        FetionGang gang = new FetionGang();
//        gang.setId(1);
//        assertNull("should have no gang showName", fetionAccount
//                .getGangShowName(gang));
//    }
//
//    public void testGetInfo()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        assertEquals("wrong User Id?", "1234", fetionAccount.getUserId());
//        assertEquals("wrong password?", PASSWORD, fetionAccount
//                .getUserPassword());
//        assertEquals("wrong show name?", "honnix", fetionAccount
//                .getUserShowName());
//        assertEquals("wrong uri?", URI, fetionAccount.getUserUri());
//        assertEquals("wrong mobile number?", MOBILE_NUMBER, fetionAccount
//                .getUserMobileNumber());
//        assertEquals("wrong score?", 0, fetionAccount.getUserScore());
//        assertEquals("wrong expire time?", 100, fetionSession.getExpireTime());
//    }
//
//    public void testGetInfoByAccount()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        String id = fetionAccount.getUserId();
//        assertNotNull("User ID is null?", id);
//        FetionAccount account =
//                fetionAccount.getAccountById(Long.parseLong(id));
//
//        assertTrue("should be PC user", fetionAccount
//                .isPCUserByAccount(account));
//        assertEquals("should have been authorized",
//                EventConstant.LOGIN_AUTH_OK, fetionAccount
//                        .isAuthorizedByAccount(account));
//        assertFalse("should no in blacklist", fetionAccount
//                .isInBlacklistByAccount(account));
//        assertTrue("should be online", fetionAccount.isOnlineByAccount(account));
//        assertEquals("should be online", EventConstant.STATUS_ONLINE,
//                fetionAccount.getOnlineStatusByAccount(account));
//        assertEquals("wrong showName without impresa?", "honnix", fetionAccount
//                .getAccountShowName(account, false));
//        assertEquals("wrong showName with impresa?", "honnix", fetionAccount
//                .getAccountShowName(account, true));
//        assertEquals("wrong groupId?", 1, fetionAccount
//                .getAccountGroupId(account));
//    }
//
    public void testGetInfoById()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String id = fetionAccount.getUserId();
        assertNotNull("User ID is null?", id);

        FetionAccount account =
                fetionAccount.getAccountById(Long.parseLong(id));

        assertEquals("wrong id?", Long.parseLong(id), account.getId());
        assertEquals("wrong uri?", URI, account.getUri());
        assertEquals("wrong localName?", "honnix", account.getLocalName());
        assertEquals("wrong buddyList?", "shadow", account.getBuddyList());
        assertEquals("wrong groupId?", 1, account.getGroupId());
        assertEquals("wrong relationStatus?", 1, account.getRelationStatus());
        assertEquals("wrong onlineNotify?", 1, account.getOnlineNotify());
        assertEquals("wrong statusCode?", 200, account.getStatusCode());
        assertEquals("wrong onlineStatus?", 1, account.getOnlineStatus());
        assertEquals("wrong portraitCrc?", 1, account.getPortraitCrc());
        assertNotNull("wrong personalInfo", account.getPersonalInfo());
        assertEquals("wrong userType?", FetionUserType.FETION_UTYPE_PC, account
                .getUserType());

        FetionGang gang = fetionAccount.getGangById(Long.parseLong(id));
        assertNull("should have no gang", gang);

        assertTrue("should be PC user", fetionAccount.isPCUserById(Long
                .parseLong(id)));
        assertFalse("should not be gang", fetionAccount.isGangById(Long
                .parseLong(id)));
        assertEquals("should have been authorized",
                EventConstant.LOGIN_AUTH_OK, fetionAccount
                        .isAuthorizedById(Long.parseLong(id)));
        assertFalse("should no in blacklist", fetionAccount
                .isInBlacklistById(Long.parseLong(id)));
        assertTrue("should be online", fetionAccount.isOnlineById(Long
                .parseLong(id)));
        assertEquals("should be online", EventConstant.STATUS_ONLINE,
                fetionAccount.getOnlineStatusById(Long.parseLong(id)));

        fetionAccount.updateAccountInfoById(Long.parseLong(id));
        fetionAccount.updateAccountInfoAll();
    }
//
//    public void testGetList()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        List<FetionGroup> groupList = fetionAccount.getGroupList();
//        assertNull("should have no group", groupList);
//
//        List<FetionAccount> accountList = fetionAccount.getAccountList();
//        assertEquals("should have only one account", 1, accountList);
//
//        List<FetionBlacklistItem> blacklist = fetionAccount.getBlacklist();
//        assertNull("should have no blacklist", blacklist);
//
//        List<FetionGang> gangList = fetionAccount.getGangList();
//        assertNull("should have no gang", gangList);
//    }
//
//    public void testGetMessage()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        String id = fetionAccount.getUserId();
//        assertNotNull("User ID is null?", id);
//
//        assertNull("should be no message", fetionMessage.getMessage(Long
//                .parseLong(id)));
//    }
//
//    public void testGetPersonalInfo()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        FetionPersonalInfo personalInfo = fetionAccount.getPersonalInfo();
//
//        assertEquals("wrong nickname?", "honnix", personalInfo.getNickname());
//        assertEquals("wrong impresa?", "what is this", personalInfo
//                .getNickname());
//        assertEquals("wrong gender", 1, personalInfo.getGender());
//        assertEquals("wrong nation?", "China", personalInfo.getNation());
//        assertEquals("wrong province?", "Shanghai", personalInfo.getProvince());
//        assertEquals("wrong city?", 1, personalInfo.getCity());
//        assertEquals("wrong ivrEnabled?", 0, personalInfo.getIvrEnabled());
//        assertEquals("wrong portraitCrc?", 1, personalInfo.getPortraitCrc());
//        assertEquals("wrong provisioning?", 1, personalInfo.getProvisioning());
//        assertEquals("wrong mobileNumber?", MOBILE_NUMBER, personalInfo
//                .getMobileNumber());
//        assertEquals("wrong name?", "honnix", personalInfo.getName());
//        assertEquals("wrong birthday?", "1900-1-1", personalInfo.getBirthday());
//        assertEquals("wrong birthdayValid?", 1, personalInfo.getBirthdayValid());
//        assertEquals("wrong lunarAnimal?", 1, personalInfo.getLunarAnimal());
//        assertEquals("wrong horoscope?", 1, personalInfo.getHoroscope());
//        assertEquals("wrong profile?", "profile", personalInfo.getProfile());
//        assertEquals("wrong bloodType?", 1, personalInfo.getBloodType());
//        assertEquals("wrong occupation?", "occupation", personalInfo
//                .getOccupation());
//        assertEquals("wrong hobby?", "music", personalInfo.getHobby());
//        assertEquals("wrong personalEmail?", "hxliang1982@gmail.com",
//                personalInfo.getPersonalEmail());
//        assertEquals("wrong workEmail?", "hongxin.liang@ericsson.com",
//                personalInfo.getWorkEmail());
//        assertEquals("wrong otherEmail?", "hxliang1982@gmail.com", personalInfo
//                .getOtherEmail());
//        assertEquals("wrong primaryEmail?", 1, personalInfo.getPrimaryEmail());
//        assertEquals("wrong jobTitle?", "SE", personalInfo.getJobTitle());
//        assertEquals("wrong homePhone?", "11111111", personalInfo
//                .getHomePhone());
//        assertEquals("wrong workPhone?", "22222222", personalInfo
//                .getWorkPhone());
//        assertEquals("wrong otherPhone?", "33333333", personalInfo
//                .getOtherPhone());
//        assertEquals("wrong company?", "Ericsson", personalInfo.getCompany());
//        assertEquals("wrong companyWebsite?", "www.ericsson.com", personalInfo
//                .getCompanyWebsite());
//        assertEquals("wrong matchEnabled?", 1, personalInfo.getMatchEnabled());
//    }
//
//    public void testLogin()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//    }
//
//    public void testSendSms()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//
//        String id = fetionAccount.getUserId();
//        assertNotNull("User ID is null?", id);
//
//        assertTrue("send sms failed?", fetionMessage.sendSms(
//                Long.parseLong(id), MESSAGE));
//    }
//
//    public void testSendSmsByMobileNumber()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//        assertTrue("send sms failed?", fetionMessage.sendSmsByMobileNumber(
//                MOBILE_NUMBER, MESSAGE));
//    }
//
//    public void testSendSmsToSelf()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//        assertTrue("send sms failed??", fetionMessage.sendSmsToSelf(MESSAGE));
//    }
//
//    public void testSetSystemMessageEventListener()
//    {
//        assertTrue("init failed??", fetionSession.init());
//        fetionSession.setSystemMessageEventListener(systemMessageEventListener,
//                checker);
//        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
//                PASSWORD));
//    }

}
