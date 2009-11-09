/**
 * EventConstant.java
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
package com.honnix.jfetion.impl.event;

/**
 * 
 * This class defines all event related constants.
 * 
 */
public final class EventConstant
{

    private static final int EVENT_BASE = 0x0000;

    public static final int EVENT_SPARE = 0x00F0;

    public static final int LOGIN_CONNECTING = EVENT_BASE + 0x0001;

    public static final int LOGIN_WAIT_AUTH = EVENT_BASE + 0x0002;

    public static final int LOGIN_AUTH_OK = EVENT_BASE + 0x0003;

    public static final int LOGIN_FAIL = EVENT_BASE + 0x0004;

    public static final int LOGIN_NETWORK_ERROR = EVENT_BASE + 0x0005;

    public static final int LOGIN_UNKNOWN_ERROR = EVENT_BASE + 0x0006;

    public static final int LOGIN_UNKNOWN_USER = EVENT_BASE + 0x0007;

    public static final int LOGIN_GCL_GETTING = EVENT_BASE + 0x0008;

    public static final int LOGIN_GCL_OK = EVENT_BASE + 0x0009;

    public static final int LOGIN_GCL_FAIL = EVENT_BASE + 0x000A;

    public static final int LOGIN_GP_GETTING = EVENT_BASE + 0x000B;

    public static final int LOGIN_GP_OK = EVENT_BASE + 0x000C;

    public static final int LOGIN_GP_FAIL = EVENT_BASE + 0x000D;

    public static final int LOGIN_OK = EVENT_BASE + 0x000E;

    public static final int LOGIN_TIMEOUT = EVENT_BASE + 0x000F;

    public static final int LOGIN_URI_ERROR = EVENT_SPARE + 0x0001;

    public static final int LOGIN_SERVER_ERROR = EVENT_SPARE + 0x0002;

    public static final int LOGIN_SERVER_REFUSE = EVENT_SPARE + 0x0003;

    public static final int LOGIN_GSML_OK = EVENT_SPARE + 0x0004;

    public static final int LOGIN_GSML_FAIL = EVENT_SPARE + 0x0005;

    public static final int NEW_MESSAGE = EVENT_BASE + 0x0010;

    public static final int NEW_GANG_MESSAGE = EVENT_BASE + 0x0011;

    public static final int SYS_MESSAGE = EVENT_BASE + 0x0012;

    public static final int SMS_OK = EVENT_BASE + 0x0020;

    public static final int SMS_FAIL = EVENT_BASE + 0x0021;

    public static final int SMS_TIMEOUT = EVENT_BASE + 0x0022;

    public static final int SMS_UNKNOWN_ERROR = EVENT_BASE + 0x0023;

    public static final int SMS_FAIL_LIMIT = EVENT_BASE + 0x0024;

    public static final int DIA_BEGIN_TRYING = EVENT_BASE + 0x0030;

    public static final int DIA_BEGIN_OK = EVENT_BASE + 0x0031;

    public static final int DIA_BEGIN_FAIL = EVENT_BASE + 0x0032;

    public static final int DIA_BEGIG_TIMEOUT = EVENT_BASE + 0x0033;

    public static final int DIA_SEND_OK = EVENT_BASE + 0x0034;

    public static final int DIA_SEND_FAIL = EVENT_BASE + 0x0035;

    public static final int DIA_SEND_TIMEOUT = EVENT_BASE + 0x0036;

    public static final int DIA_UNKNOWN_ERROR = EVENT_BASE + 0x0037;

    public static final int STATUS_UNSET = EVENT_BASE + 0x0040;

    public static final int STATUS_ONLINE = EVENT_BASE + 0x0042;

    public static final int STATUS_BUSY = EVENT_BASE + 0x0043;

    public static final int STATUS_OFFLINE = EVENT_BASE + 0x0044;

    public static final int STATUS_AWAY = EVENT_BASE + 0x0045;

    public static final int STATUS_MEETING = EVENT_BASE + 0x0046;

    public static final int STATUS_PHONE = EVENT_BASE + 0x0047;

    public static final int STATUS_DINNER = EVENT_BASE + 0x0048;

    public static final int STATUS_EXTENDED_AWAY = EVENT_BASE + 0x0049;

    public static final int STATUS_NUM_PRIMITIVES = EVENT_BASE + 0x004A;

    public static final int STATUS_WAITING_AUTH = EVENT_BASE + 0x004B;

    public static final int STATUS_REFUSE = EVENT_BASE + 0x004C;

