#pragma once

#include "MACE/PhaseI/Simulation/SD/TTCSiPMSD.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class TTCSiPMSD final : public Simulation::TTCSiPMSD {
public:
    using Simulation::TTCSiPMSD::TTCSiPMSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} 
