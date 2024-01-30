#pragma once

#include "MACE/Simulation/SD/EMCPMTSD.h++"

namespace MACE::SimEMC::inline SD {

class EMCPMTSD final : public Simulation::EMCPMTSD {
public:
    using Simulation::EMCPMTSD::EMCPMTSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimEMC::inline SD
