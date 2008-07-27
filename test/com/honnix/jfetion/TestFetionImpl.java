package com.honnix.jfetion;

import junit.framework.TestCase;

import com.honnix.jfetion.impl.FetionFactory;
import com.honnix.jfetion.impl.data.FetionAccount;

public class TestFetionImpl
    extends TestCase
{

    private FetionSessionControl fetionSession;

    private FetionAccountControl fetionAccount;

    private FetionMessageControl fetionMessage;

    protected void setUp()
        throws Exception
    {
        fetionSession = FetionFactory.getFetionSessionControl();
        fetionAccount = FetionFactory.getFetionAccountControl();
        fetionMessage = FetionFactory.getFetionMessageControl();
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

    public void testSetLoginStatus()
    {
        assertTrue("init failed??", fetionSession.init());
        assertTrue("login failed??", fetionSession.login("13761089478",
                "honnix548"));

        fetionAccount.setLoginStatus(76);
        FetionAccount account = new FetionAccount();
        account.setId(728801465);
        //account.setLocalName("honnix");

        assertEquals("Wrong status?", 76, fetionAccount
                .getOnlineStatusByAccount(account));
    }

}
