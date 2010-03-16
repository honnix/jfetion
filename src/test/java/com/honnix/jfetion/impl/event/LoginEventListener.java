/**
 * LoginEventListener.java
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
package com.honnix.jfetion.impl.event;

import com.honnix.jfetion.Checker;
import com.honnix.jfetion.EventListener;

/**
 * 
 */
public class LoginEventListener
    implements EventListener
{

    /*
     * (non-Javadoc)
     * 
     * @see com.honnix.jfetion.EventListener#callback(int, long, long,
     *      java.lang.Object[])
     */
    public void callback(int message, long firstMessageParam,
            long secondMessageParam, Object... args)
    {
        switch (message)
        {
        case EventConstant.LOGIN_CONNECTING:
            System.out.println("login connecting");
            break;

        case EventConstant.LOGIN_WAIT_AUTH:
            System.out.println("login with auth");
            break;

        case EventConstant.LOGIN_AUTH_OK:
            System.out.println("login auth ok");
            break;

        case EventConstant.LOGIN_OK:
            System.out.println("login ok");
            ((Checker) args[0]).setCalled(true);
            break;

        case EventConstant.LOGIN_FAIL:
        case EventConstant.LOGIN_NETWORK_ERROR:
            System.out.println("login fail or network error");
            ((Checker) args[0]).setCalled(true);
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

        default:
            System.out.println("login unknown message " + message);
            ((Checker) args[0]).setCalled(true);
            break;
        }
    }

}
