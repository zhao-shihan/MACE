#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/SD/TTCSiPMSD.h++"

namespace MACE::SimMMS::inline SD {

auto TTCSiPMSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::TTCSiPMSD::EndOfEvent(hc);
    Analysis::Instance().SubmitTTCSiPMHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimMMS::inline SD
