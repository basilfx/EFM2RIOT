#!/bin/sh

BOARDS="{{ boards|join(" ") }}"
FAMILIES="{{ families|join(" ") }}"

SOURCE=`dirname $0`/..
TARGET=$1

# Symlink all boards into `RIOT_ROOT/boards/`.
for board in $BOARDS
do
    ln -sf `realpath "$SOURCE/boards/$board"` "$TARGET/boards/"
done

# Symlink the families folder into `RIOT_ROOT/cpu/families/`.
for family in $FAMILIES
do
    ln -sf `realpath "$SOURCE/cpu/efm32/families/$family"` "$TARGET/cpu/efm32/families/"
done
