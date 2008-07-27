package com.honnix.jfetion.impl.event;


public final class EventConstant
{

    private EventConstant()
    {
        super();
    }
    
    private static final int EVENT_BASE = 0x0000;
    
    private static final int EVENT_SPARE = 0x00F0;
    
    private static final int LOGIN_CONNECTING = EVENT_BASE + 0x0001;
    
    private static final int LOGIN_WAIT_AUTH = EVENT_BASE + 0x0002;
    
    private static final int LOGIN_AUTH_OK = EVENT_BASE + 0x0003;
    
    private static final int LOGIN_FAIL = EVENT_BASE + 0x0004;
}
