# RISC-V介绍

发布版本：1.0

作者邮箱：jason.zhu@rock-chips.com

日期：2019.03

文件密级：公开资料

------

**前言**

**概述**

RISC-V介绍。

**读者对象**

本文档（本指南）主要适用于以下工程师：

技术支持工程师

软件开发工程师

**产品版本**

**修订记录**

| **日期**   | **版本** | **作者**  | **修改说明** |
| ---------- | -------- | --------- | ------------ |
| 2019-03-21 | V1.0     | Jason Zhu | 初始版本     |

------

[TOC]

------

## 1 引用参考

1. 《RISC-V架构与嵌入式开发快速入门》
2. <https://riscv.org/>
3. <https://ring00.github.io/bbl-ucore/#/toolchain-overview?id=risc-v-tools>

## 2 术语

## 3 测试平台

ubuntu 18.10

qemu

## 4 简介

RISC-V(读作“RISC-FIVE”)是基于精简指令集计算(RISC)原理建立的开放指令集架构(ISA)，V表示为第五代RISC(精简指令集计算机),表示此前已经四代RISC处理器原型芯片。每一代RISC处理器都是在同一人带领下完成，那就是加州大学伯克利分校的David A. Patterson教授。与大多数ISA相反，RISC-V ISA可以免费地用于所有希望的设备中，允许任何人设计、制造和销售RISC-V芯片和软件。

目前官方除了以下三个文档，可以依据此三个文档设计开发：

- 《riscv-spec-v2.2.pdf》

- 《riscv-debug-0.13.1.pdf》

- 《riscv-privileged-v1.10.pdf》

### 4.1 Modular ISA

RISC-V ISA是模块化的，它由一个基本指令集和一些扩展指令集组成

Base integer ISAs

- RV32I
- RV64I
- RV128I

Standard extensions

- M: Integer Multiply
- A: Atomic Memory Operations
- F: Single-percison Floating-point
- D: Double-precision Floating-point
- G: IMAFD, General Purpose ISA

举例：RV32IMA表示支持基本整数操作和原子操作的32位RISC-V指令集。

### 4.2 Privileged ISA

RISC-V共有4种不同的特权级，与x86不同的是，RISC-V中特权级对应数字越小，权限越低：

| Level | Encoding | Name             | Abbreviation |
| ----- | -------- | ---------------- | ------------ |
| 0     | 00       | User/Application | U            |
| 1     | 01       | Supervisor       | S            |
| 2     | 10       | Hypervisor       | H            |
| 3     | 11       | Machine          | M            |

一个RISC-V的实现并不要求同时支持这四种特权级，可接受的特权级组合如下：

| Number of levels | Supported Modes | Intended Usage                              |
| ---------------- | --------------- | ------------------------------------------- |
| 1                | M               | Simple embedded systems                     |
| 2                | M, U            | Secure embedded systems                     |
| 3                | M, S, U         | Systems running Unix-like operating systems |
| 4                | M, H, S, U      | Systems running Type-1 hypervisors          |

### 4.3 指令及ABI

```
https://github.com/riscv/riscv-elf-psabi-doc.git
```

## 5 工具链

开源意味着各个可以加入自己的指令集，一些工具链会加入自己的指令集命令，造成前期工具链并不是很通用。

### 5.1  gcc工具链制作

可以直接依据下列地址生成工具链，会比较稳定。

```
https://github.com/riscv/riscv-tools
编译：
git submodule update --init --recursive
export RISCV=/path/to/install/riscv/toolchain
./build.sh
另，注意riscv-qemu需要另外自己编译：
For RV64GC:
./configure --target-list=riscv64-softmmu && make
For RV32GC:
./configure --target-list=riscv32-softmmu && make
```

可以直接使用成熟的gcc，Hifive官网有提供工具链，供下载使用。

```
https://www.sifive.com/boards
```

也可以到syntacore下载：

```
https://github.com/riscv/riscv-toolchain-conventions.git
```

工具链的配置可以参考：

```
https://github.com/riscv/riscv-toolchain-conventions.git
```

### 5.2 CLANG

#### 5.2.1 安装

```
sudo apt-get install clang
```

参考链接：<https://github.com/lowRISC/riscv-llvm>

riscv clang

```
https://github.com/lowrisc/riscv-llvm
```

另附上armclang工具链地址：

```
https://archlinuxarm.org/packages/arm/clang
```

#### 5.2.2 使用

**To-Do**

## 6 仿真器

使用openocd进行仿真调试。

使用openocd连接设备：

```
openocd -f interface.cfg -f target.cfg
telnet localhost 4444
halt
flash write_image erase xxxx.hex
```

参考《openocd+jlink.md》。

## 7 rk-riscv搭建

工程项目：

```
https://github.com/zhuzhizhan/rk-riscv
```

更改Makefile中的CROSS_COMPILE为本机对应的工具链，make。

运行./qemu.sh即可仿真结果。

## 8 scr1仿真

### 8.1 工具链

安装，也可以从syntacore下载现成的工具链。

```
sudo apt-get install autoconf automake libmpc-dev libmpfr-dev libgmp-dev gawk bison
flex texinfo libtool make g++ pkg-config libexpat1-dev zlib1g-dev
git clone https://github.com/riscv/riscv-gnu-toolchain.git
cd riscv-gnu-toolchain
git checkout a71fc539850f8dacf232fc580743b946c376014b
git submodule update --init --recursive
./configure --prefix=<GCC_INSTALL_PATH> --enable-multilib
make
```

环境变量设置：

```
export PATH=$PATH:<GCC_INSTALL_PATH>/bin
```

ubuntu18编译会找不到libmpfr.so.4，需要执行以下命令：

```
sudo ln -s /usr/lib/x86_64-linux-gnu/libmpfr.so.6 /usr/lib/x86_64-linux-gnu/libmpfr.so.4
```

### 8.2 riscv-tests

riscv-tests为ISA测试，执行下列命令：

```
git clone https://github.com/riscv/riscv-tests
cd riscv-tests
git checkout a9433c4daa287fbe101025f2a079261a10149225
export RISCV_TESTS=<RISCV_TESTS_PATH>
```

### 8.3 riscv-compliance

```
git clone https://github.com/riscv/riscv-compliance
cd riscv-compliance
git checkout 9273836251cc53069f9cc48543fa9c1417e98cb7
export RISCV_COMPLIANCE_TESTS=<RISCV_COMPLIANCE_TESTS_PATH>
```

### 8.4 coremark

coremark为软件性能评分软件，非常容易移植，只需执行下列步骤：

```
git clone https://github.com/eembc/coremark.git
把文件core_main.c，core_list_join.c，coremark.h，core_matrix.c，core_state.c，core_util.c移动到tests/benchmarks/coremark/src目录下
```

### 8.5 执行仿真

make run_<SIMULATOR> BUS=<AHB, AXI> ARCH=<I, IM, IMC, IC, EM, EMC, EC> IPIC=<0, 1>

SIMULATOR支持：

- run_modelsim
- run_vcs
- run_ncsim
- run_verilator

前三个需要安装收费软件，最后一个只需执行：

```
sudo apt-get install verilator
```

例：make run_verilator BUS=AHB ARCH=IMC IPIC=0

参考《scr1_um.pdf》

## 9 参考资料

所有RISC-V芯片与软件相关的产品可以从 <https://github.com/riscv/riscv-wiki/wiki> 获取。

