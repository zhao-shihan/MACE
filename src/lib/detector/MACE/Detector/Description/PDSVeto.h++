#pragma once

#include "Mustard/Detector/Description/DescriptionWithCacheBase.h++"

#include <vector>
namespace MACE::Detector::Description {

class PDSVeto final : public Mustard::Detector::Description::DescriptionWithCacheBase<PDSVeto> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    PDSVeto();
    ~PDSVeto() = default;

public:
    auto NModuleOfaType() const -> const auto& { return *fNModuleOfaType; }
    auto NLayerPerModuleOfaType() const -> const auto& { return *fNLayerPerModuleOfaType; }
    auto NStripPerLayerOfaType() const -> const auto& { return *fNStripPerLayerOfaType; }
    auto StripLengthOfaType() const -> const auto& { return *fStripLengthOfaType; }
    auto ReflectiveFilmThickness() const -> const auto& { return *fReflectiveFilmThickness; }
    auto InterPSGap() const -> const auto& { return *fInterPSGap; }
    auto InterModuleGap() const -> const auto& { return *fInterModuleGap; }
    auto Cap12Gap() const -> const auto& { return *fCap12Gap; }
    auto ModuleOffset() const -> const auto& { return *fModuleOffset; }
    auto AlAbsorberThickness() const -> const auto& { return *fAlAbsorberThickness; }
    auto FTypeConfiguration() const -> const auto& {return *fTypeConfiguration;}
    auto FStripInformation() const -> const auto& {return *fStripInformation;}
    auto FiberNum() const -> const auto& {return *fFiberNum;}
    auto SelectedType() const -> const auto& {return *fSelectedType;}

    auto PSScintillationEnergyBin() const -> const auto& {return *fPSScintillationEnergyBin;}
    auto PSScintillationComponent1() const -> const auto& {return *fPSScintillationComponent1;}
    auto PSScintillationYield() const -> const auto& {return *fPSScintillationYield;}
    auto PSScintillationTimeConstant1() const -> const auto& {return *fPSScintillationTimeConstant1;}
    auto PSResolutionScale() const -> const auto& {return *fPSResolutionScale;}

    auto PSWidth() const -> const auto& { return *fPSWidth; }
    auto PSThickness() const -> const auto& { return *fPSThickness; }
    auto SiPMThickness() const -> const auto& { return *fSiPMThickness; }
    auto SiPMCathodeThickness() const -> const auto& { return *fSiPMCathodeThickness; }
    auto SiPMCouplerThickness() const -> const auto& { return *fSiPMCouplerThickness; }
    auto SiPMSize() const -> const auto& { return *fSiPMSize; }
    auto SiPMEnergyBin() const -> const auto& {return *fSiPMEnergyBin;}
    auto SiPMEfficiency() const -> const auto& {return *fSiPMEfficiency;}

    auto PSFiberRadius() const -> const auto& { return *fPSFiberRadius; }
    // auto PSFiberCurvatureRadius() const -> const auto& { return *fPSFiberCurvatureRadius; }
    auto PSHoleRadius() const -> const auto& { return *fPSHoleRadius; }
    auto WlsRIndexEnergy() const -> const auto& {return *fWlsRIndexEnergy;}
    auto WlsRIndex() const -> const auto& {return *fWlsRIndex;}
    auto WlsVAbsEnergy() const -> const auto& {return *fWlsVAbsEnergy;}
    auto WlsVAbsLength() const -> const auto& {return *fWlsVAbsLength;}
    auto WlsAbsEnergy() const -> const auto& {return *fWlsAbsEnergy;}
    auto WlsAbsLength() const -> const auto& {return *fWlsAbsLength;}
    auto WlsEmissionEnergy() const -> const auto& {return *fWlsEmissionEnergy;}
    auto WlsEmissionAmplitude() const -> const auto& {return *fWlsEmissionAmplitude;}



public:
    struct TypeConfiguration {
        struct ModuleConfiguration {
            struct LayerConfiguration {
                struct StripConfiguration {
                    int stripID;
                    int stripLocalID;
                    G4Transform3D stripLocalTranform;
                };
                int layerID;
                int layerLocalID;
                G4Transform3D layerLocalTransform;
                G4Transform3D alAbsorberLocalTransform;
                std::vector<StripConfiguration> strips;
            };
            int moduleID;
            int moduleLocalID;
            G4Transform3D moduleTransform;
            std::vector<LayerConfiguration> layers;
        };
        int typeID;
        double moduleLength;
        double moduleWidth;
        double moduleThickness;
        std::vector<ModuleConfiguration> modules;
    };

    struct StripInformation {
        int stripID;
        int stripLocalID;
        int layerID;
        int layerLocalID;
        int moduleID;
        int moduleLocalID;
        int typeID;
        double stripLength;
        // muc::array3d stripLocation;
        muc::array3d readDirection;
    };

private:
    auto CalculateTypeConfiguration() const -> std::vector<TypeConfiguration>;
    auto CalculateStripInformation() const -> std::vector<StripInformation>;

    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    // Geometry
    Simple<std::vector<int>> fNModuleOfaType; // top 1, side 2 , cap1 4 , cap2 4
    Simple<std::vector<int>> fNLayerPerModuleOfaType;
    Simple<std::vector<int>> fNStripPerLayerOfaType;
    Simple<std::vector<double>> fStripLengthOfaType;

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
    Simple<std::vector<double>> fWlsRIndexEnergy;
    Simple<std::vector<double>> fWlsRIndex;
    Simple<std::vector<double>> fWlsVAbsEnergy;
    Simple<std::vector<double>> fWlsVAbsLength;
    Simple<std::vector<double>> fWlsAbsEnergy;
    Simple<std::vector<double>> fWlsAbsLength;
    Simple<std::vector<double>> fWlsEmissionEnergy;
    Simple<std::vector<double>> fWlsEmissionAmplitude;
    
    Simple<double> fInterPSGap;
    Simple<double> fInterModuleGap;
    Simple<double> fCap12Gap;
    Simple<double> fModuleOffset;
    Simple<double> fAlAbsorberThickness;
    Simple<double> fReflectiveFilmThickness;
    Simple<double> fSolenoidWindowRadius;
    Simple<int> fFiberNum;
    Simple<int> fSelectedType;



    
    

    Cached<std::vector<TypeConfiguration>> fTypeConfiguration;
    Cached<std::vector<StripInformation>> fStripInformation;
    // Cached<std::vector<double>> fModuleLengthOfaType;
};
} // namespace MACE::Detector::Description