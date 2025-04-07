#pragma once

#include "Mustard/Detector/Description/DescriptionWithCacheBase.h++"

#include "G4Transform3D.hh"

#include "muc/array"

#include <vector>
namespace MACE::Detector::Description {

class PDSVeto final : public Mustard::Detector::Description::DescriptionWithCacheBase<PDSVeto> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    PDSVeto();
    ~PDSVeto() = default;

public:
    auto NModuleOfACategory() const -> const auto& { return *fNModuleOfACategory; }
    auto NLayerPerModuleOfACategory() const -> const auto& { return *fNLayerPerModuleOfACategory; }
    auto NStripPerLayerOfACategory() const -> const auto& { return *fNStripPerLayerOfACategory; }
    auto StripLengthOfACategory() const -> const auto& { return *fStripLengthOfACategory; }
    auto ReflectiveFilmThickness() const -> const auto& { return *fReflectiveFilmThickness; }
    auto InterPSGap() const -> const auto& { return *fInterPSGap; }
    auto PerpendicularModuleGap() const -> const auto& { return *fPerpendicularModuleGap; }
    auto ParallelModuleGap() const -> const auto& { return *fParallelModuleGap; }
    auto ModuleOffset() const -> const auto& { return *fModuleOffset; }
    auto AlAbsorberThickness() const -> const auto& { return *fAlAbsorberThickness; }
    auto FiberNum() const -> const auto& { return *fFiberNum; }
    auto SelectedCategory() const -> const auto& { return *fSelectedCategory; }

    auto PSScintillationEnergyBin() const -> const auto& { return *fPSScintillationEnergyBin; }
    auto PSScintillationComponent1() const -> const auto& { return *fPSScintillationComponent1; }
    auto PSScintillationYield() const -> const auto& { return *fPSScintillationYield; }
    auto PSScintillationTimeConstant1() const -> const auto& { return *fPSScintillationTimeConstant1; }
    auto PSResolutionScale() const -> const auto& { return *fPSResolutionScale; }

    auto PSWidth() const -> const auto& { return *fPSWidth; }
    auto PSThickness() const -> const auto& { return *fPSThickness; }
    auto SiPMThickness() const -> const auto& { return *fSiPMThickness; }
    auto SiPMCathodeThickness() const -> const auto& { return *fSiPMCathodeThickness; }
    auto SiPMCouplerThickness() const -> const auto& { return *fSiPMCouplerThickness; }
    auto SiPMSize() const -> const auto& { return *fSiPMSize; }
    auto SiPMEnergyBin() const -> const auto& { return *fSiPMEnergyBin; }
    auto SiPMEfficiency() const -> const auto& { return *fSiPMEfficiency; }

    auto PSFiberRadius() const -> const auto& { return *fPSFiberRadius; }
    auto PSHoleRadius() const -> const auto& { return *fPSHoleRadius; }
    auto WLSRIndexEnergy() const -> const auto& { return *fWLSRIndexEnergy; }
    auto WLSRIndex() const -> const auto& { return *fWLSRIndex; }
    auto WLSVAbsEnergy() const -> const auto& { return *fWLSVAbsEnergy; }
    auto WLSVAbsLength() const -> const auto& { return *fWLSVAbsLength; }
    auto WLSAbsEnergy() const -> const auto& { return *fWLSAbsEnergy; }
    auto WLSAbsLength() const -> const auto& { return *fWLSAbsLength; }
    auto WLSEmissionEnergy() const -> const auto& { return *fWLSEmissionEnergy; }
    auto WLSEmissionAmplitude() const -> const auto& { return *fWLSEmissionAmplitude; }

    auto CategoryConfiguration() const -> const auto& { return *fCategoryConfiguration; }
    auto StripInformation() const -> const auto& { return *fStripInformation; }
    auto StartingStripIDOfAModule() const -> const auto& { return *fStartingStripIDOfAModule; }

public:
    struct CategoryConfigurationType {
        struct ModuleConfiguration {
            struct AlLayerConfiguration {
                int layerID;
                int layerLocalID;
                // G4Transform3D layerLocalTransform;
                G4Transform3D alAbsorberLocalTransform;
            };
            struct StripConfiguration {
                int stripID;
                int stripLocalID;
                G4Transform3D stripLocalTransform;
            };
            int moduleID;
            int moduleLocalID;
            G4Transform3D moduleTransform;
            std::vector<AlLayerConfiguration> alLayers;
            std::vector<StripConfiguration> strips;
        };
        int categoryID;
        double moduleLength;
        double moduleWidth;
        double moduleThickness;
        std::vector<ModuleConfiguration> modules;
    };

    struct StripInformationType {
        int stripID;
        int stripLocalID;
        int layerID;
        int layerLocalID;
        int moduleID;
        int moduleLocalID;
        int categoryID;
        double stripLength;
        // muc::array3d stripLocation;
        muc::array3d readDirection;
    };

private:
    auto CalculateCategoryConfiguration() const -> std::vector<CategoryConfigurationType>;
    auto CalculateStripInformation() const -> std::vector<StripInformationType>;
    auto CalculateStartingStripIDOfAModule() const -> std::vector<short>;

    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    // Geometry
    Simple<std::vector<int>> fNModuleOfACategory; // top 1, side 2 , cap1 4 , cap2 4
    Simple<std::vector<int>> fNLayerPerModuleOfACategory;
    Simple<std::vector<int>> fNStripPerLayerOfACategory;
    Simple<std::vector<double>> fStripLengthOfACategory;

    // Simple<double> fPSFiberCurvatureRadius; //

    Simple<double> fPSWidth;
    Simple<double> fPSThickness;
    Simple<std::vector<double>> fPSScintillationEnergyBin;
    Simple<std::vector<double>> fPSScintillationComponent1;
    Simple<double> fPSScintillationYield;
    Simple<double> fPSScintillationTimeConstant1;
    Simple<double> fPSResolutionScale;

    Simple<double> fSiPMThickness;
    Simple<double> fSiPMCathodeThickness;
    Simple<double> fSiPMCouplerThickness;
    Simple<double> fSiPMSize;
    Simple<std::vector<double>> fSiPMEnergyBin;
    Simple<std::vector<double>> fSiPMEfficiency;

    Simple<double> fPSFiberRadius;
    Simple<double> fPSHoleRadius;
    Simple<std::vector<double>> fWLSRIndexEnergy;
    Simple<std::vector<double>> fWLSRIndex;
    Simple<std::vector<double>> fWLSVAbsEnergy;
    Simple<std::vector<double>> fWLSVAbsLength;
    Simple<std::vector<double>> fWLSAbsEnergy;
    Simple<std::vector<double>> fWLSAbsLength;
    Simple<std::vector<double>> fWLSEmissionEnergy;
    Simple<std::vector<double>> fWLSEmissionAmplitude;

    Simple<double> fInterPSGap;
    Simple<double> fPerpendicularModuleGap;
    Simple<double> fParallelModuleGap;
    Simple<double> fModuleOffset;
    Simple<double> fAlAbsorberThickness;
    Simple<double> fReflectiveFilmThickness;
    Simple<double> fSolenoidWindowRadius;
    Simple<int> fFiberNum;
    Simple<int> fSelectedCategory;

    Cached<std::vector<CategoryConfigurationType>> fCategoryConfiguration;
    Cached<std::vector<StripInformationType>> fStripInformation;
    Cached<std::vector<short>> fStartingStripIDOfAModule;
    // Cached<std::vector<double>> fModuleLengthOfaCategory;
};

} // namespace MACE::Detector::Description
