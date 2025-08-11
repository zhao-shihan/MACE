#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/SciFiSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto SciFiSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::SciFiSD::EndOfEvent(hc);
    Analysis::Instance().SubmitSciFiHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
