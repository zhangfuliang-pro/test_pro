#!/bin/bash

while getopts "a:c:" opt; do
  case $opt in
    a)
      alkaid_dir=$OPTARG
      ;;
    c)
      chip=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      ;;
  esac
done

uboot_dir=$PWD


if [ "${chip}" = "i5" ]; then
  make infinity5_defconfig
  make clean; make
  if [ -d $alkaid_dir/project/board/i5/boot/nor/uboot ]; then
    cp $uboot_dir/u-boot.xz.img.bin $alkaid_dir/project/board/i5/boot/nor/uboot
  fi

  make infinity5_spinand_defconfig
  make clean; make
  if [ -d $alkaid_dir/project/board/i5/boot/spinand/uboot ]; then
    cp $uboot_dir/u-boot_spinand.xz.img.bin $alkaid_dir/project/board/i5/boot/spinand/uboot
  fi
fi

if [ "${chip}" = "i6" ]; then
  make infinity6_defconfig
  make clean; make -j4
  if [ -d $alkaid_dir/project/board/${chip}/boot/nor/uboot ]; then
    cp $uboot_dir/u-boot.xz.img.bin $alkaid_dir/project/board/${chip}/boot/nor/uboot
  fi

  make infinity6_spinand_defconfig
  make clean; make -j4
  if [ -d $alkaid_dir/project/board/${chip}/boot/spinand/uboot ]; then
    cp $uboot_dir/u-boot_spinand.xz.img.bin $alkaid_dir/project/board/${chip}/boot/spinand/uboot
  fi
fi