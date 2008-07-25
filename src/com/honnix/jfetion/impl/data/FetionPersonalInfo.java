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
public class FetionPersonalInfo
{

    private String nickname;

    private String impresa;

    private int gender;

    private String nation;

    private String province;

    private int city;

    private int ivrEnabled;

    private int portraitCrc;

    private int provisioning;

    private String mobileNumber;

    private String name;

    private String birthday;

    private int birthdayValid;

    private int lunarAnimal;

    private int horoscope;

    private String profile;

    private int bloodType;

    private String occupation;

    private String hobby;

    private String personalEmail;

    private String workEmail;

    private String otherEmail;

    private int primaryEmail;

    private String jobTitle;

    private String homePhone;

    private String workPhone;

    private String company;

    private String companyWebsite;

    private int matchEnabled;

    public FetionPersonalInfo()
    {
        super();
    }

    /**
     * @return the birthday
     */
    public String getBirthday()
    {
        return birthday;
    }

    /**
     * @return the birthdayValid
     */
    public int getBirthdayValid()
    {
        return birthdayValid;
    }

    /**
     * @return the bloodType
     */
    public int getBloodType()
    {
        return bloodType;
    }

    /**
     * @return the city
     */
    public int getCity()
    {
        return city;
    }

    /**
     * @return the company
     */
    public String getCompany()
    {
        return company;
    }

    /**
     * @return the companyWebsite
     */
    public String getCompanyWebsite()
    {
        return companyWebsite;
    }

    /**
     * @return the gender
     */
    public int getGender()
    {
        return gender;
    }

    /**
     * @return the hobby
     */
    public String getHobby()
    {
        return hobby;
    }

    /**
     * @return the homePhone
     */
    public String getHomePhone()
    {
        return homePhone;
    }

    /**
     * @return the horoscope
     */
    public int getHoroscope()
    {
        return horoscope;
    }

    /**
     * @return the impresa
     */
    public String getImpresa()
    {
        return impresa;
    }

    /**
     * @return the ivrEnabled
     */
    public int getIvrEnabled()
    {
        return ivrEnabled;
    }

    /**
     * @return the jobTitle
     */
    public String getJobTitle()
    {
        return jobTitle;
    }

    /**
     * @return the lunarAnimal
     */
    public int getLunarAnimal()
    {
        return lunarAnimal;
    }

    /**
     * @return the matchEnabled
     */
    public int getMatchEnabled()
    {
        return matchEnabled;
    }

    /**
     * @return the mobileNumber
     */
    public String getMobileNumber()
    {
        return mobileNumber;
    }

    /**
     * @return the name
     */
    public String getName()
    {
        return name;
    }

    /**
     * @return the nation
     */
    public String getNation()
    {
        return nation;
    }

    /**
     * @return the nickname
     */
    public String getNickname()
    {
        return nickname;
    }

    /**
     * @return the occupation
     */
    public String getOccupation()
    {
        return occupation;
    }

    /**
     * @return the otherEmail
     */
    public String getOtherEmail()
    {
        return otherEmail;
    }

    /**
     * @return the personalEmail
     */
    public String getPersonalEmail()
    {
        return personalEmail;
    }

    /**
     * @return the portraitCrc
     */
    public int getPortraitCrc()
    {
        return portraitCrc;
    }

    /**
     * @return the primaryEmail
     */
    public int getPrimaryEmail()
    {
        return primaryEmail;
    }

    /**
     * @return the profile
     */
    public String getProfile()
    {
        return profile;
    }

    /**
     * @return the province
     */
    public String getProvince()
    {
        return province;
    }

    /**
     * @return the provisioning
     */
    public int getProvisioning()
    {
        return provisioning;
    }

    /**
     * @return the workEmail
     */
    public String getWorkEmail()
    {
        return workEmail;
    }

    /**
     * @return the workPhone
     */
    public String getWorkPhone()
    {
        return workPhone;
    }

    /**
     * @param birthday
     *            the birthday to set
     */
    public void setBirthday(String birthday)
    {
        this.birthday = birthday;
    }

