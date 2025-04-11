#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/SciFiSiPMSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto SciFiSiPMSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::SciFiSiPMSD::EndOfEvent(hc);
    Analysis::Instance().SubmitSciFiSiPMHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD