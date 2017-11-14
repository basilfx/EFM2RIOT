#!/bin/sh

BOARDS="{{ boards|join(" ") }}"

SOURCE=`dirname $0`/..
TARGET=$1

# Symlink all boards into `RIOT_ROOT/boards/`.
for board in $BOARDS
do
    ln -sf `realpath "$SOURCE/boards/$board"` "$TARGET/boards/"
done

# Symlink the cpu folder into `RIOT_ROOT/cpu`.
ln -sf `realpath "$SOURCE/cpu/efm32"` "$TARGET/cpu/"
