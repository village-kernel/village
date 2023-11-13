
# Village内核特点:
- ### 1.上层功能代码与底层驱动代码分离，可移植。
- ### 2.支持模块化，代码模块可分离
- ### 3.支持多线程，多任务

# Village内核目标：
- ### 1.可在低端的嵌入式设备运行，也可以在高端的PC运行
- ### 2.让嵌入式开发者花费更少精力在底层，有更多精力搞好应用
- ### 3.适配更多通用设备，让开发者更快实现业务
- ### 4.不为项目更换MCU，需要重新适配底层而烦恼

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
# 参与village-kernel开发：

- ## 1.系统要求
		mac os / linux / windows

- ## 2.搭建开发环境, 以mac os为例
	## 安装vscode, git
		安装简单，跳过

	### 安装brew
		/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

	### 安装交叉编译工具
		brew install i686-elf-binutils i686-elf-gcc i386-elf-gdb

	### 安装qemu模拟器
		brew install qemu

- ## 3.克隆village-kernel项目
		git clone git@github.com:village-kernel/village-kernel.git
		cd village-kernel
		git submodule update --init --recursive

- ## 4.使用vscode打开village-kernel项目
		把项目目录village-kernel拉到vscode界面
		
		接着打开vscode终端，拷贝配置文件
		cp vk.scripts/configs/i686.config .config
		
		修改配置
		make menuconfig
		配置交叉编译器和gdb
		
		编译项目
		make

- ## 5.创建rootfs文件系统镜像
		切换到vscode终端，拷贝文件系统镜像
		cp vk.scripts/rootfs.img rootfs.img
		在Finder中打开rootfs.img
		make rootfs

- ## 6.运行与调试代码
		切换到vscode debug界面
		选择QEMU Debug x86_64 kernel

---

# 下载源码 
- ### 下拉项目
		git clone git@github.com:village-kernel/village-kernel.git
- ### 下拉子模块
		git submodule update --init --recursive
- ### 增加子模块（需要增加子模块时使用）
		git submodule add git@xxxx.git

# 说明
- 目前还处于开发阶段，各功能还不完善，代码还有点垃圾。
- 驱动模块需要进行修改，目前注册驱动还不理想。
- GUI图形界面目前还没编写，只实现了简单的显示功能。
- 专用Bootloader目前还没编写。
- 网络功能还没时间开发，目前只有一人，搞不过来。
- FAT文件系统还在编写完善，目前只能实现读取功能，其他文件系统待开发。
- 适配平台不多，目前只适配了cortex-m和i686平台，其他平台待适配。
- 硬件层代码都存放在vk.hardware子模块中。
- 初步实现了任务管理，内存分配，文件系统，动态加载，系统调度，中断管理，工作队列，
  线程同步（互斥锁，自旋锁，信号量）。

# 展望未来
- 短时间内单靠一个人，搞不定太多，进度实在太慢。
- 编写适配平台底层代码，重写C库，重写文件系统，太耗时间。
- 寻找更多志同道合的码友，一起参与项目开发，人多力量大。
- 目前还很简陋，但星星之火，也可以燎原，一起把火烧起来。
