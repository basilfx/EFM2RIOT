#!/bin/sh

BOARDS="brd4162a slstk3401a slstk3402a slstk3701a sltb001a slwstk6220a stk3200 stk3600 stk3700 stk3800"

SOURCE=`dirname $0`/..
TARGET=$1

# Symlink all boards into `RIOT_ROOT/boards/`.
for board in $BOARDS
do
    ln -sf `realpath "$SOURCE/boards/$board"` "$TARGET/boards/"
done

# Symlink the cpu folder into `RIOT_ROOT/cpu`.
ln -sf `realpath "$SOURCE/cpu/efm32"` "$TARGET/cpu/"

# Symlink the pkg/gecko_sdk folder into `RIOT_ROOT/pkg/gecko_sdk`.
ln -sf `realpath "$SOURCE/pkg/gecko_sdk"` "$TARGET/pkg/"
