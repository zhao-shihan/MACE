#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimEMC::Detector {

class EMCMagnet final : public MACE::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
};

} // namespace MACE::SimEMC::Detector
