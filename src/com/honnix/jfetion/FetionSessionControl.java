/**
 * Fetion.java
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

/**
 * 
 */
public interface FetionSessionControl
{

    int asyncLogin(String userId, String password, EventListener eventListener,
            Object... args);

    int asyncReLogin(EventListener eventListener, Object... args);

    boolean closeNetwork();

    int getExpireTime();

    String getProxy();

    boolean init();

    boolean login(String id, String password);

    void logout();

    void setLoginStatus(int status);

    boolean setProxy(String proxy);

    void setSystemMessageEventListener(EventListener eventListener,
            Object... args);

    void setUnknownProxy();
    
    void terminate();

}