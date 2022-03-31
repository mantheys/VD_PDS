#!/bin/bash
# i_x=0.08125;i_y=-3.41875;i_z=0.0
# f_x=6.41875;f_y=3.41875;f_z=3.0
# step_x=0.1625;step_y=0.1625;step_z=0.25

#test version with reduced values
i_x=0.1625;i_y=-3.3375;i_z=0.0
f_x=6.3375;f_y=3.3375;f_z=3.0
step_x=0.325;step_y=0.325;step_z=1.0

cd /nashome/s/smanthey/standalone/VD_PDS/vdriftAr/
for x in $(LC_ALL=en_US.UTF-8 seq $i_x $step_x $f_x) ; do
    for y in $(LC_ALL=en_US.UTF-8 seq $i_y $step_y $f_y) ; do
        for z in $(LC_ALL=en_US.UTF-8 seq $i_z $step_z $f_z) ; do
            ./vdrift_build/g4workshop $x $y $z
            mv -- arapuca* /nashome/s/smanthey/standalone/NEW_PARAM/
        done
    done
done