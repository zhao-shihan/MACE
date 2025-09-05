# build
mkdir build && cd build && cmake .. && make

mkdir "Test_$(date "+%Y%m%d-%H:%M")" && cd "$_"

source data/mace_offline_data.sh 

# modules
# ../MACE GenMuonICDecay -d 1 -s 2 -o "test_mu2eeevv.root" 1000
# ../MACE GenMuoniumICDecay -d 1 -s 2 -o "test_M2eeevv.root" 1000
# ../MACE PhaseI SimMACEPhaseI 
# ../MACE SmearMACE 1000
# subcommand ReconECAL, ReconSciFi not tested. ReconECAL need SimMACEPhaseI_geom.yaml.  
# ReconMMSTrack: empty list of input files.
# ReconECAL: empty list of input files.

# modules=("SimDose" "SimECAL" "SimMACE" "SimMMS" "SimPTS" "SimTTC" "SimTarget" "SimVeto")

../../MACE SimMMS ../../SimMMS/run_em_flat.mac -o "SimMMS_em_flat_test.root"
../../MACE SimVeto ../../SimVeto/run_hit_partial.mac -o "SimVeto_hit_partial_test.root"
../../MACE SimTTC ../../SimTTC/run_em_flat.mac -o "SimTTC_em_flat_test.root"
../../MACE SimMACE ../../SimMACE/run_signal.mac -o "SimMACE_signal_test.root"

root -l -q '../TestCDCSimHit.cxx("SimMMS_em_flat","SimMMS_em_flat_test.root","../Sample.root")'
root -l -q '../TestMMSSimTrack.cxx("SimMMS_em_flat","SimMMS_em_flat_test.root","../Sample.root")'
root -l -q '../TestVetoSimHit.cxx("SimVeto_hit_partial","SimVeto_hit_partial_test.root","../Sample.root")'
root -l -q '../TestTTCSimHit.cxx("SimTTC_em_flat","SimTTC_em_flat_test.root","../Sample.root")'
root -l -q '../TestMCPSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
root -l -q '../TestTTCSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
root -l -q '../TestCDCSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
root -l -q '../TestMMSSimTrack.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
