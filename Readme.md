乡村计划：
1.开发一个通用嵌入式开发平台

目的：

1.实现代码模块可分离，减少耦合
2.实现上层功能代码与底层驱动代码分离，增强可移植性

目录：
VK.Application: 用来存放上层代码
VK.Hardware: 用来存放硬件层代码
VK.Kernel: 用来存放微内核代码
VK.Build：用来存放编译文件

ubuntu 安装开发环境:
1.arm-none-eabi-gcc
sudo apt install arm-none-eabi-gcc
2.openocd
sudo apt install openocd

macos 安装开发环境：
0.brew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
1.arm-none-eabi-gcc
brew install armmbed/formulae/arm-none-eabi-gcc
2.openocd
brew install open-ocd

windows 安装开发环境：
0.cywin：
以下工具都可以在cywin里面下载。
注意：不要使用mingw64，问题太多。
1.make
2.gcc
3.arm-none-eabi-gcc
4.openocd

