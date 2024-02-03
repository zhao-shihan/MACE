#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimEMC::Detector {

class EMCMagnet final : public MACE::Detector::Definition::GeometryBase {
private:
    auto Construct(G4bool checkOverlaps) -> void override;
};

} // namespace MACE::SimEMC::Detector
