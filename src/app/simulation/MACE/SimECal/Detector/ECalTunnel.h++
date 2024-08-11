#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimECal::Detector {

class ECalTunnel final : public Mustard::Detector::Definition::DefinitionBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::SimECal::Detector
