#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::Detector::Definition {

class SolenoidS1Field final : public GeometryBase {
private:
    auto Construct(G4bool checkOverlaps) -> void override;
};

} // namespace MACE::Detector::Definition
