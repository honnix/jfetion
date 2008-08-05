/**
 * DialogSendEventListener.java
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
public class DialogSendEventListener
    implements EventListener
{

    /*
     * (non-Javadoc)
     * 
     * @see com.honnix.jfetion.EventListener#callback(int, long, long,
     * java.lang.Object[])
     */
    public void callback(int message, long firstMessageParam,
            long secondMessageParam, Object... args)
    {
        switch (message)
        {
        case EventConstant.DIA_SEND_OK:
            System.out.println("dialog send ok");
            ((Checker) args[0]).setCalled(true);
            break;

        case EventConstant.DIA_SEND_FAIL:
            System.out.println("dialog send fail");
            ((Checker) args[0]).setCalled(true);
            break;

        case EventConstant.DIA_SEND_TIMEOUT:
            System.out.println("dialog send timeout");
            ((Checker) args[0]).setCalled(true);
            break;

        default:
            System.out.println("dialog unknown message: " + message);
            ((Checker) args[0]).setCalled(true);
            break;
        }
    }

}
