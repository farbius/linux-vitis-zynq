# linux-vitis-buildroot-zynq
The repository describes how to build linux (system software) for Zynq 7000 and Zynqmp from sources by using Xilinx Vitis 2022.1 and Buildroot
All information is available on Xilinx Confluence [Xilinx Open Source Linux](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/460653138/Xilinx+Open+Source+Linux).
The system software was build by using Windows 10 with Vitis 2022.2 installed and Ubuntu 18.04 running on VMware Workstation virtual machine
The dependencies for Ubuntu 18.04

```sh
sudo apt-get install -y gcc git make net-tools libncurses5-dev tftpd zlib1g-dev libssl-dev flex bison libselinux1 gnupg wget 
sudo apt-get install diffstat chrpath socat xterm autoconf libtool tar unzip texinfo zlib1g-dev gcc-multilib build-essential 
sudo apt-get install libsdl1.2-dev libglib2.0-dev zlib1g:i386 screen pax gzip gawk
sudo apt-get install python-dev
sudo apt-get install swig python3-dev
sudo apt-get install python3-pip
sudo apt-get install gcc make gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu
sudo apt-get install u-boot-tools
pip3 install setuptools-scm==5.0.2
```

Repo structure

```
+-- boot/ # used for keeping compiled images
|
+-- devicetree-src/ # for device tree sources
|	|
|	+-- zynq/
|	+-- zynqmp/
|
+-- external-tree/ # buildroot project
|	|
|	+-- boards/
|	+-- configs/
|
+-- u-boot-xlnx-src/ # for u-boot sources
	|
	+-- arch/
	+-- configs/
	+-- include/
```


### Deliviring system software step-by-step

1. Building a project in Vivado 2022.2 and exporting .xsa file to Vitis 2022.2 envoriment
1. [Customizing and building devicetree, FSBL, PMU (for zynqmp)](https://github.com/farbius/linux-vitis-zynq/tree/main/devicetree-src)
1. [Customizing and building u-boot](https://github.com/farbius/linux-vitis-zynq/tree/main/u-boot-xlnx-src)
1. [Customizing and building a buildroot project](https://github.com/farbius/linux-vitis-zynq/tree/main/external-tree)
1. Preparing and loading Image to the target

### Build ARM trusted firmware for zynqmp

> **Note:** Please see [Xilinx Wiki](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842305/Build+ARM+Trusted+Firmware+ATF) about building arm-trusted-firmware  


load and extract an archive with x86_64 Linux hosted cross compiler AArch64 ELF bare-metal target [aarch64-none-elf](https://developer.arm.com/downloads/-/gnu-a)

```
ls -l
total 28
-rw-r--r-- 1 aleksei aleksei 3797 Jul 13  2021 10.3-2021.07-x86_64-aarch64-none-elf-manifest.txt
drwxr-xr-x 5 aleksei aleksei 4096 Jul  1  2021 aarch64-none-elf
drwxr-xr-x 2 aleksei aleksei 4096 Jul  1  2021 bin
drwxr-xr-x 3 aleksei aleksei 4096 Jul  1  2021 include
drwxr-xr-x 4 aleksei aleksei 4096 Jul  1  2021 lib
drwxr-xr-x 3 aleksei aleksei 4096 Jul  1  2021 libexec
drwxr-xr-x 7 aleksei aleksei 4096 Jul  1  2021 share

cd bin/
export PATH=`pwd`:$PATH
source ~/.bashrc
cd ../..
git clone https://github.com/Xilinx/arm-trusted-firmware.git
cd arm-trusted-firmware
make CROSS_COMPILE=aarch64-none-elf- PLAT=zynqmp RESET_TO_BL31=1
```

copy `/arm-trusted-firmware/build/zynqmp/release/bl31/bl31.elf` to `boot/`


### Preparing and loading Image to the target
Linux Image for zynq / zynqmp is presented by `BOOT.BIN` (`fsbl.elf`, `pmufw.elf` (for zynqmp), `bl31.elf` (for zynqmp), `u-boot.elf`, `system.bit`) 
and `image.itb` (`rootfs.cpio`, `devicetree.dtb`, `Linux_kernel`) 

For generating `BOOT.BIN` Vitis 2022.1 is used (In created Platform Project `Xilinx - Create Boot Image - Zynq and Zynq Ultrascle - Browse output.bif file`) 

`output.bif` is situated in `boot/` folder

Created BOOT.BIN file should be writing into flash memory


### booting and running `image.itb` on targets via TFTP

For TFTP server [Windows TFTP Utility](https://sourceforge.net/projects/tftputil/) is used.

IP address 192.168.0.21 for tftp server are pointed in u-boot settings (.h configuration file) and should be set on the local machine for IP4V
```
#define CONFIG_SERVERIP 	192.168.0.21
#define CONFIG_GATEWAYIP	192.168.0.1
#define CONFIG_NETMASK		255.255.255.0
```

Commands for loading and running image.itb in u-boot console:

*Zynq 7000:*
```
tftpb 0x4000000 image-arty.itb
bootm 0x4000000
```

*Zynqmp:*
```
tftpb 0x60000000 image-trenz.itb
bootm 0x60000000
```

Last command will load and run Linux on the target

#### Writing BOOT.BIN into flash from u-boot (BOOT.BIN is less than 8 Mb)


*Zynq 7000:*
```sh
tftpb 0x4000000 BOOT.BIN
sf probe 0 0 0
sf erase 0 0x1000000
sf write 0x4000000 0 0x800000
```

*Zynqmp:*
```sh
tftpb 0x60000000 BOOT.BIN
sf probe 0 0 0
sf erase 0 0x800000
sf write 0x60000000 0 0x800000
```
