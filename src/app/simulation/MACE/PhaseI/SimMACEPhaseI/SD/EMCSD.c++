#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/EMCSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto EMCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::EMCSD::EndOfEvent(hc);
    Analysis::Instance().SubmitEMCHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
