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

/**
 * 
 */
public class TestFetion
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
                ((Checker) args[0]).isCalled = true;
            }
        }

    }

    private static final String MOBILE_NUMBER = "13761089478";

    private static final String PASSWORD = "honnix548";

    private static final String MESSAGE = "sent using JNI";

    private static FetionSessionControl fetionSession;

    private static FetionAccountControl fetionAccount;

    private static FetionMessageControl fetionMessage;

    private static MockEventListener mockEventListener;

    private static Checker checker;

    private static void waitUntilCalledBack()
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

    private TestFetion()
    {
        fetionSession = FetionFactory.getFetionSessionControl();
        fetionAccount = FetionFactory.getFetionAccountControl();
        fetionMessage = FetionFactory.getFetionMessageControl();

        mockEventListener = new MockEventListener();
        checker = new Checker();
    }

    /**
     * @param args
     */
    public static void main(String[] args)
    {
        TestFetion test = new TestFetion();
        test.fetionSession.init();
        test.fetionSession.asyncLogin(MOBILE_NUMBER, PASSWORD,
                mockEventListener, checker);

        waitUntilCalledBack();
    }

}
