/**
 * FetionGangMember.java
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
 * Data structure of gang memeber.
 * 
 */
public class FetionGangMember
{

    private long id;

    private String uri;

    private String nickname;

    private String iicNickname;

    private int identity;

    private int status;

    private String clientType;

    public FetionGangMember()
    {
        super();
    }

    /**
     * @return the clientType
     */
    public String getClientType()
    {
        return clientType;
    }

    /**
     * @return the id
     */
    public long getId()
    {
        return id;
    }

    /**
     * @return the identity
     */
    public int getIdentity()
    {
        return identity;
    }

    /**
     * @return the iicNickname
     */
    public String getIicNickname()
    {
        return iicNickname;
    }

    /**
     * @return the nickname
     */
    public String getNickname()
    {
        return nickname;
    }

    /**
     * @return the status
     */
    public int getStatus()
    {
        return status;
    }

    /**
     * @return the uri
     */
    public String getUri()
    {
        return uri;
    }

    /**
     * @param clientType
     *            the clientType to set
     */
    public void setClientType(String clientType)
    {
        this.clientType = clientType;
    }

    /**
     * @param id
     *            the id to set
     */
    public void setId(long id)
    {
        this.id = id;
    }

    /**
     * @param identity
     *            the identity to set
     */
    public void setIdentity(int identity)
    {
        this.identity = identity;
    }

    /**
     * @param iicNickname
     *            the iicNickname to set
     */
    public void setIicNickname(String iicNickname)
    {
        this.iicNickname = iicNickname;
    }

    /**
     * @param nickname
     *            the nickname to set
     */
    public void setNickname(String nickname)
    {
        this.nickname = nickname;
    }

    /**
     * @param status
     *            the status to set
     */
    public void setStatus(int status)
    {
        this.status = status;
    }

    /**
     * @param uri
     *            the uri to set
     */
    public void setUri(String uri)
    {
        this.uri = uri;
    }

}
