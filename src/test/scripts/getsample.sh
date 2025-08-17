SAMPLING_DIR="Sampling_$(date "+%Y%m%d-%H:%M")"
mkdir "$SAMPLING_DIR" && cd $_

source ../../data/mace_offline_data.sh 

../../MACE SimMMS ../../SimMMS/run_em_flat.mac 
root '../GetCDCSimHit.cxx("SimMMS_em_flat","SimMMS_em_flat.root","Sample.root")'

../../MACE SimVeto ../../SimVeto/run_hit_partial.mac
root '../GetVetoSimHit.cxx("SimVeto_hit_partial","SimVeto_hit_partial.root","Sample.root")'

../../MACE SimTTC ../../SimTTC/run_em_flat.mac
root '../GetTTCSimHit.cxx("SimTTC_em_flat","SimTTC_em_flat.root","Sample.root")'

../../MACE SimECAL ../../SimECAL/test.mac 
root '../GetECALSimHit.cxx("SimECAL_test","SimECAL_test.root","Sample.root")'

# ../MACE Sim
