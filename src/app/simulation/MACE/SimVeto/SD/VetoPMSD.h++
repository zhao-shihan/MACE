#pragma once

#include "MACE/Simulation/SD/VetoPMSD.h++"

namespace MACE::SimVeto::inline SD {

class VetoPMSD final : public Simulation::VetoPMSD {
public:
    using Simulation::VetoPMSD::VetoPMSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimVetoPM::inline SD
