#include "MACE/SimVeto/Analysis.h++"
#include "MACE/SimVeto/SD/VetoStripSD.h++"

namespace MACE::SimVetoStrip::inline SD {

auto VetoStripSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::VetoStripSD::EndOfEvent(hc);
    Analysis::Instance().SubmitVetoStripHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimVetoStrip::inline SD
