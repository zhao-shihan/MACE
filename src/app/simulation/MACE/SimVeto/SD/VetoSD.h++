#pragma once

#include "MACE/Simulation/SD/VetoSD.h++"

namespace MACE::SimVeto::inline SD {

class VetoSD final : public Simulation::VetoSD {
public:
    using Simulation::VetoSD::VetoSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimVeto::inline SD
