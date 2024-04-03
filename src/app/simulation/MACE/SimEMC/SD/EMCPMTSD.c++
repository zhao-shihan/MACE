#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/EMCPMTSD.h++"

namespace MACE::SimEMC::inline SD {

auto EMCPMTSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::EMCPMTSD::EndOfEvent(hc);
    Analysis::Instance().SubmitEMCPMTHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimEMC::inline SD
