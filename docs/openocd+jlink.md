# OpenOCD + Jlink

发布版本：1.0

作者邮箱：jason.zhu@rock-chips.com

日期：2019.01

文件密级：内部资料

------

**前言**

**概述**

**读者对象**

本文档（本指南）主要适用于以下工程师：

技术支持工程师

软件开发工程师

**产品版本**

**修订记录**

| **日期**   | **版本** | **作者**  | **修改说明** |
| ---------- | -------- | --------- | ------------ |
| 2018-03-12 | V1.0     | Jason Zhu | 初始版本     |

------

[TOC]

------

## 1 引用参考

<https://blog.csdn.net/qingwufeiyang12346/article/details/45954595>

<https://blog.csdn.net/qingwufeiyang12346/article/details/45954859>

## 2 术语

OpenOCD: Open On-Chip Debugger

Jlink: JTAG仿真器

## 3 简介

OpenOCD: 开放式片上调试器旨在为嵌入式目标器件提供调试，系统内编程和边界扫描测试。

Jlink: 硬件调试器。

本文将介绍如何通过OpenOCD + Jlink进行片上仿真调试。

## 4 驱动安装

1. 安装Jlink驱动
2. 登陆<http://www.freddiechopin.info/en/download/category/4-openocd>下载OpenOCD
3. 登陆<http://zadig.akeo.ie/>下载zadig
4. 插入Jlink仿真器（如果是第一次插入Jlink仿真器，系统会要求安装驱动程序，我们可以点击取消，不必理会)，运行zadig软件
5. 选择Options-List All Devices
6. 在其下拉列表中选择J-Link
7. 选择WinUSB驱动程序，点击Reinstall Driver按钮或Replace Driver按钮，这样便完成了驱动程序的替换
8. 进入下载的OpenOCD软件

## 5 OpenOCD调试

1. 连接设备

```
openocd -f interface/jlink.cfg -f target/stm32f4x.cfg
telnet localhost 4444
```

2. 下载固件

```
halt
flash write_image erase /home/liuyang/Projects/Nuttx/nuttx/nuttx.hex
```