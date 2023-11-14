#!/bin/bash

mkdir -p tmp/
cd tmp/
fold="buildroot"
if [ -d "$PWD/$fold" ]; then
  echo "Buildroot repo is already cloned"
else
  git clone https://github.com/buildroot/buildroot.git
  cd buildroot/
  git checkout tags/2023.05
  cd ..
fi
mkdir -p zynq_lin
cd zynq_lin/
make --directory=../buildroot/ BR2_EXTERNAL=../../external-tree/ zynq_defconfig O=$PWD
make
