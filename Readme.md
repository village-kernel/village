# 乡村内核计划：
# Village内核特点:
- ### 1.上层功能代码与底层驱动代码分离，可移植性强
- ### 2.支持模块化，代码模块可分离
- ### 3.支持多线程，多任务

---
# 目录：
- ## vk.application: 应用层代码
- ## vk.bootloader: 加载器代码
- ## vk.hardware: 硬件层代码
- ## vk.kernel: 微内核代码
- ## vk.network: 网络层代码
- ## vk.scripts: 工具脚本
- ## vk.build：编译输出文件夹

---
# 环境搭建：
## ubuntu 安装开发环境:

- ### arm-none-eabi-gcc
		sudo apt install arm-none-eabi-gcc

- ### openocd
		sudo apt install openocd

## macos 安装开发环境：
- ### brew
		/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

- ### arm-none-eabi-gcc
		brew install armmbed/formulae/arm-none-eabi-gcc

- ### i386-elf-gcc
		brew install i386-elf-binutils i386-elf-gcc i386-elf-gdb

- ### qemu
		brew install qemu

- ### openocd
		brew install open-ocd

## windows 安装开发环境：
- ### cywin：
- ### make：
- ### gcc:
- ### arm-none-eabi-gcc:
- ### openocd:

### 以上工具都可以在cywin里面下载。注意：不要使用mingw64，问题太多。

---

# 增加子模块
	git submodule add git@xxxx.git

# 说明
	目前还处于开发阶段，各功能还不完善。
	适配平台不多，目前只适配了cortex-m和i686平台，其他平台待适配。

