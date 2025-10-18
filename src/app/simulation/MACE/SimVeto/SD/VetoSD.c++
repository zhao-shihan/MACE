#include "MACE/SimVeto/Analysis.h++"
#include "MACE/SimVeto/SD/VetoSD.h++"

namespace MACE::SimVeto::inline SD {

auto VetoSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::VetoSD::EndOfEvent(hc);
    Analysis::Instance().SubmitVetoHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimVeto::inline SD
