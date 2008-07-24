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
package com.honnix.jfetion.impl.data;

/**
 * 
 */
public class FetionMessage
{

    private long id;

    private String message;

    private String messageFormat;

    private long extId;

    /**
     * @return the extId
     */
    public long getExtId()
    {
        return extId;
    }

    /**
     * @return the id
     */
    public long getId()
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
     * @return the messageFormat
     */
    public String getMessageFormat()
    {
        return messageFormat;
    }

    /**
     * @param extId
     *            the extId to set
     */
    public void setExtId(long extId)
    {
        this.extId = extId;
    }

    /**
     * @param userId
     *            the id to set
     */
    public void setId(long id)
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
     * @param messageFormat
     *            the messageFormat to set
     */
    public void setMessageFormat(String messageFormat)
    {
        this.messageFormat = messageFormat;
    }

}
