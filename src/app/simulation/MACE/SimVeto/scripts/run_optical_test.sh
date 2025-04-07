cd ~/mace/build
mpirun ./MACE SimVeto SimVeto/optical_test_run.mac
cd ~/mace/build/SimVeto_optical_test
hadd -f merged.root ./*
rm -rf SimVeto_optical_test_mpi*

