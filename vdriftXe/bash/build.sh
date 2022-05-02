#!/bin/bash

source /nashome/s/smanthey/standalone/PDS_VD/vdriftXe/bash/setup.sh
source /nashome/s/smanthey/standalone/PDS_VD/vdriftXe/bash/setup.sh
rm -rf /nashome/s/smanthey/standalone/PDS_VD/vdriftXe/vdrift_build
rm /nashome/s/smanthey/standalone/PDS_VD/vdriftXe/vdriftXe_tar.tgz
mkdir /nashome/s/smanthey/standalone/PDS_VD/vdriftXe/vdrift_build
cd /nashome/s/smanthey/standalone/PDS_VD/vdriftXe/vdrift_build/
cmake -DGeant4_DIR=$G4COMP ../vdrift_ref/
make -j
cd /nashome/s/smanthey/standalone/PDS_VD/vdriftXe/
tar -czvf vdriftXe4x20_vspace13_tar.tgz vdrift_build