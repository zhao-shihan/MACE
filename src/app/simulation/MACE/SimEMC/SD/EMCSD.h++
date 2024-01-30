#pragma once

#include "MACE/Simulation/SD/EMCSD.h++"

namespace MACE::SimEMC::inline SD {

class EMCSD final : public Simulation::EMCSD {
public:
    using Simulation::EMCSD::EMCSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimEMC::inline SD
