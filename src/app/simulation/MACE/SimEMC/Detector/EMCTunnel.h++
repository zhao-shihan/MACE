#pragma once

#include "MACE/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimEMC::Detector {

class EMCTunnel final : public MACE::Detector::Definition::DefinitionBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::SimEMC::Detector
