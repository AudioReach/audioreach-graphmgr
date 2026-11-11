/*
** Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above
**     copyright notice, this list of conditions and the following
**     disclaimer in the documentation and/or other materials provided
**     with the distribution.
**   * Neither the name of The Linux Foundation nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
** WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
** ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
** BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
** OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
** IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** Changes from Qualcomm Technologies, Inc. are provided under the following license:
** Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
** SPDX-License-Identifier: BSD-3-Clause
**/

#ifndef __UTILS_H__
#include "ar_osal_error.h"

#ifdef AGM_USE_SYSLOG
#include <stdint.h>
#include <syslog.h>

#ifndef ALOGD
#define ALOGD(fmt, arg...) syslog (LOG_DEBUG, fmt, ##arg)
#endif

#ifndef ALOGI
#define ALOGI(fmt, arg...) syslog (LOG_INFO, fmt, ##arg)
#endif

#ifndef ALOGE
#define ALOGE(fmt, arg...) syslog (LOG_ERR, fmt, ##arg)
#endif

#ifndef ALOGV
#define ALOGV(fmt, arg...) syslog (LOG_DEBUG, fmt, ##arg)
#endif

#else
#include <log/log.h>
#endif

#include <stdint.h>

/* Debug tiers, bits as PAL. vendor.audio.agm.loglevel is hexadecimal.
 * DBG is the master switch. HIGH/MID/LOW are independent tier selectors.
 * Only libagm (AGM_LOG_TIERS) filters; other users print all. */
#define AGM_LOG_ERR             (0x1)
#define AGM_LOG_INFO            (0x2)
#define AGM_LOG_DBG             (0x4)
#define AGM_LOG_VERBOSE         (0x8)
#define AGM_LOG_DBG_HIGH        (0x10) /* Main flow, once per operation. */
#define AGM_LOG_DBG_MID         (0x20) /* One-off config and on-demand details. */
#define AGM_LOG_DBG_LOW         (0x40) /* Per-call, per-buffer and dump logs. */
#define AGM_LOG_DBG_SUB_MASK    (AGM_LOG_DBG_HIGH | AGM_LOG_DBG_MID | AGM_LOG_DBG_LOW)

#ifdef AGM_LOG_TIERS
extern uint32_t agm_log_lvl;
#define AGM_LOG_ON(mask) (agm_log_lvl & (mask))
#else
#define AGM_LOG_ON(mask) (1)
#endif

#define AGM_LOG_DBG_TIER_ON(tier) \
    (AGM_LOG_ON(AGM_LOG_DBG) && \
     (!(AGM_LOG_ON(AGM_LOG_DBG_SUB_MASK)) || AGM_LOG_ON(tier)))

#define AGM_LOGE(arg,...) \
    do { if (AGM_LOG_ON(AGM_LOG_ERR)) \
        ALOGE("%s: %d " arg, __func__, __LINE__, ##__VA_ARGS__); } while (0)
#define AGM_LOGD_HIGH(arg,...) \
    do { if (AGM_LOG_DBG_TIER_ON(AGM_LOG_DBG_HIGH)) \
        ALOGD("%s: %d " arg, __func__, __LINE__, ##__VA_ARGS__); } while (0)
/* Legacy AGM_LOGD() sites are HIGH. With no tier selector bits, all debug
 * tiers remain enabled to preserve the old DBG-only behavior. */
#define AGM_LOGD AGM_LOGD_HIGH
#define AGM_LOGD_MID(arg,...) \
    do { if (AGM_LOG_DBG_TIER_ON(AGM_LOG_DBG_MID)) \
        ALOGD("%s: %d " arg, __func__, __LINE__, ##__VA_ARGS__); } while (0)
#define AGM_LOGD_LOW(arg,...) \
    do { if (AGM_LOG_DBG_TIER_ON(AGM_LOG_DBG_LOW)) \
        ALOGD("%s: %d " arg, __func__, __LINE__, ##__VA_ARGS__); } while (0)
#define AGM_LOGI(arg,...) \
    do { if (AGM_LOG_ON(AGM_LOG_INFO)) \
        ALOGI("%s: %d " arg, __func__, __LINE__, ##__VA_ARGS__); } while (0)
#define AGM_LOGV(arg,...) \
    do { if (AGM_LOG_ON(AGM_LOG_VERBOSE)) \
        ALOGV("%s: %d " arg, __func__, __LINE__, ##__VA_ARGS__); } while (0)

/*convert osal error codes to lnx error codes*/
int ar_err_get_lnx_err_code(uint32_t error);
/*helper to print errors in string form*/
char *ar_err_get_err_str(uint32_t error);

#endif /*__UTILS_H*/
