#!/bin/bash

source /nashome/s/smanthey/standalone/VD_PDS/vdriftAr/bash/setup.sh
source /nashome/s/smanthey/standalone/VD_PDS/vdriftAr/bash/setup.sh
rm -rf /nashome/s/smanthey/standalone/VD_PDS/vdriftAr/vdrift_build
rm /nashome/s/smanthey/standalone/VD_PDS/vdriftAr/vdriftAr_tar.tgz
mkdir /nashome/s/smanthey/standalone/VD_PDS/vdriftAr/vdrift_build
cd /nashome/s/smanthey/standalone/VD_PDS/vdriftAr/vdrift_build/
cmake -DGeant4_DIR=$G4COMP ../vdrift_ref/
make -j
cd /nashome/s/smanthey/standalone/VD_PDS/vdriftAr/
tar -czvf vdriftAr_tar.tgz vdrift_build