    /**
     * @param birthdayValid
     *            the birthdayValid to set
     */
    public void setBirthdayValid(int birthdayValid)
    {
        this.birthdayValid = birthdayValid;
    }

    /**
     * @param bloodType
     *            the bloodType to set
     */
    public void setBloodType(int bloodType)
    {
        this.bloodType = bloodType;
    }

    /**
     * @param city
     *            the city to set
     */
    public void setCity(int city)
    {
        this.city = city;
    }

    /**
     * @param company
     *            the company to set
     */
    public void setCompany(String company)
    {
        this.company = company;
    }

    /**
     * @param companyWebsite
     *            the companyWebsite to set
     */
    public void setCompanyWebsite(String companyWebsite)
    {
        this.companyWebsite = companyWebsite;
    }

    /**
     * @param gender
     *            the gender to set
     */
    public void setGender(int gender)
    {
        this.gender = gender;
    }

    /**
     * @param hobby
     *            the hobby to set
     */
    public void setHobby(String hobby)
    {
        this.hobby = hobby;
    }

    /**
     * @param homePhone
     *            the homePhone to set
     */
    public void setHomePhone(String homePhone)
    {
        this.homePhone = homePhone;
    }

    /**
     * @param horoscope
     *            the horoscope to set
     */
    public void setHoroscope(int horoscope)
    {
        this.horoscope = horoscope;
    }

    /**
     * @param impresa
     *            the impresa to set
     */
    public void setImpresa(String impresa)
    {
        this.impresa = impresa;
    }

    /**
     * @param ivrEnabled
     *            the ivrEnabled to set
     */
    public void setIvrEnabled(int ivrEnabled)
    {
        this.ivrEnabled = ivrEnabled;
    }

    /**
     * @param jobTitle
     *            the jobTitle to set
     */
    public void setJobTitle(String jobTitle)
    {
        this.jobTitle = jobTitle;
    }

    /**
     * @param lunarAnimal
     *            the lunarAnimal to set
     */
    public void setLunarAnimal(int lunarAnimal)
    {
        this.lunarAnimal = lunarAnimal;
    }

    /**
     * @param matchEnabled
     *            the matchEnabled to set
     */
    public void setMatchEnabled(int matchEnabled)
    {
        this.matchEnabled = matchEnabled;
    }

    /**
     * @param mobileNumber
     *            the mobileNumber to set
     */
    public void setMobileNumber(String mobileNumber)
    {
        this.mobileNumber = mobileNumber;
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
     * @param nation
     *            the nation to set
     */
    public void setNation(String nation)
    {
        this.nation = nation;
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
     * @param occupation
     *            the occupation to set
     */
    public void setOccupation(String occupation)
    {
        this.occupation = occupation;
    }

    /**
     * @param otherEmail
     *            the otherEmail to set
     */
    public void setOtherEmail(String otherEmail)
    {
        this.otherEmail = otherEmail;
    }

    /**
     * @param personalEmail
     *            the personalEmail to set
     */
    public void setPersonalEmail(String personalEmail)
    {
        this.personalEmail = personalEmail;
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
     * @param primaryEmail
     *            the primaryEmail to set
     */
    public void setPrimaryEmail(int primaryEmail)
    {
        this.primaryEmail = primaryEmail;
    }

    /**
     * @param profile
     *            the profile to set
     */
    public void setProfile(String profile)
    {
        this.profile = profile;
    }

    /**
     * @param province
     *            the province to set
     */
    public void setProvince(String province)
    {
        this.province = province;
    }

    /**
     * @param provisioning
     *            the provisioning to set
     */
    public void setProvisioning(int provisioning)
    {
        this.provisioning = provisioning;
    }

    /**
     * @param workEmail
     *            the workEmail to set
     */
    public void setWorkEmail(String workEmail)
    {
        this.workEmail = workEmail;
    }

    /**
     * @param workPhone
     *            the workPhone to set
     */
    public void setWorkPhone(String workPhone)
    {
        this.workPhone = workPhone;
    }

}
