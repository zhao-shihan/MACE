#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::Detector::Definition {

class PDSVeto final : public Mustard::Detector::Definition::DefinitionBase {
public:
    // struct Module {
    //     Module() {};
    //     ~Module() {};
    //     std::string fName;
    //     double fLength;
    //     double fWidth;
    //     double fThickness;
    //     std::vector<G4Transform3D> fTransforms;
    //     int fModuleLayerCount;
    //     int fLayerStripCount;
    //     int fCategoryIter;
    //     LVStore fLVStore;
    // };
    auto Construct(bool checkOverlaps) -> void override;
    auto DefineMaterial() -> void;
    auto ConstructLV() -> void;
    // auto ConstructAll(bool checkOverlaps) -> void;
    // auto ConstructSingleStrip(int categoryID, bool checkOvelaps) -> void;
    // auto PlaceModuleBox(int moduleID, bool checkOverlaps) -> void;
    // auto PlaceStripBox(int stripID, bool checkOverlaps) -> void;
    // auto PlaceAlAbsorber(int layerID, bool checkOverlaps) -> void;
    // auto PlaceStrips();
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
    std::vector<std::string> fCategoryNames{"Top", "Side", "Cap1", "Cap2"};
};

} // namespace MACE::Detector::Definition
