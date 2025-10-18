#include "MACE/SimVeto/Analysis.h++"
#include "MACE/SimVeto/SD/VetoPMSD.h++"

namespace MACE::SimVeto::inline SD {

auto VetoPMSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::VetoPMSD::EndOfEvent(hc);
    Analysis::Instance().SubmitVetoPMHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimVetoPM::inline SD
