#pragma once

#include "MACE/Simulation/SD/SciFiSiPMSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class SciFiSiPMSD final : public Simulation::SciFiSiPMSD {
public:
    using Simulation::SciFiSiPMSD::SciFiSiPMSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
