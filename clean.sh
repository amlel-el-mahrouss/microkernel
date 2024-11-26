#!/bin/zsh

if cd init >/dev/null 2>&1; then
    make -f ${MACHINE}.make clean
else
    echo "Failed to change directory into init/!"
    exit 1
fi
