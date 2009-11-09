/**
 * FetionBlacklistItem.java
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
 * Data structure of blacklist item.
 * 
 */
public class FetionBlacklistItem
{

    private long id;

    private String uri;

    private String localName;

    public FetionBlacklistItem()
    {
        super();
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
     * @return the uri
     */
    public String getUri()
    {
        return uri;
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
     * @param uri
     *            the uri to set
     */
    public void setUri(String uri)
    {
        this.uri = uri;
    }

}
