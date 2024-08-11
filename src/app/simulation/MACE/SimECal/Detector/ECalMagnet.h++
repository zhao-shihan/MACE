#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimECal::Detector {

class ECalMagnet final : public Mustard::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
};

} // namespace MACE::SimECal::Detector
