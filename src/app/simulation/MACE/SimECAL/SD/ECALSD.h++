#pragma once

#include "MACE/Simulation/SD/ECALSD.h++"

namespace MACE::SimECAL::inline SD {

class ECALSD final : public Simulation::ECALSD {
public:
    using Simulation::ECALSD::ECALSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimECAL::inline SD
