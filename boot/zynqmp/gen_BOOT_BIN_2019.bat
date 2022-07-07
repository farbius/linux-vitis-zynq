@echo off
rem generate boot.bin
C:\Xilinx\SDK\2019.1\bin\bootgen -image output_itb.bif -arch zynqmp -o BOOT.BIN -w on
