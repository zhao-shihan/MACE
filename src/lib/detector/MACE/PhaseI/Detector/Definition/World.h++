#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::PhaseI::Detector::Definition {

class World final : public MACE::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
};

} // namespace MACE::PhaseI::Detector::Definition
