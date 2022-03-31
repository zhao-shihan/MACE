#include "Core/Geometry/Description/CalorimeterField.hxx"
#include "Utility/LiteralUnit.hxx"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

CalorimeterField& CalorimeterField::Instance() noexcept {
    static CalorimeterField instance;
    return instance;
}

CalorimeterField::CalorimeterField() :
    IDescription("CalorimeterField"),
    fRadius(25_cm),
    fLength(70_cm) {}

G4Transform3D MACE::Core::Geometry::Description::CalorimeterField::GetTransform() const {
    auto&& thirdTransportField = ThirdTransportField::Instance();
    auto transX = thirdTransportField.GetTransform().dx();
    auto transY = thirdTransportField.GetTransform().dy();
    auto transZ = thirdTransportField.GetTransform().dz() + thirdTransportField.GetLength() / 2 + fLength / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(transX, transY, transZ));
}

} // namespace MACE::Core::Geometry::Description
