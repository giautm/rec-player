LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := riff-tmg
LOCAL_CFLAGS := -Werror -std=gnu++11
LOCAL_C_INCLUDES := $(LOCAL_PATH) $(JNI_PATH)
LOCAL_SRC_FILES  := src/riff.cc
include $(BUILD_STATIC_LIBRARY)
