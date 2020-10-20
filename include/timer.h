#ifndef __TIMER_H__
#define __TIMER_H__

#include "psp_defines.h"
#include "psp_types.h"

/* Specified RAM address for timer duration setup (SweRVolf special implementation) */
#if (0 != D_TIMER_DURATION_SETUP_ADDRESS)
    #define D_BSP_TIMER_DURATION_SETUP_REGISTER   D_TIMER_DURATION_SETUP_ADDRESS
#else
    #error "Timer setup address is not defined"
#endif

/* Specified RAM address for timer activation (SweRVolf special implementation) */
#if (0 != D_TIMER_ACTIVATION_ADDRESS)
    #define D_BSP_TIMER_ACTIVATION_REGISTER   D_TIMER_ACTIVATION_ADDRESS
#else
    #error "Timer activation address is not defined"
#endif

#define D_TIMER_START   1
#define D_TIMER_STOP    0

/* SweRVolf EH1 rate is 50Mhz, EL2 = 25Mhz. Convert duration (in MSec) to number of timer cycles */
#define M_MSEC_DURATION_TO_CYCLES(duration)   (duration * (D_CLOCK_RATE / D_PSP_MSEC))

typedef enum pspTimers
{
   E_MACHINE_TIMER     = 0,
   E_INTERNAL_TIMER0   = 1,
   E_INTERNAL_TIMER1   = 2,
   E_LAST_TIMER
} ePspTimers_t;

void timer_machine_setup(u32_t period_cycles);
void timer_counter_setup_and_run(u32_t ui_timer, u32_t period_cycles);
u64_t timer_counter_get(u32_t ui_timer);
u64_t timer_compare_counter_get(u32_t ui_timer);
void timer_enable_count_in_sleep_mode(u32_t ui_timer);
void timer_disable_count_in_sleep_mode(u32_t ui_timer);
void timer_enable_count_in_stall_mode(u32_t ui_timer);
void timer_disable_count_in_stall_mode(u32_t ui_timer);
void timer_start(void);
void timer_stop(void);

#endif
