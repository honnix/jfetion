CC=gcc
LD=g++
TARGET_DIR=build
OS=$(shell uname)

ifeq ($(OS), Darwin)
	CFLAGS=-DDEBUG -arch i386 -arch ppc -Wall -I/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers/ -I../include
	LDFLAGS=-dynamiclib -arch i386 -arch ppc -Wall -fpic ../lib/libfetion_mac.a -lpthread -lcurl -lcrypto -compatibility_version 1.0.0 -current_version 1.3.0
	TARGET=libjfetion.dylib
else
	CFLAGS=-DDEBUG -ggdb -Wall -I/opt/jdk/include -I/opt/jdk/include/linux -I../include
	LDFLAGS=-shared -Wall -fpic ../lib/libfetion_32.a -lpthread -lcurl
	TARGET=libjfetion.so
endif

all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/$(TARGET): $(TARGET_DIR)/FetionImpl.o
	$(LD) -o $(TARGET_DIR)/$(TARGET) $(TARGET_DIR)/FetionImpl.o $(LDFLAGS)

$(TARGET_DIR)/FetionImpl.o: FetionImpl.c FetionImpl.h FetionHelper.h
	$(CC) $(CFLAGS) -c -o $(TARGET_DIR)/FetionImpl.o FetionImpl.c

clean:
	rm -rf $(TARGET_DIR)/*.* TAGS

etags:
	find ./ -name '*.[hc]' | xargs etags

.PHONY: all clean etags
