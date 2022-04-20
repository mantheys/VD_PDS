#!/bin/bash
i_x=6.725
i_y=-3.0875
f_x=7.375
f_y=3.0875
step_x=0.05
step_y=0.325
step_z=0.25
#step_x=6.75
#step_y=6.5
i_z=0.00
f_z=1.50
for x in $(LC_ALL=en_US.UTF-8 seq $i_x $step_x $f_x) ; do
    for y in $(LC_ALL=en_US.UTF-8 seq $i_y $step_y $f_y) ; do
	for z in $(LC_ALL=en_US.UTF-8 seq $i_z $step_z $f_z) ; do
            jobsub_submit -G dune -Q --role=Analysis -N 1 --expected-lifetime=2h --memory=500MB --disk=1GB --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --OS=SL7 file:///pnfs/dune/scratch/users/smanthey/vdriftXe/buffer/4x20/buffer_05/run_point.sh $x $y $z
	done
    done
done
