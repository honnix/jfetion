/**
 * FetionScheduledSMS.java
 * 
 * Copyright : (C) 2009 by Honnix
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

import java.util.List;

/**
 * Data structure of scheduled SMS.
 * 
 */
public final class FetionScheduledSMS
{

    private int id;

    private int version;

    private String sendTime;

    private String message;

    private List<FetionAccount> receiverList;

    public FetionScheduledSMS()
    {
        super();
    }

    /**
     * @return the id
     */
    public int getId()
    {
        return id;
    }

    /**
     * @return the message
     */
    public String getMessage()
    {
        return message;
    }

    /**
     * @return the receiverList
     */
    public List<FetionAccount> getReceiverList()
    {
        return receiverList;
    }

    /**
     * @return the sendTime
     */
    public String getSendTime()
    {
        return sendTime;
    }

    /**
     * @return the version
     */
    public int getVersion()
    {
        return version;
    }

    /**
     * @param id
     *            the id to set
     */
    public void setId(int id)
    {
        this.id = id;
    }

    /**
     * @param message
     *            the message to set
     */
    public void setMessage(String message)
    {
        this.message = message;
    }

    /**
     * @param receiverList
     *            the receiverList to set
     */
    public void setReceiverList(List<FetionAccount> receiverList)
    {
        this.receiverList = receiverList;
    }

    /**
     * @param sendTime
     *            the sendTime to set
     */
    public void setSendTime(String sendTime)
    {
        this.sendTime = sendTime;
    }

    /**
     * @param version
     *            the version to set
     */
    public void setVersion(int version)
    {
        this.version = version;
    }

}
