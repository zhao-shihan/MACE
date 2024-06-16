#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimEMC::Detector {

class EMCTunnel final : public Mustard::Detector::Definition::DefinitionBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::SimEMC::Detector
