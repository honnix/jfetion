/**
 * SystemMessageEventListener.java
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

import com.honnix.jfetion.EventListener;

/**
 *
 */
public class SystemMessageEventListener
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
        System.out.println("message: " + message);
        System.out.println("firstMessageParam: " + firstMessageParam);
        System.out.println("secondMessageParam: " + secondMessageParam);
        System.out.println("args: " + args.toString());
    }

}
