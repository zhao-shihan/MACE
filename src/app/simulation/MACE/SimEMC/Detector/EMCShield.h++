#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimEMC::Detector {

class EMCShield final : public MACE::Detector::Definition::GeometryBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::SimEMC::Detector
