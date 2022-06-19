## u-boot building and customization
*  Fetch u-boot sources from Xilinx repository on Ubuntu and checkout 2022.1 version
```sh
git clone https://github.com/Xilinx/u-boot-xlnx.git
cd u-boot-xlnx
git checkout xilinx-v2021.2
```
* Replace and add files from the repo (/u-boot-xlnx-src). In `/arch/arm/dts` folder compiled and renamed [kernel.dts](https://github.com/farbius/linux-vitis-zynq/tree/main/devicetree-src) file are used.
> **Note:** The customization can be done by editing `xilinx_zynq_virt_defconfig`, `xilinx_zynqmp_virt_defconfig`, `arty_zynq.h` or `trenz_zynqmp.h` files 
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
|			+-- trenz_zynqmp.dts
|			+-- Makefile
|				|dtb-$(CONFIG_ARCH_ZYNQ) += \
|				|    arty_zynq.dtb
|				|dtb-$(CONFIG_ARCH_ZYNQMP) += \
|				|    trenz_zynqmp.dtb
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
|			|DEFAULT_DEVICETREE = "trenz_zynqmp"
|			|DEFAULT_SYS_FILE   = "trenz_zynqmp"
|	 		`----
|
+-- include/
	|
 	+-- conf/
		|
		+-- arty_zynq.h
		+-- trenz_zynqmp.h
```

* Compile the u-boot sources by using target-related cross-compiler (arm32 or aarch64) 

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

* Copy `u-boot.elf` to `/boot` folder