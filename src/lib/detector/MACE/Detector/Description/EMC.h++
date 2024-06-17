#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Vector/ThreeVector.h"

#include "muc/array"

#include <vector>

namespace MACE::Detector::Description {

class EMC final : public Mustard::Detector::Description::DescriptionBase<EMC> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    EMC();
    ~EMC() = default;

public:
    auto NSubdivision() const -> auto { return fNSubdivision; }
    auto InnerRadius() const -> auto { return fInnerRadius; }
    auto CrystalHypotenuse() const -> auto { return fCrystalHypotenuse; }
    auto UpstreamWindowRadius() const -> auto { return fUpstreamWindowRadius; }
    auto DownstreamWindowRadius() const -> auto { return fDownstreamWindowRadius; }
    auto PMTDimensions() const -> const auto& { return fPMTDimensions; }
    auto PMTCouplerThickness() const -> auto { return fPMTCouplerThickness; }
    auto PMTWindowThickness() const -> auto { return fPMTWindowThickness; }
    auto PMTCathodeThickness() const -> auto { return fPMTCathodeThickness; }

    auto PMTWaveLengthBin() const -> const auto& { return fPMTWaveLengthBin; }
    auto PMTQuantumEfficiency() const -> const auto& { return fPMTQuantumEfficiency; }
    auto CsIEnergyBin() const -> const auto& { return fCsIEnergyBin; }
    auto CsIScintillationComponent1() const -> const auto& { return fCsIScintillationComponent1; }
    auto ScintillationYield() const -> auto { return fScintillationYield; }
    auto ScintillationTimeConstant1() const -> auto { return fScintillationTimeConstant1; }
    auto ResolutionScale() const -> auto { return fResolutionScale; }

    auto Mesh() const -> const auto& { return fMeshManager.Get(this); }
    auto NUnit() const -> auto { return Mesh().fFaceList.size(); }
    auto ComputeTransformToOuterSurfaceWithOffset(int cellID, double offsetInNormalDirection) const -> HepGeom::Transform3D;

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    auto NSubdivision(int val) -> void { fNSubdivision = val, SetGeometryOutdated(); }
    auto InnerRadius(double val) -> void { fInnerRadius = val, SetGeometryOutdated(); }
    auto CrystalHypotenuse(double val) -> void { fCrystalHypotenuse = val, SetGeometryOutdated(); }
    auto UpstreamWindowRadius(double val) -> void { fUpstreamWindowRadius = val, SetGeometryOutdated(); }
    auto DownstreamWindowRadius(double val) -> void { fDownstreamWindowRadius = val, SetGeometryOutdated(); }
    auto PMTDimensions(std::vector<muc::array3d> val) -> void { fPMTDimensions = std::move(val); }
    auto PMTCouplerThickness(double val) -> void { fPMTCouplerThickness = val; }
    auto PMTWindowThickness(double val) -> void { fPMTWindowThickness = val; }
    auto PMTCathodeThickness(double val) -> void { fPMTCathodeThickness = val; }

    auto PMTWaveLengthBin(std::vector<double> val) -> void { fPMTWaveLengthBin = std::move(val); }
    auto PMTQuantumEfficiency(std::vector<double> val) -> void { fPMTQuantumEfficiency = std::move(val); }
    auto CsIEnergyBin(std::vector<double> val) -> void { fCsIEnergyBin = std::move(val); }
    auto CsIScintillationComponent1(std::vector<double> val) -> void { fCsIScintillationComponent1 = std::move(val); }
    auto ScintillationYield(double val) -> void { fScintillationYield = val; }
    auto ScintillationTimeConstant1(double val) -> void { fScintillationTimeConstant1 = val; }
    auto ResolutionScale(double val) -> void { fResolutionScale = val; }

    struct MeshInformation {
    private:
        struct Face {
            CLHEP::Hep3Vector centroid;
            CLHEP::Hep3Vector normal;
            std::vector<std::ptrdiff_t> vertexIndex;
        };

    public:
        std::vector<HepGeom::Point3D<double>> fVertex;
        std::vector<Face> fFaceList;
        std::map<int, int> fTypeMap;
    };

private:
    class MeshManager {
    public:
        auto SetOutdated() -> void { fOutdated = true; }
        auto Get(const EMC* emc) -> const MeshInformation&;

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
    double fUpstreamWindowRadius;
    double fDownstreamWindowRadius;
    std::vector<stdx::array3d> fPMTDimensions;
    double fPMTCouplerThickness;
    double fPMTWindowThickness;
    double fPMTCathodeThickness;

    std::vector<double> fPMTWaveLengthBin;
    std::vector<double> fPMTQuantumEfficiency;
    std::vector<double> fCsIEnergyBin;
    std::vector<double> fCsIScintillationComponent1;
    double fScintillationYield;
    double fScintillationTimeConstant1;
    double fResolutionScale;

    mutable MeshManager fMeshManager;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/EMC.inl"
