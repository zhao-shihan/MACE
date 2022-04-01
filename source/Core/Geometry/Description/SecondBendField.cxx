#include "Core/Geometry/Description/SecondBendField.hxx"
#include "Utility/LiteralUnit.hxx"

#include "G4RotationMatrix.hh"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SecondBendField& SecondBendField::Instance() noexcept {
    static SecondBendField instance;
    return instance;
}

SecondBendField::SecondBendField() :
    IDescription("SecondBendField"),
    fBendRadius(50_cm) {}

G4Transform3D SecondBendField::GetTransform() const {
    auto&& secondTransportField = SecondTransportField::Instance();
    auto transX = secondTransportField.GetTransform().dx() + secondTransportField.GetLength() / 2;
    auto transY = secondTransportField.GetTransform().dy();
    auto transZ = secondTransportField.GetTransform().dz() + fBendRadius;
    return G4Transform3D(G4RotationMatrix(G4ThreeVector(1, 0, 0), M_PI_2), G4ThreeVector(transX, transY, transZ));
}

} // namespace MACE::Core::Geometry::Description
