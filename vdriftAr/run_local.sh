#!/bin/bash
i_x=0.0;i_y=-3.25;i_z=0.0
f_x=6.75;f_y=3.25;f_z=1.0
step_x=0.6750;step_y=0.650;step_z=1.0

for x in $(LC_ALL=en_US.UTF-8 seq $i_x $step_x $f_x) ; do
    for y in $(LC_ALL=en_US.UTF-8 seq $i_y $step_y $f_y) ; do
        for z in $(LC_ALL=en_US.UTF-8 seq $i_z $step_z $f_z) ; do
            ./vdrift_build/g4workshop $x $y $z
            mv -- arapuca* run/
        done
    done
done