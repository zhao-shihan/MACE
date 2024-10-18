#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECALSensorSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto ECALSensorSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECALSensorSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALSensorHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
