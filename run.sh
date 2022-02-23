#!/bin/bash

MAIN_DIR="$(dirname $(dirname $(realpath $0)) )"
echo "MAIN_DIR: $MAIN_DIR"

i_x=0.0;i_y=0.0;i_z=0.0
f_x=1.0;f_y=1.0;f_z=1.0
step_x=0.5;step_y=0.5;step_z=0.5

for x in $(LC_ALL=en_US.UTF-8 seq $i_x $step_x $f_x) ; do
    for y in $(LC_ALL=en_US.UTF-8 seq $i_y $step_y $f_y) ; do
        for z in $(LC_ALL=en_US.UTF-8 seq $i_z $step_z $f_z) ; do
            "${MAIN_DIR}/vdrift_build/g4workshop" $x $y $z
            mv -- "${MAIN_DIR}/arapuca.root" "${MAIN_DIR}/sim/arapuca_${x}_${y}_${z}.root"
        done
    done
done