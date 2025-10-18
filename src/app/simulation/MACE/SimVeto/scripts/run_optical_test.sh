cd ~/mace/build/
mpirun ./MACE SimVeto SimVeto/run_optical_test.mac
cd ~/mace/build/SimVeto_optical_test/
hadd -ff merged.root ./SimVeto_optical_test_mpi*
rm -rf SimVeto_optical_test_mpi*

