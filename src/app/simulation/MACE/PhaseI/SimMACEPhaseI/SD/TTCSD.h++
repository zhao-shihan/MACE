#pragma once

#include "MACE/PhaseI/Simulation/SD/TTCSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class TTCSD final : public Simulation::TTCSD {
public:
    using Simulation::TTCSD::TTCSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} 
