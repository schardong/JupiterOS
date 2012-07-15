#!/bin/bash

if [ "$(id -u)" != "0" ]; then
    echo "You must run this script as root"
    exit 1
else
    /sbin/losetup /dev/loop1 floppy.img
    mount /dev/loop1 /mnt
    cp bin/kernel /mnt/kernel
    cp initrd.img /mnt/initrd
    umount /dev/loop1
    /sbin/losetup -d /dev/loop1
    losetup /dev/loop1 floppy.img
    bochs -q -f bochsrc.txt
    losetup -d /dev/loop1
    exit 0
fi
