/***************************************************************************//**
 * @file
 * @brief app_process.c
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "em_burtc.h"
#include "em_gpio.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "app_log.h"
#include "em4_mode.h"
#include "app_process.h"
#include "app_gpio_config.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

static void disable_HF_clocks(void);
static void init_BURTC(void);
static void set_burtc_clk(void);
static void init_EM4(void);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void BURTC_IRQHandler(void)
{
  // Clear interrupt source
  BURTC_IntClear(BURTC_IEN_COMP);

  //Go to sleep in EM4
  app_trigger_em4_sleep();
}

static void disable_HF_clocks(void)
{
  app_log_info("app: Disabeling HF clocks");
  // Disable high frequency peripherals
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
  USART0->EN_CLR = 0x1;
  USART1->EN_CLR = 0x1;
  USART2->EN_CLR = 0x1;
  TIMER0->EN_CLR = 0x1;
  TIMER1->EN_CLR = 0x1;
  TIMER2->EN_CLR = 0x1;
  TIMER3->EN_CLR = 0x1;
#if defined(ACMP0)
  ACMP0->EN_CLR = 0x1;
#endif // (ACMP0)
#if defined(ACMP1)
  ACMP1->EN_CLR = 0x1;
#endif // (ACMP1)
#if defined(IADC0)
  IADC0->EN_CLR = 0x1;
#endif // (IADC0)
#if defined(I2C0)
  I2C0->EN_CLR = 0x1;
#endif // (I2C0)
#if defined(I2C1)
  I2C1->EN_CLR = 0x1;
#endif // (I2C1)
  GPCRC->EN_CLR = 0x1;
#else
  CMU->CLKEN0_SET = CMU_CLKEN0_HFRCO0;
#endif
  CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_FSRCO);
#if (_SILICON_LABS_32B_SERIES_2_CONFIG <= 2)
  // Check that HFRCODPLL and HFXO are not requested
  while (((HFRCO0->STATUS & _HFRCO_STATUS_ENS_MASK) != 0U)
         || ((HFXO0->STATUS & _HFXO_STATUS_ENS_MASK) != 0U)) {
  }
#endif
#if (_SILICON_LABS_32B_SERIES_2_CONFIG > 1)
#if defined(USART_PRESENT)
  CMU_ClockEnable(cmuClock_USART0, false);
#endif
  CMU_ClockEnable(cmuClock_PRS, false);
  CMU_ClockEnable(cmuClock_GPIO, false);
  CMU_ClockEnable(cmuClock_HFXO, false);
  CMU_ClockEnable(cmuClock_DPLL0, false);
  CMU_ClockEnable(cmuClock_HFRCO0, false);
  CMU_ClockEnable(cmuClock_MSC, false);
  CMU_ClockEnable(cmuClock_DCDC, false);
#endif
}

static void init_BURTC(void)
{
  BURTC_Init_TypeDef burtcInit = BURTC_INIT_DEFAULT;
  burtcInit.compare0Top = true;
  burtcInit.em4comp = true;

  // Initialize BURTC. This also starts BURTC automatically.
  BURTC_Init(&burtcInit);

  BURTC_Stop(); // Stop the counter, we will start it when we need it
  BURTC_SyncWait(); // Wait for the stop to synchronize
  BURTC_CompareSet(0, BURTC_COUNT_BETWEEN_WAKEUP);

  // Enable compare interrupt flag
  BURTC_IntEnable(BURTC_IF_COMP);
  // Enable Interrupt from BURTC
  NVIC_EnableIRQ(BURTC_IRQn);

  // Enable BURTC
  BURTC_Enable(true);
}

static void set_burtc_clk(void)
{
  // Select reference clock/oscillator for the desired clock branch (BURTC Clk).
  // Reference selected for clocking: ULFRCO
  CMU_ClockSelectSet(cmuClock_EM4GRPACLK, cmuSelect_ULFRCO);
  // Enable BURTC Clk
  CMU_ClockEnable(cmuClock_BURTC, true);
}

void reset_burtc_timer(void)
{
  // Reset and stop BURTC counter until advertising timeout.
  BURTC_CounterReset();
  BURTC_SyncWait(); // Wait for the reset to synchronize
}

void start_burtc_timeout(void)
{
  BURTC_CounterReset();
  BURTC_Start();
  BURTC_SyncWait(); // Wait for the start to synchronize
}

void init_GPIO_EM4(void)
{
  // Configure Button PB1 as input and EM4 wake-on pin source
  GPIO_PinModeSet(SL_SIMPLE_BUTTON_EM4WU_PORT, SL_SIMPLE_BUTTON_EM4WU_PIN, gpioModeInput, 1);
  // Enable EM4 wake-up from GPIO pin (BTN1)
  GPIO_EM4EnablePinWakeup(GPIO_IEN_EM4WUIEN4, 0);
#if defined(SL_RADIO_EXTERNAL)
  // Configure SPIDRV CS pin in pull mode so it stays high when going to EM4 (this keeps the Semtech chip in sleep mode)
  GPIO_PinModeSet(SL_SX_CS_PIN, SL_SX_CS_PORT, gpioModeInputPull, 1);

  GPIO_PinModeSet(SL_ANTSW_PORT, SL_ANTSW_PIN, gpioModeDisabled, 0);
#endif
}

static void init_EM4(void)
{
  EMU_EM4Init_TypeDef em4Init = EMU_EM4INIT_DEFAULT;
#if defined(SL_RADIO_EXTERNAL)
  em4Init.pinRetentionMode = EMU_EM4CTRL_EM4IORETMODE_EM4EXIT;
#endif
  EMU_EM4Init(&em4Init);
}

void init_peripheral_for_EM4(void)
{
  //Select ULFRCO as the BURTC clock source.
  set_burtc_clk();
  //Initialize BURTC.
  init_BURTC();
}

void em_EM4_ULfrcoBURTC(void)
{
  //Enable GPIO for EM4 wake-up
  init_GPIO_EM4();

  app_log_info("app: Going to EM4");

  // Make sure clocks are disabled.
  disable_HF_clocks();

  init_EM4();

  // Reset BURTC timer before going to sleep to ensure we start at 0.
  BURTC_CounterReset();
  BURTC_SyncWait();

  // Enter EM4.
  EMU_EnterEM4();
}
