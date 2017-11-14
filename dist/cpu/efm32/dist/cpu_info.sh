#!/bin/sh

cat $1 | grep FLASH_BASE | awk -F"[()]" '{print $2}' | sed -e "s/UL//"
cat $1 | grep FLASH_SIZE | awk -F"[()]" '{print $2}' | sed -e "s/UL//"
cat $1 | grep SRAM_BASE | awk -F"[()]" '{print $2}' | sed -e "s/UL//"
cat $1 | grep SRAM_SIZE | awk -F"[()]" '{print $2}' | sed -e "s/UL//"
