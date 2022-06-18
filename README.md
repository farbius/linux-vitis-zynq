# linux-vitis-buildroot-zynq
The repository describes how to build linux for Zynq 7000 and ZynqMP from sources by using Xilinx Vitis 2022.1 and Buildroot
All information is available on Xilinx Confluence [Xilinx Open Source Linux](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/460653138/Xilinx+Open+Source+Linux).

The dependencies for Ubuntu 18.04 .

```sh
sudo apt-get install -y gcc git make net-tools libncurses5-dev tftpd zlib1g-dev libssl-dev flex bison libselinux1 gnupg wget 
sudo apt-get install diffstat chrpath socat xterm autoconf libtool tar unzip texinfo zlib1g-dev gcc-multilib build-essential 
sudo apt-get install libsdl1.2-dev libglib2.0-dev zlib1g:i386 screen pax gzip gawk
sudo apt-get install swig python3-dev
sudo apt-get install python3-pip
sudo apt-get install gcc make gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi
sudo apt-get install u-boot-tools
pip3 install setuptools-scm==5.0.2
```



## devicetree customization (output file is arty_zynq.dts)
< **Note:** Device tree sources should be getting from Vitis, but building is done by Device Tree Compiler.  
DTC compiler should be fetched and compiled
```sh
git clone https://git.kernel.org/pub/scm/utils/dtc/dtc.git
cd dtc
make
export PATH=`pwd`:$PATH
```

Fetch xilinx device-tree repository and checkout it to installed version of Vitis (2022.1)
```sh
git clone https://github.com/Xilinx/device-tree-xlnx.git
git checkout xilinx_v2022.1
```
Build Vivado 2022.1 project and export to Vitis including bitstream (.xsa file).
Start new platform project in Vitis and point to .xsa file.
.......
Copy all device tree sources to *devicetree-src/zynq* or *devicetree-src/zynqmp* and run *build.sh*


```
devicetree-src/
|
+-- zynq/
|	|	
|	+-- build.sh
|	+-- zynq.dtsi
|	
|
+-- zynqmp/
	|
	+-- build.sh
	+-- zynq.dtsi
 	+-- zynqmp.sh
```	
## u-boot customization (output file is u-boot.elf)
Fetch u-boot sources from Xilinx repository and checkout 2022.1 version
```sh
git clone https://github.com/Xilinx/u-boot-xlnx.git
cd u-boot-xlnx
git checkout xilinx-v2021.2
```
Replace and add files from u-boot-xlnx-src 
< **Note:** The customization can be done by editing defconfig, .dts, .h files 
```
u-boot-xlnx-src/
|
+-- arch/
|	|
| 	+-- arm/
|		|
| 		+-- dts/
|			|
|			+-- arty_zynq.dts
|			+-- xxx.dts
|			+-- Makefile
|				|dtb-$(CONFIG_ARCH_ZYNQ) += \
|				|    arty_zynq.dtb
|				|dtb-$(CONFIG_ARCH_ZYNQMP) += \
|				|    xxx.dtb
|	 			`----
|
+-- configs/
|	|
|	+-- xilinx_zynq_virt_defconfig
|	|		|DEFAULT_DEVICETREE = "arty_zynq"
|	|		|DEFAULT_SYS_FILE   = "arty_zynq"
|	|		`----
|	|
|	+-- xilinx_zynqmp_virt_defconfig
|			|DEFAULT_DEVICETREE = "xxx"
|			|DEFAULT_SYS_FILE   = "xxx"
|	 		`----
|
+-- include/
	|
 	+-- conf/
		|
		+-- arty_zynq.h
		+-- xxx.h
```
Then compile the u-boot sources by using target-related cross-compiler (arm32 or aarch64) 

*Zynq 7000:*
```sh
cd u-boot-xlnx
export CROSS_COMPILE=arm-linux-gnueabihf-
export ARCH=arm
make distclean
make xilinx_zynq_virt_defconfig
make
```

*ZynqMP:*
```sh
cd u-boot-xlnx
export CROSS_COMPILE=aarch64-linux-gnueabihf-
export ARCH=arm
make distclean
make xilinx_zynqmp_virt_defconfig
make
```

## buildroot project customization (output file is image.itb, that combines compiled kernel, devicetree and rootfs)
```
external-tree/
|
+-- board/
|	|	
|	+-- zynq/
|	|	|
|	|	+-- rootfs-overlay/
|	|	+-- image.its
|	|	+-- kernel.config
|	|	+-- kernel.dts
|	|	+-- post-image.sh
|	|
|	+-- zynqmp/
|		|
|		+-- rootfs-overlay/
|		+-- image.its
|		+-- kernel.config
|		+-- kernel.dts
|		+-- post-image.sh
|	
|
+-- configs/
|	|
|	+-- zynq_defconfig
|	+-- zynqmp_defconfig
|	
|
+-- Config.in
+-- external.mk
+-- external.desc
```

## booting and running images on targets via TFTP

Writing BOOT.BIN into flash from u-boot

```sh
tftpb 0x4000000 BOOT.BIN
sf probe 0 0 0
sf erase 0 0x1000000
sf write 0x4000000 0 0x800000
```
