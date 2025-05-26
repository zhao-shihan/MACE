cd ~/mace/build/
mpirun ./MACE SimVeto SimVeto/run_hit_partial.mac
cd ~/mace/build/SimVeto_hit_partial_test/
hadd -ff merged.root ./*


