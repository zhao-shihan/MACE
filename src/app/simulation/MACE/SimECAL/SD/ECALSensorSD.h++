#pragma once

#include "MACE/Simulation/SD/ECALSensorSD.h++"

namespace MACE::SimECAL::inline SD {

class ECALSensorSD final : public Simulation::ECALSensorSD {
public:
    using Simulation::ECALSensorSD::ECALSensorSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace MACE::SimECAL::inline SD
