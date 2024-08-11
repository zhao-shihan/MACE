#pragma once

#include "MACE/Simulation/SD/ECalSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class ECalSD final : public Simulation::ECalSD {
public:
    using Simulation::ECalSD::ECalSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
