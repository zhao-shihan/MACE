#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::Detector::Definition {

class PDSVeto final : public Mustard::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
    auto DefineMaterial() -> void;
    auto ConstructLV() -> void;

private:
    G4Material* fAir;
    G4Material* fPlasticScintillaor;
    G4Material* fEpoxy;
    G4Material* fSiliconeGrease;
    G4Material* fSilicon;
    G4Material* fAl;
    G4Material* fWlsPS;
    G4Material* fFP;
    G4Material* fPMMA;
};

} // namespace MACE::Detector::Definition
