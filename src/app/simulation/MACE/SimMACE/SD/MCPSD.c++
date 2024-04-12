#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/SD/MCPSD.h++"

namespace MACE::SimMACE::inline SD {

auto MCPSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::MCPSD::EndOfEvent(hc);
    Analysis::Instance().SubmitMCPHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
