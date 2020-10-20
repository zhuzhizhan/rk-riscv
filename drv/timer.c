#include "mem_map.h"
#include "psp_csrs_eh1.h"
#include "psp_defines.h"
#include "psp_macros.h"
#include "timer.h"

/**
* @brief Setup the countup of Machine Timer
*
* @parameter - period_cycles - defines the timer's period in cycles
*
***************************************************************************************************/
void timer_machine_setup(u32_t period_cycles)
{
#if (0 == D_MTIME_ADDRESS) || (0 == D_MTIMECMP_ADDRESS)
        #error "D_MTIME_ADDRESS or D_MTIMECMP_ADDRESS is not defined"
#endif
        volatile u64_t *p_mtime    = (u64_t*)D_MTIME_ADDRESS;
        volatile u64_t *p_mtimecmp = (u64_t*)D_MTIMECMP_ADDRESS;
        u64_t ud_now, ud_then;

        /* Set the mtime and mtimecmp (memory-mapped registers) per privileged spec */
        ud_now = *p_mtime;
        ud_then = 0x0fffffffffffffff;
        *p_mtimecmp = ud_then;
}

/**
* @brief Setup and activate Timer
*
* @parameter - timer            - indicates which timer to setup and run
* @parameter - period_cycles - defines the timer's period in cycles
*
***************************************************************************************************/
void timer_counter_setup_and_run(u32_t ui_timer, u32_t period_cycles)
{
        u32_t ui_now, ui_then;

        M_PSP_ASSERT((E_MACHINE_TIMER == ui_timer) || (E_INTERNAL_TIMER0 == ui_timer) || (E_INTERNAL_TIMER1 == ui_timer));

        switch (ui_timer) {
        case E_MACHINE_TIMER:
                timer_machine_setup(period_cycles);
                break;
        case E_INTERNAL_TIMER0:
                /* Read Timer0 counter */
                ui_now = M_PSP_READ_CSR(D_PSP_MITCNT0_NUM);
                ui_then = ui_now + period_cycles;
                /* Set Timer0 bound */
                M_PSP_WRITE_CSR(D_PSP_MITBND0_NUM, ui_then);
                /* Enable Timer0 counting */
                M_PSP_SET_CSR(D_PSP_MITCTL0_NUM, D_PSP_MITCTL_EN_MASK);
                break;
        case E_INTERNAL_TIMER1:
                /* Read Timer1 counter */
                ui_now = M_PSP_READ_CSR(D_PSP_MITCNT1_NUM);
                ui_then = ui_now + period_cycles;
                /* Set Timer1 bound */
                M_PSP_WRITE_CSR(D_PSP_MITBND1_NUM, ui_then);
                /* Enable Timer1 counting */
                M_PSP_SET_CSR(D_PSP_MITCTL1_NUM, D_PSP_MITCTL_EN_MASK);
                break;
        default:
                break;
        }
}

/**
* @brief Get Timer counter value
*
* @parameter - timer - indicates which timer to setup and run
*
* @return u64_t      - Timer counter value
*
***************************************************************************************************/
u64_t timer_counter_get(u32_t ui_timer)
{
        u64_t ud_counter = 0;

        M_PSP_ASSERT((E_MACHINE_TIMER == ui_timer) || (E_INTERNAL_TIMER0 == ui_timer) || (E_INTERNAL_TIMER1 == ui_timer));

        switch (ui_timer) {
        case E_MACHINE_TIMER:
                ud_counter = *(u64_t*)D_MTIME_ADDRESS;
                break;
        case E_INTERNAL_TIMER0:
                ud_counter = (u64_t)M_PSP_READ_CSR(D_PSP_MITCNT0_NUM);
                break;
        case E_INTERNAL_TIMER1:
                ud_counter = (u64_t)M_PSP_READ_CSR(D_PSP_MITCNT1_NUM);
                break;
        default:
                break;
        }

        return (ud_counter);
}

