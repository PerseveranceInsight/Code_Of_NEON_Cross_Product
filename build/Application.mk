APP_PROJECT_PATH := $(call my-dir)
APP_ABI := arm64-v8a
APP_OPTION := debug
APP_DEBUG := true

ifeq ($(EN_DEBUG_SYM),true)
APP_STRIP_MODE := none
endif
