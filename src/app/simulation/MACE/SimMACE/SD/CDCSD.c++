#include "MACE/SimMACE/Data/Analysis.h++"
#include "MACE/SimMACE/SD/CDCSD.h++"

namespace MACE::SimMACE::inline SD {

auto CDCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::CDCSD::EndOfEvent(hc);
    Data::Analysis::Instance().SubmitCDCHC(fHitsCollection->GetVector());
    Data::Analysis::Instance().SubmitCDCTrackData(fTrackData);
}

} // namespace MACE::SimMACE::inline SD
