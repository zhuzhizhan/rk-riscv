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

#include "encoding.h"
#include "interrupt.h"
#include "printf.h"
#include "timer.h"
#include "coremark.h"

extern MAIN_RETURN_TYPE
core_main(void);

void board_info(void)
{
	int a = 10;
	int b = 3;

	printf("Hello world from SweRV on FPGA!\n");
	printf("a + b = %d\n", a + b);
	printf("a - b = %d\n", a - b);
	printf("a * b = %d\n", a * b);
	printf("a / b = %d\n", a / b);
	printf("a %% b = %d\n", a % b);
        printf("Vendor ID is %x\n", read_csr(0xf11));
        printf("Architecture ID is %x\n", read_csr(0xf12));
        printf("Implementation ID is %x\n", read_csr(0xf13));
        printf("Hardware thread ID is %x\n", read_csr(0xf14));
}

int main()
{
	board_info();

	core_main();

	return 0;
}
