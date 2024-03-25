#pragma once

#include "MACE/Simulation/SD/STCSD.h++"

namespace MACE::SimMMS::inline SD {

class STCSD final : public Simulation::STCSD {
public:
    using Simulation::STCSD::STCSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimMMS::inline SD
