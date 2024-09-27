#include "MACE/SimECAL/Analysis.h++"
#include "MACE/SimECAL/SD/ECALSD.h++"

namespace MACE::SimECAL::inline SD {

auto ECALSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECALSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECALHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimECAL::inline SD
