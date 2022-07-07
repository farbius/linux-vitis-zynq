zynqmp@ubuntu:~/linux-vitis-zynq/user-space-app/gpio-py$ swig -python led.i
zynqmp@ubuntu:~/linux-vitis-zynq/user-space-app/gpio-py$ /home/zynqmp/arty/host/bin/arm-buildroot-linux-gnueabihf-gcc -c -fpic -I/home/zynqmp/arty/host/include/python3.10 led.c led_wrap.c 
zynqmp@ubuntu:~/linux-vitis-zynq/user-space-app/gpio-py$ /home/zynqmp/arty/host/bin/arm-buildroot-linux-gnueabihf-gcc -shared led.o led_wrap.o -o _led.so
zynqmp@ubuntu:~/linux-vitis-zynq/user-space-app/gpio-py$ scp _led.so root@192.168.0.123:/root
root@192.168.0.123's password: 
_led.so                                                                                           100%   49KB   6.1MB/s   00:00    
zynqmp@ubuntu:~/linux-vitis-zynq/user-space-app/gpio-py$ 

