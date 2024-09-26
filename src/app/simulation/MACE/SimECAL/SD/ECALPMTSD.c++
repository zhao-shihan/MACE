#include "MACE/SimECAL/Analysis.h++"
#include "MACE/SimECAL/SD/ECALPMTSD.h++"

namespace MACE::SimECAL::inline SD {

auto ECALPMTSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECALPMTSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALPMTHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimECAL::inline SD
