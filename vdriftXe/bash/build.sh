#!/bin/bash

source /nashome/s/smanthey/standalone/VD_PDS/vdriftXe/bash/setup.sh
source /nashome/s/smanthey/standalone/VD_PDS/vdriftXe/bash/setup.sh
rm -rf /nashome/s/smanthey/standalone/VD_PDS/vdriftXe/vdrift_build
rm /nashome/s/smanthey/standalone/VD_PDS/vdriftXe/vdriftXe_tar.tgz
mkdir /nashome/s/smanthey/standalone/VD_PDS/vdriftXe/vdrift_build
cd /nashome/s/smanthey/standalone/VD_PDS/vdriftXe/vdrift_build/
cmake -DGeant4_DIR=$G4COMP ../vdrift_ref/
make -j
cd /nashome/s/smanthey/standalone/VD_PDS/vdriftXe/
tar -czvf vdriftXe_tar.tgz vdrift_build