#!/bin/bash
rm led.o  led.py  _led.so  led_wrap.c  led_wrap.o
swig -python led.i
/home/zynqmp/arty/host/bin/arm-buildroot-linux-gnueabihf-gcc -c -fpic -I/home/zynqmp/arty/host/include/python3.10 led.c led_wrap.c
/home/zynqmp/arty/host/bin/arm-buildroot-linux-gnueabihf-gcc -shared led.o led_wrap.o -o _led.so
scp _led.so root@192.168.0.123:/root
