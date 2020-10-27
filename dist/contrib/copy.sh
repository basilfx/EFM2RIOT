#!/bin/sh

BOARDS="slstk3301a slstk3400a slstk3401a slstk3402a slstk3701a sltb001a sltb004a sltb009a sltb010a slwstk6000b slwstk6220a stk3200 stk3600 stk3700 stk3800"
FAMILIES="efm32g efm32gg efm32gg11b efm32gg12b efm32hg efm32jg12b efm32jg1b efm32lg efm32pg12b efm32pg1b efm32tg efm32tg11b efm32wg efm32zg efr32bg12p efr32bg13p efr32bg14p efr32bg1b efr32bg1p efr32bg1v efr32bg21 efr32bg22 efr32fg12p efr32fg13p efr32fg14p efr32fg14v efr32fg1p efr32fg1v efr32fg22 efr32mg12p efr32mg13p efr32mg14p efr32mg1b efr32mg1p efr32mg1v efr32mg21 efr32mg22 efr32zg13p efr32zg14p ezr32hg ezr32lg ezr32wg"

SOURCE=$(dirname "$0")/..
TARGET=$1

# Copy all boards into `RIOT_ROOT/boards/`.
for board in $BOARDS
do
    rm -rf "$TARGET/boards/$board"
    cp -r "$(realpath "$SOURCE/boards/$board")" "$TARGET/boards/$board"
done

# Copy all families into `RIOT_ROOT/cpu/families/`.
for family in $FAMILIES
do
    rm -rf "$TARGET/cpu/efm32/families/$family/"
    cp -r "$(realpath "$SOURCE/cpu/efm32/families/$family")" "$TARGET/cpu/efm32/families/$family"
done
