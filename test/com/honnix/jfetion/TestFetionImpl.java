package com.honnix.jfetion;

import junit.framework.TestCase;

import com.honnix.jfetion.impl.FetionFactory;
import com.honnix.jfetion.impl.data.FetionAccount;
import com.honnix.jfetion.impl.event.EventConstant;

public class TestFetionImpl
    extends TestCase
{

    private class MockEventListener
        implements EventListener
    {

        public void callback(int message, long firstMessageParam,
                long secondMessageParam, Object... args)
        {
            ((TestFetionImpl) args[0]).isCalled = true;
        }
    }

    private FetionSessionControl fetionSession;

    private FetionAccountControl fetionAccount;

    private FetionMessageControl fetionMessage;

    private MockEventListener mockEventListener;

    private boolean isCalled;

    protected void setUp()
        throws Exception
    {
        fetionSession = FetionFactory.getFetionSessionControl();
        fetionAccount = FetionFactory.getFetionAccountControl();
        fetionMessage = FetionFactory.getFetionMessageControl();

        mockEventListener = new MockEventListener();
        isCalled = false;
    }

    protected void tearDown()
        throws Exception
    {
        fetionSession.logout();
        fetionSession.terminate();
    }

    //    public void testLogin()
    //    {
    //        assertTrue("init failed??", fetionSession.init());
    //        assertTrue("login failed??", fetionSession.login("13761089478",
    //                "honnix548"));
    //    }
    //
    //    public void testSend()
    //    {
    //        assertTrue("init failed??", fetionSession.init());
    //        assertTrue("login failed??", fetionSession.login("13761089478",
    //                "honnix548"));
    //        assertTrue("send sms failed??", fetionMessage
    //                .sendSmsToSelf("sent from jni"));
    //    }

    public void testSetUserStatus()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login("13761089478",
                "honnix548"));

        fetionAccount.asyncSetUserState(EventConstant.STATUS_AWAY, null,
                mockEventListener, this);

        while (true)
        {
            if (isCalled)
            {
                break;
            }

            try
            {
                Thread.sleep(5000);
            }
            catch (InterruptedException e)
            {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

        FetionAccount account = new FetionAccount();
        account.setId(728801465);

        assertEquals("Wrong status?", EventConstant.STATUS_AWAY, fetionAccount
                .getUserState());
    }
}
