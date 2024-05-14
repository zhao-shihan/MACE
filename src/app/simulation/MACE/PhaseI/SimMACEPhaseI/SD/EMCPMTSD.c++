#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/EMCPMTSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto EMCPMTSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::EMCPMTSD::EndOfEvent(hc);
    Analysis::Instance().SubmitEMCPMTHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
