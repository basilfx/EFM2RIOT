#!/bin/sh

BOARDS="stk3200 slstk3401a stk3600 stk3700 stk3800 slwstk6220a"
FAMILIES="efm32_common efm32g efm32gg efm32hg efm32jg1b efm32lg efm32pg1b efm32tg efm32wg efm32zg ezr32lg ezr32wg"

SOURCE=`dirname $0`/..
TARGET=$1

# Symlink all boards into 'RIOT_ROOT/boards/'.
for board in $BOARDS
do
    ln -sF `realpath "$SOURCE/boards/$board"` "$TARGET/boards/$board"
done

# Symlink all families into 'RIOT_ROOT/cpu/'.
for family in $FAMILIES
do
    ln -sF `realpath "$SOURCE/cpu/$family"` "$TARGET/cpu/$family"
done