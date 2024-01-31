#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::Detector::Definition {

class BeamDegrader final : public GeometryBase {
public:
    bool Enabled() const override;

private:
    auto Construct(G4bool checkOverlaps) -> void override;
};

} // namespace MACE::Detector::Definition
