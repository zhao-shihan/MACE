#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECalPMTSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

auto ECalPMTSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::ECalPMTSD::EndOfEvent(hc);
    Analysis::Instance().SubmitECalPMTHC(*fHitsCollection->GetVector());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
