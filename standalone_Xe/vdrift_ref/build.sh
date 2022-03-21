#!/bin/bash
rm -rf vdrift_build
mkdir vdrift_build
cd vdrift_build/
cmake -DGeant4_DIR=$G4COMP ../vdrift_ref/
make -j
cd ..