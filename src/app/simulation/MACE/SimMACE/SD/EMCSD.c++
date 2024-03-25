#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/SD/EMCSD.h++"

namespace MACE::SimMACE::inline SD {

auto EMCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::EMCSD::EndOfEvent(hc);
    Analysis::Instance().SubmitEMCHC(fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
