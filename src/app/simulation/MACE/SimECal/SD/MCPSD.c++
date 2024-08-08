#include "MACE/SimECal/Analysis.h++"
#include "MACE/SimECal/SD/MCPSD.h++"

namespace MACE::SimECal::inline SD {

auto MCPSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::MCPSD::EndOfEvent(hc);
    Analysis::Instance().SubmitMCPHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimECal::inline SD
