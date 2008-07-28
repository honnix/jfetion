package com.honnix.jfetion;

import junit.framework.TestCase;

import com.honnix.jfetion.impl.FetionFactory;
import com.honnix.jfetion.impl.data.FetionAccount;
import com.honnix.jfetion.impl.event.EventConstant;

public class TestFetionImpl
    extends TestCase
{

    private class Checker
    {

        private boolean isCalled;

    }

    private class MockEventListener
        implements EventListener
    {

        public void callback(int message, long firstMessageParam,
                long secondMessageParam, Object... args)
        {
            synchronized (Checker.class)
            {
                //((Checker) args[0]).isCalled = true;
            }
        }

    }

    private static final String MOBILE_NUMBER = "13761089478";

    private static final String PASSWORD = "honnix548";

    private static final String MESSAGE = "sent using JNI";

    private FetionSessionControl fetionSession;

    private FetionAccountControl fetionAccount;

    private FetionMessageControl fetionMessage;

    private MockEventListener mockEventListener;

    private Checker checker;

    private void waitUntilCalledBack()
    {
        while (true)
        {
            synchronized (Checker.class)
            {
                if (checker.isCalled)
                {
                    break;
                }
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

    protected void setUp()
        throws Exception
    {
        fetionSession = FetionFactory.getFetionSessionControl();
        fetionAccount = FetionFactory.getFetionAccountControl();
        fetionMessage = FetionFactory.getFetionMessageControl();

        mockEventListener = new MockEventListener();
        checker = new Checker();
    }

    protected void tearDown()
        throws Exception
    {
        fetionSession.logout();
        fetionSession.terminate();
    }

    public void testAsyncLogin()
    {
        assertTrue("init failed??", fetionSession.init());
        assertEquals("wrong login status?", 1, fetionSession.asyncLogin(
                MOBILE_NUMBER, PASSWORD, mockEventListener));

        waitUntilCalledBack();
    }

    //    public void testAsyncRelogin()
    //    {
    //        assertTrue("init failed??", fetionSession.init());
    //        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    //                PASSWORD));
    //        assertEquals("wrong relogin status?", 0, fetionSession.asyncReLogin(
    //                mockEventListener, this));
    //
    //        waitUntilCalledBack();
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
    //        assertTrue("send sms failed?", fetionMessage.sendSms(Long.parseLong(id), MESSAGE));
    //    }
    //
    //    public void testSetSystemMessageEventListener()
    //    {
    //        assertTrue("init failed??", fetionSession.init());
    //        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    //                PASSWORD));
    //
    //        fetionSession.setSystemMessageEventListener(mockEventListener, this);
    //
    //        waitUntilCalledBack();
    //    }
    //
    //    public void testLogin()
    //    {
    //        assertTrue("init failed??", fetionSession.init());
    //        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    //                PASSWORD));
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
    //    public void testSetLoginStatus()
    //    {
    //        assertTrue("init failed??", fetionSession.init());
    //        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    //                PASSWORD));
    //
    //        fetionSession.setLoginStatus(EventConstant.LOGIN_AUTH_OK);
    //    }
    //
    //    public void testSetUserStatus()
    //    {
    //        assertTrue("init failed??", fetionSession.init());
    //        assertTrue("login failed??", fetionSession.login(MOBILE_NUMBER,
    //                PASSWORD));
    //
    //        fetionAccount.asyncSetUserState(EventConstant.STATUS_AWAY, null,
    //                mockEventListener, this);
    //
    //        waitUntilCalledBack();
    //
    //        FetionAccount account = new FetionAccount();
    //        account.setId(728801465);
    //
    //        assertEquals("wrong status?", EventConstant.STATUS_AWAY, fetionAccount
    //                .getUserState());
    //    }

}
