#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/SD/ECalSD.h++"

namespace MACE::SimMACE::inline SD {

auto ECalSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECalSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECalHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
