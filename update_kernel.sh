#!/bin/bash

scp eoo5@thoth.cs.pitt.edu:/u/OSLab/USERNAME/linux-5.10.140/arch/i386/boot/bzImage .
scp eoo5@thoth.cs.pitt.edu:/u/OSLab/USERNAME/linux-5.10.140/System.map .
scp eoo5thoth.cs.pitt.edu:/u/OSLab/USERNAME/linux-5.10.140/mods.tar.gz .

cp bzImage /boot/vmlinuz-5.10.140-cs1550
cp System.map /boot/System.map-5.10.140-cs1550

tar xfz mods.tar.gz

cd mods/lib/modules
mv 5.10-140-cs1550 /lib/modules

echo "Kernel and modules updated."

update-initramfs -c -k 5.10.140-cs1550
grub-mkconfig -o /boot/grub/grub.cfg
