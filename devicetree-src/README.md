## devicetree building and customization

> **Note:** Device tree sources should be getting from Vitis, but building is done by Device Tree Compiler. 
 
DTC compiler should be fetched and compiled
```sh
git clone https://git.kernel.org/pub/scm/utils/dtc/dtc.git
cd dtc
make
export PATH=`pwd`:$PATH
```

Fetch xilinx device-tree repository where you have Vitis 2022.2 installed and checkout it to installed version of Vitis (2022.1)
```sh
git clone https://github.com/Xilinx/device-tree-xlnx.git
git checkout xilinx_v2022.1
```
### Creating Vitis platform project with for device tree files
* Start Vitis IDE and go `Xilinx - Software Repositories - Local Repositories - New`. Point to repo `device-tree-xlnx` folder (for example `C:\Xilinx\device-tree-xlnx`)
* Create new platform project `Platform project name - Create a new from (XSA) - Browse to you .xsa - Operating system device_tree - Check up Generate boot components - Finish`
* Build the platform project

Required files can be found:
```
platform_project_name/
|
+-- export/
|   |
|   +-- platform_project_name/
|   	|
|   	+-- sw/
|			|
|			+-- platform_project_name/
|				|
|				+-- boot/
|					|
|					+-- fsbl.elf
|					+-- pmufw.elf (for zynqmp)
+-- ps7_cortex9_0/
|	|
|	+-- device_tree_domain/
|		|
|		+-- bsp/
|			|
|			+-- pcw.dtsi
|			+-- pl.dtsi
|			+-- system.dts
|			+-- system-top.dts
|			+-- zynq-7000.dtsi
|
+-- ps7_cortexa53

```

* Copy delivered .dts .dtsi files to a `/devicetree-src` folder
> **Note:** The customization can be done by editing .dts, .dtsi files 
```
devicetree-src/
|
+-- zynq/
|	|	
|	+-- build.sh
|	+-- pcw.dtsi
|	+-- pl.dtsi
|	+-- system.dts
|	+-- system-top.dts
|	+-- zynq-7000.dtsi
|	
|
+-- zynqmp/
	|
	+-- build.sh
	+-- zynq.dtsi
 	+-- zynqmp.sh
```	

* Running `build.sh` script allows to generate `kernel.dts` file for [u-boot](https://github.com/farbius/linux-vitis-zynq/tree/main/u-boot-xlnx-src) and [buildroot project](https://github.com/farbius/linux-vitis-zynq/tree/main/external-tree)
* Copy `fsbl.elf`, `pmufw.elf` (for zynqmp) to `/boot` folder