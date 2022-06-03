#!/bin/bash
gcc -I my_dts -E -nostdinc -undef -D__DTS__ -x assembler-with-cpp -o arty_zynq.dts system-top.dts
dtc -I dts -O dtb -o system.dtb arty_zynq.dts
