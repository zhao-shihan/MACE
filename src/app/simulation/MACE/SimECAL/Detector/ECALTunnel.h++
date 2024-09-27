#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::SimECAL::Detector {

class ECALTunnel final : public Mustard::Detector::Definition::DefinitionBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::SimECAL::Detector
