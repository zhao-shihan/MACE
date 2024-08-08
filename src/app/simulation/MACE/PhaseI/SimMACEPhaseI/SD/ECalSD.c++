#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECalSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto ECalSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECalSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECalHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
