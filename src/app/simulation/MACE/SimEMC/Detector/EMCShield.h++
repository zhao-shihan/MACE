#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimEMC::Detector {

class EMCShield final : public MACE::Detector::Definition::DefinitionBase {
private:
    auto Construct(G4bool checkOverlaps) -> void override;
};

} // namespace MACE::SimEMC::Detector
