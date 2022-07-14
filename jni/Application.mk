NDK_TOOLCHAIN_VERSION := 4.8

#APP_ABI := armeabi armeabi-v7a x86 mips

APP_PLATFORM := android-8
APP_STL := stlport_static
APP_CPPFLAGS += -std=c++11 -frtti -fexceptions 

APP_CFLAGS += -Wno-error=format-security