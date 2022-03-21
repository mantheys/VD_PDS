# VD_PDS
Repository for standalone light simulations of the vertical drift modules.

#CREAR UN PROXY
kx509
export ROLE=Analysis
voms-proxy-init -rfc -noregen -voms=dune:/dune/Role=$ROLE -valid 120:00

#ACTIVAR JOBS
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup jobsub_client
