#pragma once

#include "MACE/PhaseI/Simulation/SD/SciFiSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class SciFiSD final : public Simulation::SciFiSD {
public:
    using Simulation::SciFiSD::SciFiSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
