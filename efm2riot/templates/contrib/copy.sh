#!/bin/sh

BOARDS="{{ boards|join(" ") }}"
FAMILIES="{{ families|join(" ") }}"

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
