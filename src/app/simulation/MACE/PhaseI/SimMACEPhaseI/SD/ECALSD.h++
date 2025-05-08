#pragma once

#include "MACE/Simulation/SD/ECALSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class ECALSD final : public MACE::Simulation::ECALSD {
public:
    using MACE::Simulation::ECALSD::ECALSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
