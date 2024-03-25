#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/SD/STCSD.h++"

namespace MACE::SimMMS::inline SD {

auto STCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::STCSD::EndOfEvent(hc);
    Analysis::Instance().SubmitSTCHC(fHitsCollection->GetVector());
}

} // namespace MACE::SimMMS::inline SD
