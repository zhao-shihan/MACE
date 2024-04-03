#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"

namespace MACE::SimEMC::inline SD {

auto EMCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::EMCSD::EndOfEvent(hc);
    Analysis::Instance().SubmitEMCHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimEMC::inline SD
