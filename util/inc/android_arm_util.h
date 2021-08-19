#include <android/log.h>
#ifndef __ANDROID_ARM_UTIL_H__
#define __ANDROID_ARM_UTIL_H__
#ifdef __DEBUG__
#define LOG_ERROR       ANDROID_LOG_ERROR
#define LOG_INFO        ANDROID_LOG_INFO
#define LOG_DEBUG       ANDROID_LOG_DEBUG
#define LOG_VERBOSE     ANDOIRD_LOG_VERBOSE
#define ex_log(LOG_LEVEL, x...) __android_log_print(LOG_LEVEL, "NEON_COL_SWAP", x)
#define FUNC_ENTRANCE_LOG       ex_log(LOG_DEBUG, "%s enters", __func__);
#define FUNC_EXIT_LOG           ex_log(LOG_DEBUG, "%s leaves", __func__);
#else
#define ex_log(LOG_LEVEL, x...) do {} while (0)
#endif

double now_ns(void);
#endif
