SAMPLING_DIR="Sampling_$(date "+%Y%m%d-%H:%M")"
mkdir "$SAMPLING_DIR" && cd $_

source ../../data/mace_offline_data.sh 

../../MACE SimMMS ../../SimMMS/run_em_flat.mac 

../../MACE SimVeto ../../SimVeto/run_hit_partial.mac

../../MACE SimTTC ../../SimTTC/run_em_flat.mac

../../MACE SimMACE ../../SimMACE/run_signal.mac

root -l -q '../GetCDCSimHit.cxx("SimMMS_em_flat","SimMMS_em_flat.root","Sample.root")'
root -l -q '../GetMMSSimTrack.cxx("SimMMS_em_flat","SimMMS_em_flat.root","Sample.root")'
root -l -q '../GetVetoSimHit.cxx("SimVeto_hit_partial","SimVeto_hit_partial.root","Sample.root")'
root -l -q '../GetTTCSimHit.cxx("SimTTC_em_flat","SimTTC_em_flat.root","Sample.root")'
root -l -q '../GetMCPSimHit.cxx("SimMACE_signal","SimMACE_signal.root","Sample.root")'
root -l -q '../GetTTCSimHit.cxx("SimMACE_signal","SimMACE_signal.root","Sample.root")'
root -l -q '../GetCDCSimHit.cxx("SimMACE_signal","SimMACE_signal.root","Sample.root")'
root -l -q '../GetMMSSimTrack.cxx("SimMACE_signal","SimMACE_signal.root","Sample.root")'

# ../../MACE SimECAL ../../SimECAL/test.mac 
# root '../GetECALSimHit.cxx("SimECAL_test","SimECAL_test.root","Sample.root")'

# ../../MACE PhaseI SimMACEPhaseI ../../PhaseI/SimMACEPhaseI/run_M2ee.mac
# root '../GetMRPCSimHit.cxx("SimMACEPhaseI_M2ee","SimMACEPhaseI_M2ee.root","Sample.root")'