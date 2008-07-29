/**
 * TestFetion.java
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

import com.honnix.jfetion.impl.FetionFactory;
import com.honnix.jfetion.impl.data.FetionPersonalInfo;
import com.honnix.jfetion.impl.event.EventConstant;

/**
 * 
 */
public class TestFetion
{

    private class MockEventListener
        implements EventListener
    {

        public void callback(int message, long firstMessageParam,
                long secondMessageParam, Object... args)
        {
            switch (message)
            {
            case EventConstant.LOGIN_CONNECTING:
                System.out.println("login connecting");
                break;

            case EventConstant.LOGIN_AUTH_OK:
                System.out.println("login auth ok");
                break;

            case EventConstant.LOGIN_OK:
                System.out.println("login ok");
                synchronized (TestFetion.class)
                {
                    ((TestFetion) args[0]).isCalled = true;
                }
                break;

            case EventConstant.LOGIN_FAIL:
            case EventConstant.LOGIN_NETWORK_ERROR:
                System.out.println("login fail or network error");
                synchronized (TestFetion.class)
                {
                    ((TestFetion) args[0]).isCalled = true;
                }
                break;

            case EventConstant.LOGIN_GCL_GETTING:
                System.out.println("login gcl getting");
                break;

            case EventConstant.LOGIN_GCL_OK:
                System.out.println("login gcl ok");
                break;

            case EventConstant.LOGIN_GCL_FAIL:
                System.out.println("login gcl fail");
                break;

            case EventConstant.LOGIN_GP_GETTING:
                System.out.println("login gp getting");
                break;

            case EventConstant.LOGIN_GP_OK:
                System.out.println("login gp ok");

            case EventConstant.LOGIN_GP_FAIL:
                System.out.println("login gp fail");
                break;
            }
        }
    }

    private static final String MOBILE_NUMBER = "13761089478";

    private static final String PASSWORD = "honnix548";

    private static final String MESSAGE = "sent using JNI";

    /**
     * @param args
     */
    public static void main(String[] args)
    {
        TestFetion test = new TestFetion();
        
        test.fetionSession.init();
        
        test.isCalled = false;
        test.fetionSession.asyncLogin(MOBILE_NUMBER, PASSWORD,
                test.mockEventListener, test);
        test.waitUntilCalledBack();

        FetionPersonalInfo personalInfo = test.fetionAccount.getPersonalInfo();
        System.out.println(personalInfo.getBirthday());
        System.out.println(personalInfo.getNickname());
        
        test.fetionMessage.sendSmsToSelf(MESSAGE);

        test.fetionSession.logout();
        test.fetionSession.terminate();
    }

    private boolean isCalled;

    private FetionSessionControl fetionSession;

    private FetionAccountControl fetionAccount;

    private FetionMessageControl fetionMessage;

    private MockEventListener mockEventListener;

    private TestFetion()
    {
        fetionSession = FetionFactory.getFetionSessionControl();
        fetionAccount = FetionFactory.getFetionAccountControl();
        fetionMessage = FetionFactory.getFetionMessageControl();

        mockEventListener = new MockEventListener();
    }

    private void waitUntilCalledBack()
    {
        while (true)
        {
            synchronized (TestFetion.class)
            {
                if (isCalled)
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

}
