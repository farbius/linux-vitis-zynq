#!/bin/sh

cd ${BINARIES_DIR}
cp ${BR2_EXTERNAL_EDU_PATH}/board/zynq/image.its .
mkimage -f image.its image.itb
