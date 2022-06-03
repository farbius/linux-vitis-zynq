#!/bin/sh

cd ${BINARIES_DIR}
cp ${BR2_EXTERNAL_MYDIR_PATH}/board/zynq/image.its .
gzip --force --keep Image
mkimage -f image.its image.itb
