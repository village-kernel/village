# 乡村内核计划：
# Village内核特点:
- ### 1.支持模块化，代码模块可分离
- ### 2.上层功能代码与底层驱动代码分离，可移植性强

---
# 目录：
- ## vk.application: 应用层代码
- ## vk.bootloader: 加载器代码
- ## vk.hardware: 硬件层代码
- ## vk.kernel: 微内核代码
- ## vk.scripts: 工具脚本
- ## vk.build：编译文件

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