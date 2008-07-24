package com.honnix.jfetion;

import junit.framework.TestCase;

import com.honnix.jfetion.impl.FetionFactory;

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
        assertTrue("init failed??", FetionFactory.getFetionSessionControl()
                .intit());
        assertTrue("login failed??", FetionFactory.getFetionSessionControl()
                .login("13761089478", "548026"));
        FetionFactory.getFetionSessionControl().logout();
        FetionFactory.getFetionSessionControl().terminate();
    }

    public void testSend()
    {
        assertTrue("init failed??", FetionFactory.getFetionSessionControl()
                .intit());
        assertTrue("login failed??", FetionFactory.getFetionSessionControl()
                .login("13761089478", "548026"));
        assertTrue("send sms failed??", FetionFactory.getFetionMessageControl()
                .sendSmsToSelf("sent from jni"));
        FetionFactory.getFetionSessionControl().logout();
        FetionFactory.getFetionSessionControl().terminate();
    }

}
