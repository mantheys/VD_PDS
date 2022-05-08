#!/bin/bash
source /grid/fermiapp/products/common/etc/setup
setup jobsub_client
source /grid/fermiapp/products/dune/setup_dune.sh
setup cmake v3_13_1
setup root v6_18_02a -q e17:prof
# setup geant4 v4_10_3_p03e -q e17:prof
setup geant4 v4_10_6_p01d -q e20:prof

