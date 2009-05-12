/**
 * FetionAccount.java
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
 * Data structure of account.
 * 
 */
public class FetionAccount
{

    private long id;

    private String uri;

    private String localName;

    private String buddyList;

    private int groupId;

    private int relationStatus;

    private int onlineNotify;

    private int statusCode;

    private int onlineStatus;

    private long portraitCrc;

    private int userType;

    private FetionPersonalInfo personalInfo;

    public FetionAccount()
    {
        super();
    }

    /**
     * @return the buddyList
     */
    public String getBuddyList()
    {
        return buddyList;
    }

    /**
     * @return the groupId
     */
    public int getGroupId()
    {
        return groupId;
    }

    /**
     * @return the id
     */
    public long getId()
    {
        return id;
    }

    /**
     * @return the localName
     */
    public String getLocalName()
    {
        return localName;
    }

    /**
     * @return the onlineNotify
     */
    public int getOnlineNotify()
    {
        return onlineNotify;
    }

    /**
     * @return the onlineStatus
     */
    public int getOnlineStatus()
    {
        return onlineStatus;
    }

    /**
     * @return the personalInfo
     */
    public FetionPersonalInfo getPersonalInfo()
    {
        return personalInfo;
    }

    /**
     * @return the portraitCrc
     */
    public long getPortraitCrc()
    {
        return portraitCrc;
    }

    /**
     * @return the relationStatus
     */
    public int getRelationStatus()
    {
        return relationStatus;
    }

    /**
     * @return the statusCode
     */
    public int getStatusCode()
    {
        return statusCode;
    }

    /**
     * @return the uri
     */
    public String getUri()
    {
        return uri;
    }

    /**
     * @return the userType
     */
    public int getUserType()
    {
        return userType;
    }

    /**
     * @param buddyList
     *            the buddyList to set
     */
    public void setBuddyList(String buddyList)
    {
        this.buddyList = buddyList;
    }

    /**
     * @param groupId
     *            the groupId to set
     */
    public void setGroupId(int groupId)
    {
        this.groupId = groupId;
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
     * @param localName
     *            the localName to set
     */
    public void setLocalName(String localName)
    {
        this.localName = localName;
    }

    /**
     * @param onlineNotify
     *            the onlineNotify to set
     */
    public void setOnlineNotify(int onlineNotify)
    {
        this.onlineNotify = onlineNotify;
    }

    /**
     * @param onlineStatus
     *            the onlineStatus to set
     */
    public void setOnlineStatus(int onlineStatus)
    {
        this.onlineStatus = onlineStatus;
    }

    /**
     * @param personalInfo
     *            the personalInfo to set
     */
    public void setPersonalInfo(FetionPersonalInfo personalInfo)
    {
        this.personalInfo = personalInfo;
    }

    /**
     * @param portraitCrc
     *            the portraitCrc to set
     */
    public void setPortraitCrc(long portraitCrc)
    {
        this.portraitCrc = portraitCrc;
    }

    /**
     * @param relationStatus
     *            the relationStatus to set
     */
    public void setRelationStatus(int relationStatus)
    {
        this.relationStatus = relationStatus;
    }

    /**
     * @param statusCode
     *            the statusCode to set
     */
    public void setStatusCode(int statusCode)
    {
        this.statusCode = statusCode;
    }

    /**
     * @param uri
     *            the uri to set
     */
    public void setUri(String uri)
    {
        this.uri = uri;
    }

    /**
     * @param userType
     *            the userType to set
     */
    public void setUserType(int userType)
    {
        this.userType = userType;
    }

}
