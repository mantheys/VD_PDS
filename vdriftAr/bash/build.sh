#!/bin/bash

source /nashome/s/smanthey/standalone/PDS_VD/vdriftAr/bash/setup.sh
source /nashome/s/smanthey/standalone/PDS_VD/vdriftAr/bash/setup.sh
rm -rf /nashome/s/smanthey/standalone/PDS_VD/vdriftAr/vdrift_build
rm /nashome/s/smanthey/standalone/PDS_VD/vdriftAr/vdriftAr_tar.tgz
mkdir /nashome/s/smanthey/standalone/PDS_VD/vdriftAr/vdrift_build
cd /nashome/s/smanthey/standalone/PDS_VD/vdriftAr/vdrift_build/
cmake -DGeant4_DIR=$G4COMP ../vdrift_ref/
make -j
cd /nashome/s/smanthey/standalone/PDS_VD/vdriftAr/
tar -czvf vdriftAr4x20_vspace13_tar.tgz vdrift_build