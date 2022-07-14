LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := recplayer-tmg-wrapper
LOCAL_CFLAGS := -Werror -std=gnu++11
LOCAL_C_INCLUDES := $(LOCAL_PATH) $(JNI_PATH)
LOCAL_SRC_FILES  := src/RecPlayer.cc

LOCAL_SHARED_LIBRARIES := libjpeg
LOCAL_STATIC_LIBRARIES := recplayer-tmg

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_LDFLAGS += -ljnigraphics
include $(BUILD_SHARED_LIBRARY)