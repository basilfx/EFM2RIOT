#!/bin/sh

BOARDS="stk3200 slstk3401a slstk3402a stk3600 stk3700 stk3800 slwstk6220a sltb001a"
FAMILIES="efm32_common efr32fg13p efm32gg efr32bg1p efr32fg1v efr32mg12p efr32bg1b efr32fg1p efr32bg1v efr32bg13p efm32pg12b efr32mg1p efr32mg1b efr32mg1v efm32pg1b efm32jg1b efm32g ezr32lg efm32hg efm32zg ezr32wg efm32jg12b efr32bg12p efm32wg efr32mg13p efm32tg efm32lg ezr32hg efr32fg12p"

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

# Symlink the package into 'RIOT_ROOT/pkg'
ln -sf `realpath "$SOURCE/pkg/emlib"` "$TARGET/pkg/"
