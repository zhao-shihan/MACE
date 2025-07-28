# build
mkdir build && cd build && cmake .. && make

source data/mace_offline_data.sh 

# modules
./MACE GenMuonICDecay -d 1 -s 2 -o "test_mu2eeevv_$(date "+%Y%m%d-%H:%M").root" 1000
./MACE GenMuoniumICDecay -d 1 -s 2 -o "test_M2eeevv_$(date "+%Y%m%d-%H:%M").root" 1000
./MACE PhaseI SimMACEPhaseI 
./MACE SmearMACE 1000
# subcommand ReconECAL, ReconSciFi not tested. ReconECAL need SimMACEPhaseI_geom.yaml.  
# ReconMMSTrack: empty list of input files.
# ReconECAL: empty list of input files.

modules=("SimDose" "SimECAL" "SimMACE" "SimMMS" "SimPTS" "SimTTC" "SimTarget" "SimVeto")
for module in "${modules[@]}"; do
    echo "+++> testing: $module <+++"
    ./MACE SimMACE $module
    echo "---> tesed: $module <---"
done
