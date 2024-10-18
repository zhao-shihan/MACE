#include "MACE/SimECAL/Analysis.h++"
#include "MACE/SimECAL/SD/ECALSensorSD.h++"

namespace MACE::SimECAL::inline SD {

auto ECALSensorSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECALSensorSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALSensorHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimECAL::inline SD
