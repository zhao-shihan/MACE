#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/MCPSD.h++"

namespace MACE::SimEMC::inline SD {

auto MCPSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::MCPSD::EndOfEvent(hc);
    Analysis::Instance().SubmitMCPHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimEMC::inline SD
