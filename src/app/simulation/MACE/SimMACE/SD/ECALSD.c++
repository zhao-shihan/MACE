#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/SD/ECALSD.h++"

namespace MACE::SimMACE::inline SD {

auto ECALSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECALSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
