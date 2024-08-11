#include "MACE/SimECal/Analysis.h++"
#include "MACE/SimECal/SD/ECalPMTSD.h++"

namespace MACE::SimECal::inline SD {

auto ECalPMTSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECalPMTSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECalPMTHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimECal::inline SD
