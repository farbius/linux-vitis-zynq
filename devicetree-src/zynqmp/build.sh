#!/bin/bash
gcc -I my_dts -E -nostdinc -undef -D__DTS__ -x assembler-with-cpp -o zynqmp-trenz.dts system-top.dts
dtc -I dts -O dtb -o zynqmp-trenz.dtb zynqmp-trenz.dts
