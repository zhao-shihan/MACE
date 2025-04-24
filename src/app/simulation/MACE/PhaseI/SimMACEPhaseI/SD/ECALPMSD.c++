#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECALPMSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto ECALPMSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    MACE::Simulation::ECALPMSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALPMHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
