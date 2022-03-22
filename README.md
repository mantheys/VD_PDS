# CREATE A PROXY
kx509
export ROLE=Analysis
voms-proxy-init -rfc -noregen -voms=dune:/dune/Role=$ROLE -valid 120:00

#ACTIVAR JOBS
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup jobsub_client

#CREAR LIBRERIA
tar -czvf vdriftAr_tar.tgz vdrift_build