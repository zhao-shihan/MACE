#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECALPMTSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto ECALPMTSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECALPMTSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALPMTHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
