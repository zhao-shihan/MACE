#include "MACE/SimMACE/Data/Analysis.h++"
#include "MACE/SimMACE/SD/STCSD.h++"

namespace MACE::SimMACE::inline SD {

auto STCSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::STCSD::EndOfEvent(hc);
    Data::Analysis::Instance().SubmitSTCHC(fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
