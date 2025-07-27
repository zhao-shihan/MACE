# build
mkdir build && cd build && cmake .. && make

# modules
modules=("GenMuonICDecay" "GenMuoniumICDecay" "MakeGeometry" "PhaseI" "ReconECAL" "ReconMMSTrack" "SimDose" "SimECAL" "SimMACE" "SimMMS" "SimPTS" "SimTTC" "SimTarget" "SimVeto" "SmearMACE")
for module in "${modules[@]}"; do
    echo "+++> testing: $module <+++"
    ./MACE SimMACE $module
    echo "---> tesed: $module <---"
done
