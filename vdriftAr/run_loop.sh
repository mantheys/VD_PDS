#!/bin/bash
i_x=0.00;i_y=-3.0875;i_z=0.0
f_x=6.4125;f_y=3.0875;f_z=1.0
step_x=0.3375;step_y=0.325;step_z=0.5

for x in $(LC_ALL=en_US.UTF-8 seq $i_x $step_x $f_x) ; do
    for y in $(LC_ALL=en_US.UTF-8 seq $i_y $step_y $f_y) ; do
        for z in $(LC_ALL=en_US.UTF-8 seq $i_z $step_z $f_z) ; do
            jobsub_submit -G dune -Q --role=Analysis -N 1 --expected-lifetime=2h --memory=500MB --disk=1GB --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --OS=SL7 file:///pnfs/dune/scratch/users/smanthey/vdriftAr/run_point.sh $x $y $z
        done
    done
done

mv "hist/arapuca"* /nashome/s/smanthey/standalone/