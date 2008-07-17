/**
 * FetionImpl.java
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
package com.honnix.jfetion.impl;

import com.honnix.jfetion.Fetion;

/**
 * 
 */
public class FetionImpl
    implements Fetion
{

    private static Fetion fetion = new FetionImpl();

    static
    {
        System.loadLibrary("jfetion");
    }

    public static Fetion getFetion()
    {
        return fetion;
    }

    private FetionImpl()
    {
        super();
    }

    /*
     * (non-Javadoc)
     * 
     * @see com.honnix.jfetion.Fetion#intit()
     */
    public native boolean intit();

    /*
     * (non-Javadoc)
     * 
     * @see com.honnix.jfetion.Fetion#login(java.lang.String, java.lang.String)
     */
    public native boolean login(String uid, String password);

    /*
     * (non-Javadoc)
     * 
     * @see com.honnix.jfetion.Fetion#logout()
     */
    public native void logout();

    /*
     * (non-Javadoc)
     * 
     * @see com.honnix.jfetion.Fetion#sendSmsToSelf(java.lang.String)
     */
    public native boolean sendSmsToSelf(String message);

    /*
     * (non-Javadoc)
     * 
     * @see com.honnix.jfetion.Fetion#terminate()
     */
    public native void terminate();

}
