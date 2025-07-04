#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Vector/ThreeVector.h"

#include "muc/array"
#include "muc/hash_map"

#include <vector>
#include <unordered_set>
#include "gsl/gsl"

namespace MACE::Detector::Description {

class ECAL final : public Mustard::Detector::Description::DescriptionBase<ECAL> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    ECAL();
    ~ECAL() = default;

public:
    auto NSubdivision() const -> auto { return fNSubdivision; }
    auto InnerRadius() const -> auto { return fInnerRadius; }
    auto CrystalHypotenuse() const -> auto { return fCrystalHypotenuse; }
    auto CrystalPackageThickness() const -> auto { return fCrystalPackageThickness; }
    auto UpstreamWindowRadius() const -> auto { return fUpstreamWindowRadius; }
    auto DownstreamWindowRadius() const -> auto { return fDownstreamWindowRadius; }
    auto ScintillationEnergyBin() const -> const auto& { return fScintillationEnergyBin; }
    auto ScintillationComponent1() const -> const auto& { return fScintillationComponent1; }
    auto ScintillationYield() const -> auto { return fScintillationYield; }
    auto ScintillationTimeConstant1() const -> auto { return fScintillationTimeConstant1; }
    auto ResolutionScale() const -> auto { return fResolutionScale; }

    auto UseMPPC() const -> auto { return fUseMPPC; }

    auto PMTDimensions() const -> const auto& { return fPMTDimensions; }
    auto PMTCouplerThickness() const -> auto { return fPMTCouplerThickness; }
    auto PMTWindowThickness() const -> auto { return fPMTWindowThickness; }
    auto PMTCathodeThickness() const -> auto { return fPMTCathodeThickness; }
    auto PMTEnergyBin() const -> const auto& { return fPMTEnergyBin; }
    auto PMTQuantumEfficiency() const -> const auto& { return fPMTQuantumEfficiency; }

    auto MPPCNPixelRows() const -> const auto& { return fMPPCNPixelRows; }
    auto MPPCPixelSizeSet() const -> const auto& { return fMPPCPixelSizeSet; }
    auto MPPCPitch() const -> auto { return fMPPCPitch; }
    auto MPPCThickness() const -> auto { return fMPPCThickness; }
    auto MPPCCouplerThickness() const -> auto { return fMPPCCouplerThickness; }
    auto MPPCWindowThickness() const -> auto { return fMPPCWindowThickness; }
    auto MPPCEnergyBin() const -> const auto& { return fMPPCEnergyBin; }
    auto MPPCEfficiency() const -> const auto& { return fMPPCEfficiency; }

    auto Mesh() const -> const auto& { return fMeshManager.Get(this); }
    auto NUnit() const -> auto { return Mesh().fFaceList.size(); }
    auto ComputeTransformToOuterSurfaceWithOffset(int cellID, double offsetInNormalDirection) const -> HepGeom::Transform3D;

    auto ModuleSelection() const -> const auto& { return fModuleSelection; }
    auto WaveformIntegralTime() const -> auto { return fWaveformIntegralTime; }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    auto NSubdivision(int val) -> void { fNSubdivision = val, SetGeometryOutdated(); }
    auto InnerRadius(double val) -> void { fInnerRadius = val, SetGeometryOutdated(); }
    auto CrystalHypotenuse(double val) -> void { fCrystalHypotenuse = val, SetGeometryOutdated(); }
    auto CrystalPackageThickness(double val) -> void { fCrystalPackageThickness = val, SetGeometryOutdated(); }
    auto UpstreamWindowRadius(double val) -> void { fUpstreamWindowRadius = val, SetGeometryOutdated(); }
    auto DownstreamWindowRadius(double val) -> void { fDownstreamWindowRadius = val, SetGeometryOutdated(); }
    auto ScintillationEnergyBin(std::vector<double> val) -> void { fScintillationEnergyBin = std::move(val); }
    auto ScintillationComponent1(std::vector<double> val) -> void { fScintillationComponent1 = std::move(val); }
    auto ScintillationYield(double val) -> void { fScintillationYield = val; }
    auto ScintillationTimeConstant1(double val) -> void { fScintillationTimeConstant1 = val; }
    auto ResolutionScale(double val) -> void { fResolutionScale = val; }

