#!/bin/sh

BOARDS="stk3200 slstk3401a stk3600 stk3700 stk3800 slwstk6220a thunderboard_sense"
FAMILIES="efm32_common efm32g efm32gg efm32hg efm32jg1b efm32lg efm32pg1b efm32tg efm32wg efm32zg efr32bg1b efr32bg1p efr32bg1v efr32fg1p efr32fg1v efr32mg1b efr32mg1p efr32mg1v efr32zg1b efr32zg1p efr32zg1v ezr32hg ezr32lg ezr32wg"

SOURCE=`dirname $0`/..
TARGET=$1

# Symlink all boards into 'RIOT_ROOT/boards/'.
for board in $BOARDS
do
    ln -sf `realpath "$SOURCE/boards/$board"` "$TARGET/boards/"
done

# Symlink all families into 'RIOT_ROOT/cpu/'.
for family in $FAMILIES
do
    ln -sf `realpath "$SOURCE/cpu/$family"` "$TARGET/cpu/"
done