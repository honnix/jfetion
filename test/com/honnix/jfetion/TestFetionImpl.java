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

    // public void testAsyncDialog()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // String id = fetionAccount.getUserId();
    // assertNotNull("User ID is null?", id);
    //
    // checker.setCalled(false);
    // assertEquals("begin dialog error?", 1, fetionMessage.asyncBeginDialog(
    // Long.parseLong(id), beginDialogEventListener, checker));
    //
    // waitUntilCalledBack();
    //
    // checker.setCalled(false);
    // assertEquals("dialog send error?", 1, fetionMessage.asyncDialogSend(
    // Long.parseLong(id), MESSAGE, dialogSendEventListener, checker));
    //
    // waitUntilCalledBack();
    //
    // fetionMessage.asyncEndDialog(Long.parseLong(id));
    // }

    // public void testAsyncLogin()
    // {
    // checker.setCalled(false);
    // assertTrue("init failed??", fetionSession.init());
    // assertEquals("wrong login status?", 1, fetionSession.asyncLogin(
    // MOBILE_NUMBER, PASSWORD, loginEventListener, checker));
    //
    // waitUntilCalledBack();
    // }
    //
    // public void testAsyncRelogin()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    // fetionSession.logout();
    //
    // checker.setCalled(false);
    // assertEquals("wrong relogin status?", 1, fetionSession.asyncReLogin(
    // loginEventListener, checker));
    //
    // waitUntilCalledBack();
    // }

    // public void testAsyncSendSms()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // String id = fetionAccount.getUserId();
    // assertNotNull("User ID is null?", id);
    //
    // checker.setCalled(false);
    // assertEquals("send sms failed?", 1, fetionMessage.asyncSendSms(Long
    // .parseLong(id), MESSAGE, smsEventListener, checker));
    //
    // waitUntilCalledBack();
    // }

    // public void testAsyncSendSmsByMobileNumber()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // checker.setCalled(false);
    // assertEquals("send sms failed?", 1, fetionMessage
    // .asyncSendSmsByMobileNumber("13816082319", MESSAGE,
    // smsEventListener, checker));
    //
    // waitUntilCalledBack();
    // }

    // public void testAsyncSendSmsToSelf()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // checker.setCalled(false);
    // assertEquals("send sms failed?", 1, fetionMessage.asyncSendSmsToSelf(
    // MESSAGE, smsEventListener, checker));
    //
    // waitUntilCalledBack();
    // }
    //
    // public void testAsyncSetUserState()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // checker.setCalled(false);
    // fetionAccount.asyncSetUserStatus(EventConstant.STATUS_AWAY, null,
    // setStatusEventListener, checker);
    //
    // waitUntilCalledBack();
    //
    // assertEquals("wrong status?", EventConstant.STATUS_AWAY, fetionAccount
    // .getUserStatus());
    // }
    //
    public void testDialog()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String id = fetionAccount.getUserId();
        assertNotNull("User ID is null?", id);

        assertTrue("begin dialog error?", fetionMessage.beginDialog(Long
                .parseLong(id)));

        checker.setCalled(false);
        assertTrue("dialog send error?", fetionMessage.dialogSend(Long
                .parseLong(id), MESSAGE));

        fetionMessage.endDialog(Long.parseLong(id));
    }

    // public void testGangShowName()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // FetionGang gang = new FetionGang();
    // gang.setId(1);
    // assertEquals("should have no gang showName", "1", fetionAccount
    // .getGangShowName(gang));
    // }

    //
    // public void testGetInfo()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // assertEquals("wrong User Id?", "1234", fetionAccount.getUserId());
    // assertEquals("wrong password?", PASSWORD, fetionAccount
    // .getUserPassword());
    // assertEquals("wrong show name?", "honnix", fetionAccount
    // .getUserShowName());
    // assertEquals("wrong uri?", URI, fetionAccount.getUserUri());
    // assertEquals("wrong mobile number?", MOBILE_NUMBER, fetionAccount
    // .getUserMobileNumber());
    // assertEquals("wrong score?", 0, fetionAccount.getUserScore());
    // assertEquals("wrong expire time?", 100, fetionSession.getExpireTime());
    // }
    //
    // public void testGetInfoByAccount()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // String id = fetionAccount.getUserId();
    // assertNotNull("User ID is null?", id);
    // FetionAccount account =
    // fetionAccount.getAccountById(Long.parseLong(id));
    //
    // assertTrue("should be PC user", fetionAccount
    // .isPCUserByAccount(account));
    // assertEquals("should have been authorized",
    // EventConstant.LOGIN_AUTH_OK, fetionAccount
    // .isAuthorizedByAccount(account));
    // assertFalse("should no in blacklist", fetionAccount
    // .isInBlacklistByAccount(account));
    // assertTrue("should be online", fetionAccount.isOnlineByAccount(account));
    // assertEquals("should be online", EventConstant.STATUS_ONLINE,
    // fetionAccount.getOnlineStatusByAccount(account));
    // assertEquals("wrong showName without impresa?", "honnix", fetionAccount
    // .getAccountShowName(account, false));
    // assertEquals("wrong showName with impresa?", "honnix", fetionAccount
    // .getAccountShowName(account, true));
    // assertEquals("wrong groupId?", 1, fetionAccount
    // .getAccountGroupId(account));
    // }
    //
    // public void testGetInfoById()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // String id = fetionAccount.getUserId();
    // assertNotNull("User ID is null?", id);
    //
    // FetionAccount account =
    // fetionAccount.getAccountById(Long.parseLong(id));
    //
    // assertEquals("wrong id?", Long.parseLong(id), account.getId());
    // assertEquals("wrong uri?", URI, account.getUri());
    // assertEquals("wrong localName?", "honnix", account.getLocalName());
    // assertEquals("wrong buddyList?", "shadow", account.getBuddyList());
    // assertEquals("wrong groupId?", 1, account.getGroupId());
    // assertEquals("wrong relationStatus?", 1, account.getRelationStatus());
    // assertEquals("wrong onlineNotify?", 1, account.getOnlineNotify());
    // assertEquals("wrong statusCode?", 200, account.getStatusCode());
    // assertEquals("wrong onlineStatus?", 1, account.getOnlineStatus());
    // assertEquals("wrong portraitCrc?", 1, account.getPortraitCrc());
    // assertNotNull("wrong personalInfo", account.getPersonalInfo());
    // assertEquals("wrong userType?", FetionUserType.FETION_UTYPE_PC, account
    // .getUserType());
    //
    // FetionGang gang = fetionAccount.getGangById(Long.parseLong(id));
    // assertNull("should have no gang", gang);
    //
    // assertTrue("should be PC user", fetionAccount.isPCUserById(Long
    // .parseLong(id)));
    // assertFalse("should not be gang", fetionAccount.isGangById(Long
    // .parseLong(id)));
    // assertEquals("should have been authorized",
    // EventConstant.LOGIN_AUTH_OK, fetionAccount
    // .isAuthorizedById(Long.parseLong(id)));
    // assertFalse("should no in blacklist", fetionAccount
    // .isInBlacklistById(Long.parseLong(id)));
    // assertTrue("should be online", fetionAccount.isOnlineById(Long
    // .parseLong(id)));
    // assertEquals("should be online", EventConstant.STATUS_ONLINE,
    // fetionAccount.getOnlineStatusById(Long.parseLong(id)));
    //
    // fetionAccount.updateAccountInfoById(Long.parseLong(id));
    // fetionAccount.updateAccountInfoAll();
    // }
    //
    // public void testGetList()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // List<FetionGroup> groupList = fetionAccount.getGroupList();
    // assertEquals("should have no group", 2, groupList.size());
    //
    // List<FetionAccount> accountList = fetionAccount.getAccountList();
    // assertEquals("should have only one account", 1, accountList.size());
    //
    // List<FetionBlacklistItem> blacklist = fetionAccount.getBlacklist();
    // assertEquals("should have no blacklist", 0, blacklist.size());
    //
    // List<FetionGang> gangList = fetionAccount.getGangList();
    // assertEquals("should have no gang", 0, gangList.size());
    // }

    // public void testGetMessage()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // String id = fetionAccount.getUserId();
    // assertNotNull("User ID is null?", id);
    //
    // assertNull("should be no message", fetionMessage.getMessage(Long
    // .parseLong(id)));
    // }

    // public void testGetPersonalInfo()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // FetionPersonalInfo personalInfo = fetionAccount.getPersonalInfo();
    //
    // assertEquals("wrong nickname?", "honnix", personalInfo.getNickname());
    // assertEquals("wrong impresa?", "", personalInfo.getImpresa());
    // assertEquals("wrong gender", 1, personalInfo.getGender());
    // assertEquals("wrong nation?", "CN", personalInfo.getNation());
    // assertEquals("wrong province?", "sh", personalInfo.getProvince());
    // assertEquals("wrong city?", 21, personalInfo.getCity());
    // assertEquals("wrong ivrEnabled?", 1, personalInfo.getIvrEnabled());
    // assertEquals("wrong portraitCrc?", -709378836, personalInfo
    // .getPortraitCrc());
    // assertEquals("wrong provisioning?", 0, personalInfo.getProvisioning());
    // assertEquals("wrong mobileNumber?", MOBILE_NUMBER, personalInfo
    // .getMobileNumber());
    // assertEquals("wrong name?", "", personalInfo.getName());
    // assertEquals("wrong birthday?", "1900-01-01", personalInfo
    // .getBirthday());
    // assertEquals("wrong birthdayValid?", 0, personalInfo.getBirthdayValid());
    // assertEquals("wrong lunarAnimal?", 0, personalInfo.getLunarAnimal());
    // assertEquals("wrong horoscope?", 0, personalInfo.getHoroscope());
    // assertEquals("wrong profile?", "", personalInfo.getProfile());
    // assertEquals("wrong bloodType?", 0, personalInfo.getBloodType());
    // assertEquals("wrong occupation?", "", personalInfo.getOccupation());
    // assertEquals("wrong hobby?", "", personalInfo.getHobby());
    // assertEquals("wrong personalEmail?", "", personalInfo
    // .getPersonalEmail());
    // assertEquals("wrong workEmail?", "", personalInfo.getWorkEmail());
    // assertEquals("wrong otherEmail?", "", personalInfo.getOtherEmail());
    // assertEquals("wrong primaryEmail?", 0, personalInfo.getPrimaryEmail());
    // assertEquals("wrong jobTitle?", "", personalInfo.getJobTitle());
    // assertEquals("wrong homePhone?", "", personalInfo.getHomePhone());
    // assertEquals("wrong workPhone?", "", personalInfo.getWorkPhone());
    // assertEquals("wrong otherPhone?", "", personalInfo.getOtherPhone());
    // assertEquals("wrong company?", "", personalInfo.getCompany());
    // assertNull("wrong companyWebsite?", personalInfo.getCompanyWebsite());
    // assertEquals("wrong matchEnabled?", 0, personalInfo.getMatchEnabled());
    // }
    //    
    // public void testLogin()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    // }
    //
    // public void testSendSms()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    //
    // String id = fetionAccount.getUserId();
    // assertNotNull("User ID is null?", id);
    //
    // assertTrue("send sms failed?", fetionMessage.sendSms(
    // Long.parseLong(id), MESSAGE));
    // }
    //
    // public void testSendSmsByMobileNumber()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    // assertTrue("send sms failed?", fetionMessage.sendSmsByMobileNumber(
    // "13816082319", MESSAGE));
    // }

    // public void testSendSmsToSelf()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    // assertTrue("send sms failed??", fetionMessage.sendSmsToSelf("自动安装盘"));
    // }

    // public void testSetSystemMessageEventListener()
    // {
    // assertTrue("init failed??", fetionSession.init());
    // fetionSession.setSystemMessageEventListener(systemMessageEventListener,
    // checker);
    // assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    // PASSWORD));
    // }

}