/**
* @brief Get Time compare counter value
*
* @parameter - timer - indicates which timer to setup and run
*
* @return u64_t      – Time compare counter value
*
***************************************************************************************************/
u64_t timer_compare_counter_get(u32_t ui_timer)
{
        u64_t ud_counter_compare = 0;

        // M_PSP_ASSERT((E_MACHINE_TIMER == ui_timer) || (E_INTERNAL_TIMER0 == ui_timer) || (E_INTERNAL_TIMER1 == ui_timer));

        switch (ui_timer) {
        case E_MACHINE_TIMER:
                ud_counter_compare = *(u64_t*)D_MTIMECMP_ADDRESS;
                break;
        case E_INTERNAL_TIMER0:
                ud_counter_compare = (u64_t)M_PSP_READ_CSR(D_PSP_MITBND0_NUM);
                break;
        case E_INTERNAL_TIMER1:
                ud_counter_compare = (u64_t)M_PSP_READ_CSR(D_PSP_MITBND1_NUM);
                break;
        default:
                break;
        }

        return (ud_counter_compare);
}

/**
* @brief Enable timer counting when core in sleep mode
*
* @parameter - ui_timer  - indicates which timer to setup
*
***************************************************************************************************/
void timer_enable_count_in_sleep_mode(u32_t ui_timer)
{
        M_PSP_ASSERT((E_INTERNAL_TIMER0 == ui_timer) || (E_INTERNAL_TIMER1 == ui_timer));

        switch (ui_timer) {
        case E_INTERNAL_TIMER0:
                M_PSP_SET_CSR(D_PSP_MITCTL0_NUM,D_PSP_MITCTL_HALT_EN_MASK);
                break;
        case E_INTERNAL_TIMER1:
                M_PSP_SET_CSR(D_PSP_MITCTL1_NUM,D_PSP_MITCTL_HALT_EN_MASK);
                break;
        default:
                break;
        }
}

/**
* @brief Disable timer counting when core in sleep mode
*
* @parameter - ui_timer  - indicates which timer to setup
*
***************************************************************************************************/
void timer_disable_count_in_sleep_mode(u32_t ui_timer)
{
        M_PSP_ASSERT((E_INTERNAL_TIMER0 == ui_timer) || (E_INTERNAL_TIMER1 == ui_timer));

        switch (ui_timer) {
        case E_INTERNAL_TIMER0:
                M_PSP_CLEAR_CSR(D_PSP_MITCTL0_NUM,D_PSP_MITCTL_HALT_EN_MASK);
                break;
        case E_INTERNAL_TIMER1:
                M_PSP_CLEAR_CSR(D_PSP_MITCTL1_NUM,D_PSP_MITCTL_HALT_EN_MASK);
                break;
        default:
                break;
        }
}

/**
* @brief Enable timer counting when core in in stall
*
* @parameter - ui_timer  - indicates which timer to setup
*
***************************************************************************************************/
void timer_enable_count_in_stall_mode(u32_t ui_timer)
{
        M_PSP_ASSERT((E_INTERNAL_TIMER0 == ui_timer) || (E_INTERNAL_TIMER1 == ui_timer));

        switch (ui_timer) {
        case E_INTERNAL_TIMER0:
                M_PSP_SET_CSR(D_PSP_MITCTL0_NUM,D_PSP_MITCTL_PAUSE_EN_MASK);
                break;
        case E_INTERNAL_TIMER1:
                M_PSP_SET_CSR(D_PSP_MITCTL1_NUM,D_PSP_MITCTL_PAUSE_EN_MASK);
                break;
        default:
                break;
        }
}

/**
* @brief Disable timer counting when core in in stall
*
* @parameter - ui_timer  - indicates which timer to setup
*
***************************************************************************************************/
void timer_disable_count_in_stall_mode(u32_t ui_timer)
{
        M_PSP_ASSERT((E_INTERNAL_TIMER0 == ui_timer) || (E_INTERNAL_TIMER1 == ui_timer));

        switch (ui_timer) {
        case E_INTERNAL_TIMER0:
                M_PSP_CLEAR_CSR(D_PSP_MITCTL0_NUM,D_PSP_MITCTL_PAUSE_EN_MASK);
                break;
        case E_INTERNAL_TIMER1:
                M_PSP_CLEAR_CSR(D_PSP_MITCTL1_NUM,D_PSP_MITCTL_PAUSE_EN_MASK);
                break;
        default:
                break;
        }
}

void timer_start(void)
{
        M_PSP_WRITE_REGISTER_32(D_BSP_TIMER_ACTIVATION_REGISTER, D_TIMER_START);
}

void timer_stop(void)
{
        M_PSP_WRITE_REGISTER_32(D_BSP_TIMER_ACTIVATION_REGISTER, D_TIMER_STOP);
}
