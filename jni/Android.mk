JNI_PATH := $(call my-dir)

#include $(JNI_PATH)/jpeg-9a/Android.mk
include $(JNI_PATH)/libjpeg-turbo/Android.mk
include $(JNI_PATH)/tmg/riff/Android.mk
include $(JNI_PATH)/tmg/recplayer/Android.mk
include $(JNI_PATH)/tmg/android/apps/recplayer/Android.mk