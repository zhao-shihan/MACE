#include "MACE/SimECAL/Analysis.h++"
#include "MACE/SimECAL/SD/MCPSD.h++"

namespace MACE::SimECAL::inline SD {

auto MCPSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::MCPSD::EndOfEvent(hc);
    Analysis::Instance().SubmitMCPHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimECAL::inline SD
