// SPDX-License-Identifier: Apache-2.0
// Copyright 2019 Western Digital Corporation or its affiliates.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __MEM_MAP_H
#define __MEM_MAP_H

// Memory map
#define EXT_SRAM_BASE_ADDRES            0x00000000
#define ICCM_BASE_ADDRESS		0xEE000000
#define DCCM_BASE_ADDRESS		0xF0080000
#define UART_BASE_ADDRESS		0x44A00000

// special for eh1
#define D_MTIME_ADDRESS                         0x80001020
#define D_MTIMECMP_ADDRESS                      0x80001028
#define D_CLOCK_RATE                            50000000
#define D_PIC_BASE_ADDRESS                      0xf00c0000
#define D_PIC_NUM_OF_EXT_INTERRUPTS             256
#define D_EXT_INTERRUPT_FIRST_SOURCE_USED       0
#define D_EXT_INTERRUPT_LAST_SOURCE_USED        255
#define D_EXT_INTS_GENERATION_REG_ADDRESS       0x8000100B
#define D_TIMER_DURATION_SETUP_ADDRESS          0x80001030
#define D_TIMER_ACTIVATION_ADDRESS              0x80001034
#define D_NMI_VEC_ADDRESSS                      0x8000100C
#define D_ISR_STACK_SIZE                        400

#endif //__MEM_MAP_H
