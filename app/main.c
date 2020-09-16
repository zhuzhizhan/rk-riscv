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


#include "printf.h"
#include "encoding.h"

int main()
{
	int a = 10;
	int b = 3;
	printf("a + b = %d\n", a + b);
	printf("a - b = %d\n", a - b);
	printf("a * b = %d\n", a * b);
	printf("a / b = %d\n", a / b);
	printf("a \% b = %d\n", a % b);
	printf("Hello world from SweRV on FPGA!\n");
        printf("read_csr() is %x\n", read_csr(0xf11));
        printf("read_csr() is %x\n", read_csr(0xf12));
        printf("read_csr() is %x\n", read_csr(0xf13));
        printf("read_csr() is %x\n", read_csr(0xf14));
        printf("read_csr() is %x\n", read_csr(0xb00));
        printf("read_csr() is %x\n", read_csr(0xb02));
	return 0;
}
