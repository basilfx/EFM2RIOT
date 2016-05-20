#!/bin/sh

BOARDS="{{ boards|join(" ") }}"
FAMILIES="efm32_common {{ families|join(" ") }}"

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
