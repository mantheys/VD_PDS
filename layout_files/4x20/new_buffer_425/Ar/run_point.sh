#!/bin/bash

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup ifdhc
export IFDH_CP_MAXRETRIES=0\0\0\0\0
setup cmake v3_13_1
setup root v6_18_02a -q e17:prof
# setup geant4 v4_10_3_p03e -q e17:prof
setup geant4 v4_10_6_p01d -q e20:prof
ifdh cp -D /pnfs/dune/scratch/users/smanthey/vdriftAr/buffer/4x20/new_buffer_425/vdriftAr4x20new_buffer_425_tar.tgz ./
tar -xzvf vdriftAr4x20new_buffer_425_tar.tgz
chmod u+x vdrift_build/g4workshop

./vdrift_build/g4workshop $1 $2 $3
mv -- "arapuca"* "arapuca_${1}_${2}_${3}.root"
eval "$(echo "ifdh cp -D arapuca_${1}_${2}_${3}.root /pnfs/dune/scratch/users/smanthey/vdriftAr/buffer/4x20/new_buffer_425/data")"
