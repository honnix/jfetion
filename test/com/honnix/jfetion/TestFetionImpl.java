/**
 * TestFetionImpl.java
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
package com.honnix.jfetion;

import java.util.List;

import junit.framework.TestCase;

import com.honnix.jfetion.impl.FetionFactory;
import com.honnix.jfetion.impl.data.FetionAccount;
import com.honnix.jfetion.impl.data.FetionBlacklistItem;
import com.honnix.jfetion.impl.data.FetionGang;
import com.honnix.jfetion.impl.data.FetionGroup;
import com.honnix.jfetion.impl.data.FetionPersonalInfo;
import com.honnix.jfetion.impl.data.FetionProxyInfo;
import com.honnix.jfetion.impl.data.FetionProxyType;
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

    private static final String URI = "sip:728801465@fetion.com.cn;p=3511";

    private static final String LP_ID = "1816082319";

    private static final String LP_URI = "tel:13816082319";

    private static final String USER_ID = "728801465";

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

    public void testAsyncDialog()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String id = fetionAccount.getUserId();
        assertNotNull("User ID is null?", id);

        checker.setCalled(false);
        assertEquals("begin dialog error?", 1, fetionMessage.asyncBeginDialog(
                Long.parseLong(id), beginDialogEventListener, checker));

        waitUntilCalledBack();

        checker.setCalled(false);
        assertEquals("dialog send error?", 1, fetionMessage.asyncDialogSend(
                Long.parseLong(id), MESSAGE, dialogSendEventListener, checker));

        waitUntilCalledBack();

        fetionMessage.asyncEndDialog(Long.parseLong(id));
    }

    public void testAsyncLogin()
    {
        checker.setCalled(false);
        assertTrue("init failed??", fetionSession.init());
        assertEquals("wrong login status?", 1, fetionSession.asyncLogin(
                MOBILE_NUMBER, PASSWORD, loginEventListener, checker));

        waitUntilCalledBack();
    }

    public void testAsyncRelogin()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));
        fetionSession.logout();

        checker.setCalled(false);
        assertEquals("wrong relogin status?", 1, fetionSession.asyncReLogin(
                loginEventListener, checker));

        waitUntilCalledBack();
    }

    public void testAsyncSendSms()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String id = fetionAccount.getUserId();
        assertNotNull("User ID is null?", id);

        checker.setCalled(false);
        assertEquals("send sms failed?", 1, fetionMessage.asyncSendSms(Long
                .parseLong(id), MESSAGE, smsEventListener, checker));

        waitUntilCalledBack();
    }

    public void testAsyncSendSmsByMobileNumber()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        checker.setCalled(false);
        assertEquals("send sms failed?", 1, fetionMessage
                .asyncSendSmsByMobileNumber("13816082319", MESSAGE,
                        smsEventListener, checker));

        waitUntilCalledBack();
    }

    public void testAsyncSendSmsToSelf()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        checker.setCalled(false);
        assertEquals("send sms failed?", 1, fetionMessage.asyncSendSmsToSelf(
                MESSAGE, smsEventListener, checker));

        waitUntilCalledBack();
    }

    public void testAsyncSetUserState()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        checker.setCalled(false);
        fetionAccount.asyncSetUserStatus(EventConstant.STATUS_AWAY, null,
                setStatusEventListener, checker);

        waitUntilCalledBack();

        assertEquals("wrong status?", EventConstant.STATUS_AWAY, fetionAccount
                .getUserStatus());
    }

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

    public void testGangShowName()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        FetionGang gang = new FetionGang();
        gang.setId(1);
        assertEquals("should have no gang showName", "1", fetionAccount
                .getGangShowName(gang));
    }

    public void testGetInfo()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        assertEquals("wrong User Id?", USER_ID, fetionAccount.getUserId());
        assertEquals("wrong password?", PASSWORD, fetionAccount
                .getUserPassword());
        assertEquals("wrong show name?", "honnix", fetionAccount
                .getUserShowName());
        assertEquals("wrong uri?", URI, fetionAccount.getUserUri());
        assertEquals("wrong mobile number?", MOBILE_NUMBER, fetionAccount
                .getUserMobileNumber());
        assertEquals("wrong score?", -1, fetionAccount.getUserScore());
        assertEquals("wrong expire time?", 600, fetionSession.getExpireTime());
    }

    public void testGetInfoByAccount()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String id = LP_ID;

        FetionAccount account = fetionAccount
                .getAccountById(Long.parseLong(id));
        account = fetionAccount.getAccountById(Long.parseLong(id));

        assertFalse("should not be PC user", fetionAccount
                .isPCUserByAccount(account));
        assertEquals("should have been authorized", 1, fetionAccount
                .isAuthorizedByAccount(account));
        assertFalse("should no in blacklist", fetionAccount
                .isInBlacklistByAccount(account));
        assertFalse("should not be online", fetionAccount
                .isOnlineByAccount(account));
        assertEquals("should be on mobile", EventConstant.STATUS_MOBILE,
                fetionAccount.getOnlineStatusByAccount(account));
        assertEquals("wrong showName without impresa?", "老婆", fetionAccount
                .getAccountShowName(account, false));
        assertEquals("wrong showName without impresa?", "老婆", fetionAccount
                .getAccountShowName(account, false));
        assertEquals("wrong showName with impresa?", "老婆", fetionAccount
                .getAccountShowName(account, true));
        assertEquals("wrong showName with impresa?", "老婆", fetionAccount
                .getAccountShowName(account, true));
        assertEquals("wrong groupId?", 2, fetionAccount
                .getAccountGroupId(account));
    }

    public void testGetInfoById()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        FetionAccount account = fetionAccount.getAccountById(Long
                .parseLong(LP_ID));

        assertEquals("wrong id?", Long.parseLong(LP_ID), account.getId());
        assertEquals("wrong uri?", LP_URI, account.getUri());
        assertEquals("wrong localName?", "老婆", account.getLocalName());
        assertEquals("wrong buddyList?", "2", account.getBuddyList());
        assertEquals("wrong groupId?", 0, account.getGroupId());
        assertEquals("wrong relationStatus?", 1, account.getRelationStatus());
        assertEquals("wrong onlineNotify?", 0, account.getOnlineNotify());
        assertEquals("wrong statusCode?", 0, account.getStatusCode());
        assertEquals("wrong onlineStatus?", EventConstant.STATUS_MOBILE,
                account.getOnlineStatus());
        assertEquals("wrong portraitCrc?", 0, account.getPortraitCrc());
        assertNull("should have no personalInfo", account.getPersonalInfo());
        assertEquals("wrong userType?", FetionUserType.FETION_UTYPE_MOBILE,
                account.getUserType());

        FetionGang gang = fetionAccount.getGangById(Long.parseLong(LP_ID));
        assertNull("should have no gang", gang);

        assertFalse("should not be PC user", fetionAccount.isPCUserById(Long
                .parseLong(LP_ID)));
        assertFalse("should not be gang", fetionAccount.isGangById(Long
                .parseLong(LP_ID)));
        assertEquals("should have been authorized", 1, fetionAccount
                .isAuthorizedById(Long.parseLong(LP_ID)));
        assertFalse("should no in blacklist", fetionAccount
                .isInBlacklistById(Long.parseLong(LP_ID)));
        assertFalse("should not be online", fetionAccount.isOnlineById(Long
                .parseLong(LP_ID)));
        assertEquals("should be on mobile", EventConstant.STATUS_MOBILE,
                fetionAccount.getOnlineStatusById(Long.parseLong(LP_ID)));

        fetionAccount.updateAccountInfoById(Long.parseLong(LP_ID));
        fetionAccount.updateAccountInfoAll();
    }

    public void testGetList()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        List<FetionGroup> groupList = fetionAccount.getGroupList();
        assertEquals("should have no group", 2, groupList.size());

        groupList = fetionAccount.getGroupList();
        assertEquals("should have no group", 2, groupList.size());

        List<FetionAccount> accountList = fetionAccount.getAccountList();
        assertEquals("should have two accounts", 2, accountList.size());

        accountList = fetionAccount.getAccountList();
        assertEquals("should have two accounts", 2, accountList.size());

        List<FetionBlacklistItem> blacklist = fetionAccount.getBlacklist();
        assertEquals("should have no blacklist", 0, blacklist.size());

        List<FetionGang> gangList = fetionAccount.getGangList();
        assertEquals("should have no gang", 0, gangList.size());
    }

    public void testGetMessage()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String id = fetionAccount.getUserId();
        assertNotNull("User ID is null?", id);

        assertNull("should be no message", fetionMessage.getMessage(Long
                .parseLong(id)));
    }

    public void testGetPersonalInfo()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        FetionPersonalInfo personalInfo = fetionAccount.getPersonalInfo();

        assertEquals("wrong nickname?", "honnix", personalInfo.getNickname());
        assertEquals("wrong impresa?", "", personalInfo.getImpresa());
        assertEquals("wrong gender", 1, personalInfo.getGender());
        assertEquals("wrong nation?", "CN", personalInfo.getNation());
        assertEquals("wrong province?", "sh", personalInfo.getProvince());
        assertEquals("wrong city?", 21, personalInfo.getCity());
        assertEquals("wrong ivrEnabled?", 1, personalInfo.getIvrEnabled());
        assertEquals("wrong portraitCrc?", -709378836, personalInfo
                .getPortraitCrc());
        assertEquals("wrong provisioning?", 0, personalInfo.getProvisioning());
        assertEquals("wrong mobileNumber?", MOBILE_NUMBER, personalInfo
                .getMobileNumber());
        assertEquals("wrong name?", "", personalInfo.getName());
        assertEquals("wrong birthday?", "1900-01-01", personalInfo
                .getBirthday());
        assertEquals("wrong birthdayValid?", 0, personalInfo.getBirthdayValid());
        assertEquals("wrong lunarAnimal?", 0, personalInfo.getLunarAnimal());
        assertEquals("wrong horoscope?", 0, personalInfo.getHoroscope());
        assertEquals("wrong profile?", "", personalInfo.getProfile());
        assertEquals("wrong bloodType?", 0, personalInfo.getBloodType());
        assertEquals("wrong occupation?", "", personalInfo.getOccupation());
        assertEquals("wrong hobby?", "", personalInfo.getHobby());
        assertEquals("wrong personalEmail?", "", personalInfo
                .getPersonalEmail());
        assertEquals("wrong workEmail?", "", personalInfo.getWorkEmail());
        assertEquals("wrong otherEmail?", "", personalInfo.getOtherEmail());
        assertEquals("wrong primaryEmail?", 0, personalInfo.getPrimaryEmail());
        assertEquals("wrong jobTitle?", "", personalInfo.getJobTitle());
        assertEquals("wrong homePhone?", "", personalInfo.getHomePhone());
        assertEquals("wrong workPhone?", "", personalInfo.getWorkPhone());
        assertEquals("wrong otherPhone?", "", personalInfo.getOtherPhone());
        assertEquals("wrong company?", "", personalInfo.getCompany());
        assertNull("wrong companyWebsite?", personalInfo.getCompanyWebsite());
        assertEquals("wrong matchEnabled?", 0, personalInfo.getMatchEnabled());
    }

    public void testLogin()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));
    }

    public void testRemoveFontTag()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String message = "<Font>this is just a test message.</Font>";
        message = fetionMessage.removeFontTag(message);
        message = fetionMessage.removeFontTag(message);

        assertEquals("wrong message?", "this is just a test message.", message);
    }

    public void testSendSms()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String id = fetionAccount.getUserId();
        assertNotNull("User ID is null?", id);

        assertTrue("send sms failed?", fetionMessage.sendSms(
                Long.parseLong(id), MESSAGE));
    }

    public void testSendSmsByMobileNumber()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));
        assertTrue("send sms failed?", fetionMessage.sendSmsByMobileNumber(
                "13816082319", MESSAGE));
    }

    public void testSendSmsToSelf()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));
        fetionMessage.setCatSmsEnabled(false);
        assertTrue("send sms failed??", fetionMessage.sendSmsToSelf("自动安装盘"));
        fetionMessage.setCatSmsEnabled(true);
        assertTrue(
                "send sms failed??",
                fetionMessage
                        .sendSmsToSelf("this is a very very very very very very very very very very long long long long long long messsage."));
    }

    public void testServer()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        fetionSession.setServerAddress("192.168.17.2:80");
        assertEquals("wrong server address?", "192.168.17.2:80", fetionSession
                .getServerAddress());
        assertEquals("wrong server address?", "192.168.17.2:80", fetionSession
                .getServerAddress());

        fetionSession.setUnknownServerAddress();
        assertNull("should have no server address", fetionSession
                .getServerAddress());
    }

    public void testSetSystemMessageEventListener()
    {
        assertTrue("init failed??", fetionSession.init());
        fetionSession.setSystemMessageEventListener(systemMessageEventListener,
                checker);
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));
    }

    public void testProxy()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        FetionProxyInfo proxyInfo = new FetionProxyInfo();
        proxyInfo.setHost("192.168.17.2");
        proxyInfo.setPort("80");
        proxyInfo.setType(FetionProxyType.HTTP);

        fetionSession.setProxy(proxyInfo);
        proxyInfo = fetionSession.getProxy();

        assertEquals("wrong host?", "192.168.17.2", proxyInfo.getHost());
        assertEquals("wrong port?", "80", proxyInfo.getPort());
        assertEquals("wrong type", FetionProxyType.HTTP, proxyInfo.getType());
    }

}
