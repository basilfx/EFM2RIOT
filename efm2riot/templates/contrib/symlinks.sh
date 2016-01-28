#!/bin/sh

BOARDS="{{ boards|join(" ") }}"
FAMILIES="efm32_common {{ families|join(" ") }}"

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
