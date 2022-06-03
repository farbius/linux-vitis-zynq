# Buildroot project template

## Environment

### Dependencies

Required host dependencies can be installed via following command:

```
sudo apt install u-boot-tools
```

### Configure

Example of external.desc

```
name: MYDIR
desc: Buildroot external tree for zynq(7k)mp boards
```

Example of external.mk if there is any package

```
include $(sort $(wildcard $(BR2_EXTERNAL_MYDIR_PATH)/package/*/*.mk))
```

Example of Config.in if there is any package

```
source "$BR2_EXTERNAL_MYDIR_PATH/package/ads5402/Config.in"
```

Following will configure `buildroot` for zynqmp target:

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

## Build

### Image

This builds complete target image:

```
make
```

### Package

It is possible to build a single package (convenient for building kernel modules without image):

```
make <package>
```

Available packages are located [here](https://github.com/arconcepts/arc-microwave-linux/tree/master/package).

## Working with packages

Refer to [Buildroot documentation](https://buildroot.org/downloads/manual/manual.html):
- 8.3. Understanding how to rebuild packages
- 8.13.5. Package-specific `make` targets

### Rebuild

To rebuild a package after local source code changes:

```
make <package>-rebuild
```

Example:

```
# rebuild lmx package, reassemble image binary
make lmx-rebuild
make
```

### Rebuild from scratch

To rebuild a single package from scratch:

```
make <package>-dirclean
make <package>-reconfigure
```

Example:

```
# rebuild Linux from scratch, reassemble image binary
make linux-dirclean
make linux-reconfigure
make
```

### Redownload and rebuild from scratch

To redownload and rebuild a single package from scratch:

```
rm -rf /path/to/buildroot/dl/<package>
make <package>-dirclean
make <package>-reconfigure
```

Example:

```
# redownload and rebuild Linux from scratch, reassemble image binary
rm -rf /path/to/buildroot/dl/linux
make linux-dirclean
make linux-reconfigure
make
```

