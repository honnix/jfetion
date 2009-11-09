/**
 * FetionMessageControl.java
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

import java.util.List;

import com.honnix.jfetion.impl.data.FetionAccount;
import com.honnix.jfetion.impl.data.FetionMessage;
import com.honnix.jfetion.impl.data.FetionScheduledSMS;

/**
 * 
 * This interface declares all message related operations.
 * 
 */
public interface FetionMessageControl
{

    int asyncBeginDialog(long who, EventListener eventListener, Object... args);

    int asyncDeleteScheduledSMS(int id, EventListener eventListener,
            Object... args);

    int asyncDialogSend(long who, String message, EventListener eventListener,
            Object... args);

    void asyncEndDialog(long who);

    int asyncSendSms(long who, String message, EventListener eventListener,
            Object... args);

    int asyncSendSmsByMobileNumber(String mobileNumber, String message,
            EventListener eventListener, Object... args);

    int asyncSendSmsToSelf(String message, EventListener eventListener,
            Object... args);

    int asyncSetScheduledSMS(List<FetionAccount> receiverList, String message,
            String sendTime, EventListener eventListener, Object... args);

    boolean beginDialog(long who);

    String convertScheduledSMSReceiverListToString(
            List<FetionAccount> receiverList);

    boolean dialogSend(long who, String message);

    void endDialog(long who);

    FetionMessage getMessage(long id);

    FetionScheduledSMS getScheduledSMSById(int id);

    List<FetionScheduledSMS> getScheduledSMSList();

    String removeFontTag(String message);

    boolean sendNudge(long who);

    boolean sendSms(long who, String message);

    boolean sendSmsByMobileNumber(String mobileNumber, String message);

    boolean sendSmsToSelf(String message);

    void setLongSmsEnabled(boolean enabled);

}
