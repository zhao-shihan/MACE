#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::Detector::Definition {

class EMCMagnet final : public DefinitionBase {
private:
    auto Construct(G4bool checkOverlaps) -> void override;
};

} // namespace MACE::Detector::Definition
