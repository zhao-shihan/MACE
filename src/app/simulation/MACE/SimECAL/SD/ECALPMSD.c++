#include "MACE/SimECAL/Analysis.h++"
#include "MACE/SimECAL/SD/ECALPMSD.h++"

namespace MACE::SimECAL::inline SD {

auto ECALPMSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECALPMSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALPMHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimECAL::inline SD
