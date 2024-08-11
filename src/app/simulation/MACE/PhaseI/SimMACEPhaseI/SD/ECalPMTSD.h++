#pragma once

#include "MACE/Simulation/SD/ECalPMTSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class ECalPMTSD final : public Simulation::ECalPMTSD {
public:
    using Simulation::ECalPMTSD::ECalPMTSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
