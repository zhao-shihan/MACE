#include "MACE/SimMACE/Data/Analysis.h++"
#include "MACE/SimMACE/SD/CDCSD.h++"

namespace MACE::SimMACE::inline SD {

auto CDCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::CDCSD::EndOfEvent(hc);
    Analysis::Instance().SubmitCDCHC(fHitsCollection->GetVector());
    Analysis::Instance().SubmitCDCTrackData(fTrack);
}

} // namespace MACE::SimMACE::inline SD