    public static final int STATUS_BLACK = EVENT_BASE + 0x004D;

    public static final int STATUS_MOBILE = EVENT_BASE + 0x004E;

    public static final int ACCOUNT_UPDATE_OK = EVENT_BASE + 0x0050;

    public static final int ADD_GROUP_OK = EVENT_BASE + 0x0051;

    public static final int ADD_GROUP_FAIL = EVENT_BASE + 0x0052;

    public static final int ADD_GROUP_TIMEOUT = EVENT_BASE + 0x0053;

    public static final int DEL_GROUP_OK = EVENT_BASE + 0x0054;

    public static final int DEL_GROUP_FAIL = EVENT_BASE + 0x0055;

    public static final int DEL_GROUP_TIMEOUT = EVENT_BASE + 0x0056;

    public static final int RENAME_GROUP_OK = EVENT_BASE + 0x0057;

    public static final int RENAME_GROUP_FAIL = EVENT_BASE + 0x0058;

    public static final int RENAME_GROUP_TIMEOUT = EVENT_BASE + 0x0059;

    public static final int SET_BUDDY_INFO_OK = EVENT_BASE + 0x005A;

    public static final int SET_BUDDY_INFO_FAIL = EVENT_BASE + 0x005B;

    public static final int SET_BUDDY_INFO_TIMEOUT = EVENT_BASE + 0x005C;

    public static final int ADD_ACCOUNT_APP = EVENT_BASE + 0x005D;

    public static final int ADD_BUDDY_OK = EVENT_BASE + 0x005E;

    public static final int SYS_NETWORK_ERROR = EVENT_BASE + 0x0061;

    public static final int SYS_DEREGISTERED = EVENT_BASE + 0x0062;

    public static final int SET_STATUS_OK = EVENT_BASE + 0x0063;

    public static final int SET_STATUS_FAIL = EVENT_BASE + 0x0064;

    public static final int SET_STATUS_TIMEOUT = EVENT_BASE + 0x0065;

    public static final int SET_IMPRESA_OK = EVENT_BASE + 0x0066;

    public static final int SET_IMPRESA_FAIL = EVENT_BASE + 0x0067;

    public static final int ADD_BLACKLIST_OK = EVENT_BASE + 0x0071;

    public static final int ADD_BLACKLIST_FAIL = EVENT_BASE + 0x0072;

    public static final int ADD_BLACKLIST_TIMEOUT = EVENT_BASE + 0x0073;

    public static final int REMOVE_BLACKLIST_OK = EVENT_BASE + 0x0074;

    public static final int REMOVE_BLACKLIST_FAIL = EVENT_BASE + 0x0075;

    public static final int REMOVE_BLACKLIST_TIMEOUT = EVENT_BASE + 0x0076;

    public static final int SCHEDULED_SMS_FAIL = EVENT_BASE + 0x0077;

    public static final int SCHEDULED_SMS_SUCCESS = EVENT_BASE + 0x0078;

    public static final int DEL_BUDDY_OK = EVENT_BASE + 0x0081;

    public static final int DEL_BUDDY_FAIL = EVENT_BASE + 0x0082;

    public static final int DEL_BUDDY_TIMEOUT = EVENT_BASE + 0x0083;

    public static final int MOVE_GROUP_OK = EVENT_BASE + 0x0084;

    public static final int MOVE_GROUP_FAIL = EVENT_BASE + 0x0085;

    public static final int RECEIVE_FILE = EVENT_BASE + 0x0087;

    public static final int CURRENT_VERSION = EVENT_BASE + 0x0088;

    public static final int GET_GANG_LIST_OK = EVENT_BASE + 0x0091;

    public static final int GET_GANG_LIST_FAIL = EVENT_BASE + 0x0092;

    public static final int GANG_GP_OK = EVENT_BASE + 0x0093;

    public static final int GANG_SEND_OK = EVENT_BASE + 0x0094;

    public static final int GANG_SEND_TIMEOUT = EVENT_BASE + 0x0095;

    public static final int GANG_SEND_FAIL = EVENT_BASE + 0x0096;

    public static final int GANG_SMS_OK = EVENT_BASE + 0x0097;

    public static final int GANG_SMS_TIMEOUT = EVENT_BASE + 0x0098;

    public static final int GANG_SMS_FAIL = EVENT_BASE + 0x0099;

    public static final int GANG_SMS_FAIL_LIMIT = EVENT_BASE + 0x009A;

    private EventConstant()
    {
        super();
    }

}
