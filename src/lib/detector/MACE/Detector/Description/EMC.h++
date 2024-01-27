#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Vector/ThreeVector.h"

namespace MACE::Detector::Description {

class EMC final : public DescriptionSingletonBase<EMC> {
    friend Env::Memory::SingletonInstantiator;

private:
    EMC();
    ~EMC() = default;

public:
    auto NSubdivision() const -> const auto& { return fNSubdivision; }
    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto CrystalHypotenuse() const -> const auto& { return fCrystalHypotenuse; }
    auto SmallPMTRadius() const -> const auto& { return fSmallPMTRadius; }
    auto SmallPMTLength() const -> const auto& { return fSmallPMTLength; }
    auto SmallPMTCathodeRadius() const -> const auto& { return fSmallPMTCathodeRadius; }
    auto LargePMTRadius() const -> const auto& { return fLargePMTRadius; }
    auto LargePMTCathodeRadius() const -> const auto& { return fLargePMTCathodeRadius; }
    auto LargePMTLength() const -> const auto& { return fLargePMTLength; }
    auto PMTCouplerThickness() const -> const auto& { return fPMTCouplerThickness; }
    auto PMTWindowThickness() const -> const auto& { return fPMTWindowThickness; }
    auto PMTCathodeThickness() const -> const auto& { return fPMTCathodeThickness; }

    auto PMTWaveLengthBin() const -> const auto& { return fPMTWaveLengthBin; }
    auto PMTQuantumEfficiency() const -> const auto& { return fPMTQuantumEfficiency; }
    auto CsIEnergyBin() const -> const auto& { return fCsIEnergyBin; }
    auto CsIScintillationComponent1() const -> const auto& { return fCsIScintillationComponent1; }

    auto ScintillationYield() const -> const auto& { return fScintillationYield; }
    auto ScintillationTimeConstant1() const -> const auto& { return fScintillationTimeConstant1; }
    auto ResolutionScale() const -> const auto& { return fResolutionScale; }

    auto Mesh() const -> const auto& { return fMeshManager.Get(this); }
    auto CellTotalNumber() const -> auto { return Mesh().fFaceList.size(); }
    auto ComputeTransformToOuterSurfaceWithOffset(int cellID, double offsetInNormalDirection) const -> HepGeom::Transform3D;

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    auto NSubdivision(const auto& val) -> void { (fNSubdivision = val, SetGeometryOutdated()); }
    auto InnerRadius(const auto& val) -> void { (fInnerRadius = val, SetGeometryOutdated()); }
    auto CrystalHypotenuse(const auto& val) -> void { (fCrystalHypotenuse = val, SetGeometryOutdated()); }
    auto SmallPMTRadius(const auto& val) -> void { fSmallPMTRadius = val; }
    auto SmallPMTLength(const auto& val) -> void { fSmallPMTLength = val; }
    auto SmallPMTCathodeRadius(const auto& val) -> void { fSmallPMTCathodeRadius = val; }
    auto LargePMTRadius(const auto& val) -> void { fLargePMTRadius = val; }
    auto LargePMTLength(const auto& val) -> void { fLargePMTLength = val; }
    auto LargePMTCathodeRadius(const auto& val) -> void { fLargePMTCathodeRadius = val; }
    auto PMTCouplerThickness(const auto& val) -> void { fPMTCouplerThickness = val; }
    auto PMTWindowThickness(const auto& val) -> void { fPMTWindowThickness = val; }
    auto PMTCathodeThickness(const auto& val) -> void { fPMTCathodeThickness = val; }

    auto PMTWaveLengthBin(const auto& val) -> void { fPMTWaveLengthBin = val; }
    auto PMTQuantumEfficiency(const auto& val) -> void { fPMTQuantumEfficiency = val; }
    auto CsIEnergyBin(const auto& val) -> void { fCsIEnergyBin = val; }
    auto CsIScintillationComponent1(const auto& val) -> void { fCsIScintillationComponent1 = val; }

    auto ScintillationYield(const auto& val) -> void { fScintillationYield = val; }
    auto ScintillationTimeConstant1(const auto& val) -> void { fScintillationTimeConstant1 = val; }
    auto ResolutionScale(const auto& val) -> void { fResolutionScale = val; }

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

    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    int fNSubdivision;
    double fInnerRadius;
    double fCrystalHypotenuse;
    double fSmallPMTRadius;
    double fSmallPMTLength;
    double fSmallPMTCathodeRadius;
    double fLargePMTRadius;
    double fLargePMTLength;
    double fLargePMTCathodeRadius;
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
