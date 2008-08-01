package com.honnix.jfetion;

import junit.framework.TestCase;

import com.honnix.jfetion.impl.FetionFactory;
import com.honnix.jfetion.impl.event.BeginDialogEventListener;
import com.honnix.jfetion.impl.event.DialogSendEventListener;
import com.honnix.jfetion.impl.event.EventConstant;
import com.honnix.jfetion.impl.event.LoginEventListener;
import com.honnix.jfetion.impl.event.SmsEventListener;
import com.honnix.jfetion.impl.event.SetStateEventListener;
import com.honnix.jfetion.impl.event.SystemMessageEventListener;

public class TestFetionImpl
    extends TestCase
{

    private static final String MOBILE_NUMBER = "13761089478";

    private static final String PASSWORD = "honnix548";

    private static final String MESSAGE = "sent using JNI";

    private Checker checker;

    private FetionSessionControl fetionSession;

    private FetionAccountControl fetionAccount;

    private FetionMessageControl fetionMessage;

    private LoginEventListener loginEventListener;

    private SystemMessageEventListener systemMessageEventListener;

    private SetStateEventListener setStatusEventListener;

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
        setStatusEventListener = new SetStateEventListener();
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

    public void testDialog()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        String id = fetionAccount.getUserId();
        assertNotNull("User ID is null?", id);

        assertEquals("begin dialog error?", 1, fetionMessage.beginDialog(Long
                .parseLong(id)));

        checker.setCalled(false);
        assertEquals("dialog send error?", 1, fetionMessage.dialogSend(Long
                .parseLong(id), MESSAGE));

        fetionMessage.endDialog(Long.parseLong(id));
    }

    public void testAsyncLogin()
    {
        checker.setCalled(false);
        assertTrue("init failed??", fetionSession.init());
        assertEquals("wrong login status?", 1, fetionSession.asyncLogin(
                MOBILE_NUMBER, PASSWORD, loginEventListener));

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
                .asyncSendSmsByMobileNumber(MOBILE_NUMBER, MESSAGE,
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
        fetionAccount.asyncSetUserState(EventConstant.STATE_AWAY, null,
                setStatusEventListener, checker);

        waitUntilCalledBack();

        assertEquals("wrong status?", EventConstant.STATE_AWAY, fetionAccount
                .getUserState());
    }

    public void testGetInfo()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));

        assertEquals("wrong User Id?", "1234", fetionAccount.getUserId());
        assertEquals("wrong password?", PASSWORD, fetionAccount
                .getUserPassword());
        assertEquals("wrong show name?", "honnix", fetionAccount
                .getUserShowName());
        assertEquals("wrong uri?", "honnix", fetionAccount.getUserUri());
        assertEquals("wrong mobile number?", MOBILE_NUMBER, fetionAccount
                .getUserMobileNumber());
        assertEquals("wrong score?", 0, fetionAccount.getUserScore());
        assertEquals("wrong expire time?", 100, fetionSession.getExpireTime());
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

    public void testLogin()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));
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
                MOBILE_NUMBER, MESSAGE));
    }

    public void testSendSmsToSelf()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));
        assertTrue("send sms failed??", fetionMessage.sendSmsToSelf(MESSAGE));
    }

    public void testSetSystemMessageEventListener()
    {
        fetionSession.setSystemMessageEventListener(systemMessageEventListener,
                checker);
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
                PASSWORD));
    }

}
