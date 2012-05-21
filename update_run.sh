#!/bin/bash

sudo /sbin/losetup /dev/loop1 floppy.img
sudo mount /dev/loop1 /mnt
sudo cp bin/kernel /mnt/kernel
sudo cp initrd.img /mnt/initrd
sudo umount /dev/loop1
sudo /sbin/losetup -d /dev/loop1
sudo losetup /dev/loop1 floppy.img
sudo bochs-gdb -f bochsrc.txt
sudo losetup -d /dev/loop1
