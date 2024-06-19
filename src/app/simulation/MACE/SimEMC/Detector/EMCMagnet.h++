#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimEMC::Detector {

class EMCMagnet final : public Mustard::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
};

} // namespace MACE::SimEMC::Detector
