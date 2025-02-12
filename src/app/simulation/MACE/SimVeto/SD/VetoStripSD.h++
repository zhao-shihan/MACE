#pragma once

#include "MACE/Simulation/SD/VetoStripSD.h++"

namespace MACE::SimVetoStrip::inline SD {

class VetoStripSD final : public Simulation::VetoStripSD {
public:
    using Simulation::VetoStripSD::VetoStripSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimVetoStrip::inline SD
