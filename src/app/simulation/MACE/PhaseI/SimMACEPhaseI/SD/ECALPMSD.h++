#pragma once

#include "MACE/Simulation/SD/ECALPMSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class ECALPMSD final : public Simulation::ECALPMSD {
public:
    using Simulation::ECALPMSD::ECALPMSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
