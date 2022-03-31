#!/bin/bash

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup ifdhc
export IFDH_CP_MAXRETRIES=0\0\0\0\0

setup cmake v3_13_1
setup root v6_18_02a -q e17:prof
setup geant4 v4_10_3_p03e -q e17:prof

ifdh cp -D /pnfs/dune/scratch/users/smanthey/vdriftXe/vdriftXe_tar.tgz ./
tar -xzvf vdriftXe_tar.tgz
chmod u+x vdrift_build/g4workshop
./vdrift_build/g4workshop $1 $2 $3
eval "$(echo "ifdh cp -D arapuca* /pnfs/dune/scratch/users/smanthey/vdriftXe/run/.")"

