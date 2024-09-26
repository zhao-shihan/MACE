#pragma once

#include "MACE/Simulation/SD/ECALPMTSD.h++"

namespace MACE::SimECAL::inline SD {

class ECALPMTSD final : public Simulation::ECALPMTSD {
public:
    using Simulation::ECALPMTSD::ECALPMTSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimECAL::inline SD
