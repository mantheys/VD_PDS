#!/bin/bash

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
#source /cvmfs/fermilab.opensciencegrid.org/products/common/etc/setup
setup ifdhc
export IFDH_CP_MAXRETRIES=0\0\0\0\0
#source /grid/fermiapp/products/dune/setup_dune.sh
#source /cvmfs/fermilab.opensciencegrid.org/products/larsoft/setup
setup cmake v3_13_1
setup root v6_18_02a -q e17:prof
# setup geant4 v4_10_3_p03e -q e17:prof
setup geant4 v4_10_6_p01d -q e20:prof
ifdh cp -D /pnfs/dune/scratch/users/smanthey/vdriftXe/buffer/4x20/buffer_225/vdriftXe4x20_buffer_225_tar.tgz ./
tar -xzvf vdriftXe4x20_buffer_225_tar.tgz
#ifdh cp -D /pnfs/dune/scratch/users/hamza/vdriftXe/move_arapuca.sh ./
chmod u+x vdrift_build/g4workshop
#chmod u+x move_arapuca.sh
#ifdh cp -D /pnfs/dune/scratch/users/lpaulucc/vdriftXe/preprocess ./
#chmod u+x preprocess

./vdrift_build/g4workshop $1 $2 $3
mv -- "arapuca"* "arapuca_${1}_${2}_${3}.root"
#ifdh cp -D "arapuca.root" "/pnfs/dune/scratch/users/hamza/arapuca_${1}_${2}.root"

#eval "$(echo "ifdh cp -D arapuca.root /pnfs/dune/scratch/users/hamza/arapuca_${1}_${2}.root")"
eval "$(echo "ifdh cp -D arapuca_${1}_${2}_${3}.root /pnfs/dune/scratch/users/smanthey/vdriftXe/buffer/4x20/buffer_225/.")"
#mv /pnfs/dune/scratch/users/hamza/vdriftXe/arapuca_${1}_${2}.root  /dune/app/users/hamza/standalone_sim_Xe_jobs/histograms_Xe/
#./move_arapuca.sh
