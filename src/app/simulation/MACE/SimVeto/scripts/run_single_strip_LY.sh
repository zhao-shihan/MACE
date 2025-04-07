
cd ~/mace/build/
mpirun ./MACE SimVeto SimVeto/run_single_strip_LY.mac
cd ~/mace/build/SimVeto_strip_LY
hadd -f merged.root ./SimVeto_strip_LY_mpi*
rm -rf SimVeto_strip_LY_mpi*
root splitVectorToBranches.C
cd ~/mace/build


