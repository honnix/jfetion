/**
 * FetionProxyInfo.java
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
 */
public class FetionProxyInfo
{

    private String host;

    private String port;

    private String user;

    private String password;

    private int type;

    public FetionProxyInfo()
    {
        super();
    }

    /**
     * 
     * @return the host
     */
    public String getHost()
    {
        return host;
    }

    /**
     * 
     * @return the password
     */
    public String getPassword()
    {
        return password;
    }

    /**
     * 
     * @return the port
     */
    public String getPort()
    {
        return port;
    }

    /**
     * 
     * @return the type
     */
    public int getType()
    {
        return type;
    }

    /**
     * 
     * @return the user
     */
    public String getUser()
    {
        return user;
    }

    /**
     * 
     * @param host
     *            the host to set
     */
    public void setHost(String host)
    {
        this.host = host;
    }

    /**
     * 
     * @param password
     *            the password to set
     */
    public void setPassword(String password)
    {
        this.password = password;
    }

    /**
     * 
     * @param port
     *            the port to set
     */
    public void setPort(String port)
    {
        this.port = port;
    }

    /**
     * 
     * @param type
     *            the type to set
     */
    public void setType(int type)
    {
        this.type = type;
    }

    /**
     * 
     * @param user
     *            the user to set
     */
    public void setUser(String user)
    {
        this.user = user;
    }

}
