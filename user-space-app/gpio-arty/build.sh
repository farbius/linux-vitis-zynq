#!/bin/bash

make
scp main root@192.168.0.123:/root
make clean
