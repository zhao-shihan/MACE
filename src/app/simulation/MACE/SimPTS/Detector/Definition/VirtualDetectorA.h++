#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimPTS::Detector::Definition {

class VirtualDetectorA final : public Mustard::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
};

} // namespace MACE::SimPTS::Detector::Definition
