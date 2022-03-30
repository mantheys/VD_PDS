#!/bin/bash

source setup.sh
source setup.sh
rm -rf ../vdrift_build
rm ../vdriftAr_tar.tgz
mkdir ../vdrift_build
cd ../vdrift_build/
cmake -DGeant4_DIR=$G4COMP ../vdrift_ref/
make -j
cd ..
tar -czvf vdriftAr_tar.tgz vdrift_build