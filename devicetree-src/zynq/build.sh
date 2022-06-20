#!/bin/bash
gcc -I my_dts -E -nostdinc -undef -D__DTS__ -x assembler-with-cpp -o zynq-arty.dts system-top.dts
dtc -I dts -O dtb -o zynq-arty.dtb zynq-arty.dts
