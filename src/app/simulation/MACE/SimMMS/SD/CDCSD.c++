#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/SD/CDCSD.h++"

namespace MACE::SimMMS::inline SD {

auto CDCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::CDCSD::EndOfEvent(hc);
    Analysis::Instance().SubmitCDCHC(fHitsCollection->GetVector());
    Analysis::Instance().SubmitCDCTrackData(fTrackData);
}

} // namespace MACE::SimMMS::inline SD
