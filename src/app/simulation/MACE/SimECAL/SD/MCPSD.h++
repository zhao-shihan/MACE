#pragma once

#include "MACE/Simulation/SD/MCPSD.h++"

namespace MACE::SimECAL::inline SD {

class MCPSD final : public Simulation::MCPSD {
public:
    using Simulation::MCPSD::MCPSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimECAL::inline SD
