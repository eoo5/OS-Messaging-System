#!/bin/bash

make -j2 ARCH=i386

mkdir mods

make INSTALL_MOD_PATH=mods modules_install

tar cvfz mods.tar.gz mods/

rm -rf mods

echo "Kernel built and mod packaged"

#chmod +x build_kernel.sh
#./build_kernel.sh

