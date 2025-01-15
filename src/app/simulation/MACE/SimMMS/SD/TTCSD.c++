#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/SD/TTCSD.h++"

namespace MACE::SimMMS::inline SD {

auto TTCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::TTCSD::EndOfEvent(hc);
    Analysis::Instance().SubmitTTCHC(*fHitsCollection->GetVector());
    }

} // namespace MACE::SimMMS::inline SD
