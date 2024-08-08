#include "MACE/SimECal/Analysis.h++"
#include "MACE/SimECal/SD/ECalSD.h++"

namespace MACE::SimECal::inline SD {

auto ECalSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECalSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECalHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimECal::inline SD
