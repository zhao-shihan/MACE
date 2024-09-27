#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECALSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto ECALSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECALSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
