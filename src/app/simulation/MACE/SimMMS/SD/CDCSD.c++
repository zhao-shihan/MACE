#include "MACE/SimMMS/Data/Analysis.h++"
#include "MACE/SimMMS/SD/CDCSD.h++"

namespace MACE::SimMMS::inline SD {

auto CDCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::CDCSD::EndOfEvent(hc);
    Data::Analysis::Instance().SubmitCDCHC(fHitsCollection->GetVector());
    Data::Analysis::Instance().SubmitCDCTrackData(fTrackData);
}

} // namespace MACE::SimMMS::inline SD
