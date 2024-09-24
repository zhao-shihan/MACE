#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimECAL::Detector {

class ECALShield final : public Mustard::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
};

} // namespace MACE::SimECAL::Detector
