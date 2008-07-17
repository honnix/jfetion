package com.honnix.jfetion;

import junit.framework.TestCase;
import com.honnix.jfetion.impl.FetionImpl;

public class TestFetionImpl
    extends TestCase
{

    protected void setUp()
        throws Exception
    {
    }

    protected void tearDown()
        throws Exception
    {
    }

    public void testLogin()
    {
        assertTrue("init failed??", FetionImpl.getFetion().intit());
        assertTrue("login failed??", FetionImpl.getFetion().login(
                "13761089478", "548026"));
        FetionImpl.getFetion().logout();
        FetionImpl.getFetion().terminate();
    }

    public void testSend()
    {
        assertTrue("init failed??", FetionImpl.getFetion().intit());
        assertTrue("login failed??", FetionImpl.getFetion().login(
                "13761089478", "548026"));
        assertTrue("send sms failed??", FetionImpl.getFetion().sendSmsToSelf("sent from jni"));
        FetionImpl.getFetion().logout();
        FetionImpl.getFetion().terminate();
    }

}
