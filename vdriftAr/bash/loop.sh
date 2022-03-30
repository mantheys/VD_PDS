#!/bin/bash
i_x=0.00;i_y=-3.0875;i_z=0.0
f_x=6.4125;f_y=3.0875;f_z=1.0
step_x=0.6750;step_y=0.650;step_z=1.0

for x in $(LC_ALL=en_US.UTF-8 seq $i_x $step_x $f_x) ; do
    for y in $(LC_ALL=en_US.UTF-8 seq $i_y $step_y $f_y) ; do
        for z in $(LC_ALL=en_US.UTF-8 seq $i_z $step_z $f_z) ; do
            jobsub_submit -G dune -Q --role=Analysis -N 1 --expected-lifetime=2h --memory=500MB --disk=1GB --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --OS=SL7 file:///pnfs/dune/scratch/users/smanthey/vdriftAr/point.sh $x $y $z
        done
    done
done

mv -- "run/arapuca"* "/nashome/s/smanthey/standalone/VD_PDS/vdriftAr/run/"