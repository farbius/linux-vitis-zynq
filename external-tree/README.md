## buildroot project customization (output file is image.itb, that combines compiled kernel, devicetree and rootfs)
Buildroot project allows to deliver ROOTFS file system and Linux kernel. For additional linux packages `_defconfig` files can be used. 
The structure of buildroot project:
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
### Steps are

* Clone buildroot latest repository `git clone https://github.com/buildroot/buildroot.git`.
* Configure `buildroot` for zynq 7000 or zynqmp target

#### ZynqMP Ultrascale+

```
mkdir -p /path/to/build/dir/zynqmp
cd /path/to/build/dir/zynqmp
make --directory=/path/to/buildroot/git BR2_EXTERNAL=/path/to/this/git zynqmp_defconfig O=$PWD
```

#### Zynq 7000

```
mkdir -p /path/to/build/dir/zynq7k
cd /path/to/build/dir/zynq7k
make --directory=/path/to/buildroot/git BR2_EXTERNAL=/path/to/this/git zynq7k_defconfig O=$PWD
```
* Build Image

```
make
```
* Copy `image.itb` from `/build` directory to `/boot`

