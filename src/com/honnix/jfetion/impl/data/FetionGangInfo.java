/**
 * FetionGangInfo.java
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

import java.util.List;

/**
 * 
 * Data structure of gang information.
 * 
 */
public class FetionGangInfo
{

    private String uri;

    private int groupAttributesVersion;

    private String name;

    private String category;

    private String introduction;

    private String bulletin;

    private int portraitCrc;

    private int searchable;

    private int currentMemberCount;

    private int limitMemberCount;

    private String groupActivity;

    private List<FetionGangMember> gangMemberList;

    public FetionGangInfo()
    {
        super();
    }

    /**
     * @return the bulletin
     */
    public String getBulletin()
    {
        return bulletin;
    }

    /**
     * @return the category
     */
    public String getCategory()
    {
        return category;
    }

    /**
     * @return the currentMemberCount
     */
    public int getCurrentMemberCount()
    {
        return currentMemberCount;
    }

    /**
     * @return the gangMemberList
     */
    public List<FetionGangMember> getGangMemberList()
    {
        return gangMemberList;
    }

    /**
     * @return the groupActivity
     */
    public String getGroupActivity()
    {
        return groupActivity;
    }

    /**
     * @return the groupAttributesVersion
     */
    public int getGroupAttributesVersion()
    {
        return groupAttributesVersion;
    }

    /**
     * @return the introduction
     */
    public String getIntroduction()
    {
        return introduction;
    }

    /**
     * @return the limitMemberCount
     */
    public int getLimitMemberCount()
    {
        return limitMemberCount;
    }

    /**
     * @return the name
     */
    public String getName()
    {
        return name;
    }

    /**
     * @return the portraitCrc
     */
    public int getPortraitCrc()
    {
        return portraitCrc;
    }

    /**
     * @return the searchable
     */
    public int getSearchable()
    {
        return searchable;
    }

    /**
     * @return the uri
     */
    public String getUri()
    {
        return uri;
    }

    /**
     * @param bulletin
     *            the bulletin to set
     */
    public void setBulletin(String bulletin)
    {
        this.bulletin = bulletin;
    }

    /**
     * @param category
     *            the category to set
     */
    public void setCategory(String category)
    {
        this.category = category;
    }

    /**
     * @param currentMemberCount
     *            the currentMemberCount to set
     */
    public void setCurrentMemberCount(int currentMemberCount)
    {
        this.currentMemberCount = currentMemberCount;
    }

    /**
     * @param gangMemberList
     *            the gangMemberList to set
     */
    public void setGangMemberList(List<FetionGangMember> gangMemberList)
    {
        this.gangMemberList = gangMemberList;
    }

    /**
     * @param groupActivity
     *            the groupActivity to set
     */
    public void setGroupActivity(String groupActivity)
    {
        this.groupActivity = groupActivity;
    }

    /**
     * @param groupAttributesVersion
     *            the groupAttributesVersion to set
     */
    public void setGroupAttributesVersion(int groupAttributesVersion)
    {
        this.groupAttributesVersion = groupAttributesVersion;
    }

    /**
     * @param introduction
     *            the introduction to set
     */
    public void setIntroduction(String introduction)
    {
        this.introduction = introduction;
    }

    /**
     * @param limitMemberCount
     *            the limitMemberCount to set
     */
    public void setLimitMemberCount(int limitMemberCount)
    {
        this.limitMemberCount = limitMemberCount;
    }

    /**
     * @param name
     *            the name to set
     */
    public void setName(String name)
    {
        this.name = name;
    }

    /**
     * @param portraitCrc
     *            the portraitCrc to set
     */
    public void setPortraitCrc(int portraitCrc)
    {
        this.portraitCrc = portraitCrc;
    }

    /**
     * @param searchable
     *            the searchable to set
     */
    public void setSearchable(int searchable)
    {
        this.searchable = searchable;
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
