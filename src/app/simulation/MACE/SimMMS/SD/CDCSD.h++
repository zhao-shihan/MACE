#pragma once

#include "MACE/Simulation/SD/CDCSD.h++"

namespace MACE::SimMMS::inline SD {

class CDCSD final : public Simulation::CDCSD {
public:
    using Simulation::CDCSD::CDCSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimMMS::inline SD
