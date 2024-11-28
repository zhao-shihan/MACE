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
    //     int fTypeIter;
    //     LVStore fLVStore;
    // };
    auto Construct(bool checkOverlaps) -> void override;
    auto DefineMaterial() -> void;
    auto ConstructLV() -> void;
    // auto ConstructAll(bool checkOverlaps) -> void;
    // auto ConstructSingleStrip(int typeID, bool checkOvelaps) -> void;
    // auto PlaceModuleBox(int moduleID, bool checkOverlaps) -> void;
    // auto PlaceStripBox(int stripID, bool checkOverlaps) -> void;
    // auto PlaceAlAbsorber(int layerID, bool checkOverlaps) -> void;
    // auto PlaceStrips();
private:
    G4Material* fAir;
    G4Material* fPlasticScinllator;
    G4Material* fEpoxy;
    G4Material* fSiliconeGrease;
    G4Material* fSilicon;
    G4Material* fWls;
    G4Material* fAl;
    std::vector<std::string> fTypeNames{"Top","Side","Cap1","Cap2"};
};

} // namespace MACE::Detector::Definition
