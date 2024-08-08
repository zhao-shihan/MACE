#pragma once

#include "MACE/Simulation/SD/ECalPMTSD.h++"

namespace MACE::SimECal::inline SD {

class ECalPMTSD final : public Simulation::ECalPMTSD {
public:
    using Simulation::ECalPMTSD::ECalPMTSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimECal::inline SD
