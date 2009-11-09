/**
 * FetionProxyType.java
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
package com.honnix.jfetion.impl.data;

/**
 * 
 * This class defines constants for proxy type.
 * 
 */
public final class FetionProxyType
{

    public static final int DIRECT = 0;

    public static final int HTTP = 1;

    public static final int SOCKET4 = 2;

    public static final int SOCKET5 = 3;

    public static final int MAX = 4;

    private FetionProxyType()
    {
        super();
    }

}