    auto UseMPPC(bool val) -> void { fUseMPPC = val; }

    auto PMTDimensions(std::vector<muc::array3d> val) -> void { fPMTDimensions = std::move(val); }
    auto PMTCouplerThickness(double val) -> void { fPMTCouplerThickness = val; }
    auto PMTWindowThickness(double val) -> void { fPMTWindowThickness = val; }
    auto PMTCathodeThickness(double val) -> void { fPMTCathodeThickness = val; }
    auto PMTEnergyBin(std::vector<double> val) -> void { fPMTEnergyBin = std::move(val); }
    auto PMTQuantumEfficiency(std::vector<double> val) -> void { fPMTQuantumEfficiency = std::move(val); }

    auto MPPCNPixelRows(std::vector<int> val) -> void { fMPPCNPixelRows = std::move(val); }
    auto MPPCPixelSizeSet(std::vector<double> val) -> void { fMPPCPixelSizeSet = std::move(val); }
    auto MPPCPitch(double val) -> void { fMPPCPitch = val; }
    auto MPPCThickness(double val) -> void { fMPPCThickness = val; }
    auto MPPCCouplerThickness(double val) -> void { fMPPCCouplerThickness = val; }
    auto MPPCWindowThickness(double val) -> void { fMPPCWindowThickness = val; }
    auto MPPCEnergyBin(std::vector<double> val) -> void { fMPPCEnergyBin = std::move(val); }
    auto MPPCEfficiency(std::vector<double> val) -> void { fMPPCEfficiency = std::move(val); }

    auto ModuleSelection(std::vector<int> val) { fModuleSelection = std::move(val); }
    auto WaveformIntegralTime(double val) { fWaveformIntegralTime = val; }

    struct MeshInformation {
        struct Module {
            CLHEP::Hep3Vector centroid;
            CLHEP::Hep3Vector normal;
            std::vector<gsl::index> vertexIndex;
            int typeID;
            std::unordered_set<int> neighborModuleID;            
        };
        std::vector<HepGeom::Point3D<double>> vertexList;
        std::vector<Module> faceList;
        // std::vector<int> typeMap; // moduleID -> typeID
        // std::vector<std::vector<int>> clusterMap; // moduleID -> neighbor moduleIDs
    };

private:
    class MeshManager {
    public:
        auto SetOutdated() -> void { fOutdated = true; }
        auto Get(const ECAL* ecal) -> const MeshInformation&;

    private:
        bool fOutdated = true;
        MeshInformation fMesh;
    };

    inline auto SetGeometryOutdated() const -> void;
    auto ComputeMesh() const -> MeshInformation;

    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    int fNSubdivision;
    double fInnerRadius;
    double fCrystalHypotenuse;
    double fCrystalPackageThickness;
    double fUpstreamWindowRadius;
    double fDownstreamWindowRadius;
    std::vector<double> fScintillationEnergyBin;
    std::vector<double> fScintillationComponent1;
    double fScintillationYield;
    double fScintillationTimeConstant1;
    double fResolutionScale;

    bool fUseMPPC;

    std::vector<muc::array3d> fPMTDimensions;
    double fPMTCouplerThickness;
    double fPMTWindowThickness;
    double fPMTCathodeThickness;
    std::vector<double> fPMTEnergyBin;
    std::vector<double> fPMTQuantumEfficiency;

    std::vector<int> fMPPCNPixelRows;
    std::vector<double> fMPPCPixelSizeSet;
    double fMPPCPitch;
    double fMPPCThickness;
    double fMPPCCouplerThickness;
    double fMPPCWindowThickness;
    std::vector<double> fMPPCEnergyBin;
    std::vector<double> fMPPCEfficiency;
    
    mutable MeshManager fMeshManager;

    std::vector<int> fModuleSelection;
    double fWaveformIntegralTime;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/ECAL.inl"
