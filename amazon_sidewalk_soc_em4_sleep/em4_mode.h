/***************************************************************************//**
 * @file
 * @brief app_process.h
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//#define SL_SIMPLE_BUTTON_EM4WU_MODE       SL_SIMPLE_BUTTON_MODE_INTERRUPT
#define SL_SIMPLE_BUTTON_EM4WU_PORT       gpioPortB
#define SL_SIMPLE_BUTTON_EM4WU_PIN        3
#define ULFRCO_FREQUENCY                  1000
#define WAKEUP_INTERVAL_MS                30000 // 30 seconds
#define BURTC_COUNT_BETWEEN_WAKEUP        (((ULFRCO_FREQUENCY * WAKEUP_INTERVAL_MS) / 1000) -1)

void em_EM4_ULfrcoBURTC(void);
void init_peripheral_for_EM4(void);
void init_GPIO_EM4(void);
void BURTC_IRQHandler(void);
void reset_burtc_timer(void);
void start_burtc_timeout(void);

#ifdef __cplusplus
}
#endif

