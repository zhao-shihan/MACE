#include "MACE/SimMACE/Data/Analysis.h++"
#include "MACE/SimMACE/SD/TTCSD.h++"

namespace MACE::SimMACE::inline SD {

auto TTCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::TTCSD::EndOfEvent(hc);
    Data::Analysis::Instance().SubmitTTCHC(fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
