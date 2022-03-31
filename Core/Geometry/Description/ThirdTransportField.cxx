#include "Core/Geometry/Description/ThirdTransportField.hxx"
#include "Utility/LiteralUnit.hxx"

#include "G4RotationMatrix.hh"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

ThirdTransportField& ThirdTransportField::Instance() noexcept {
    static ThirdTransportField instance;
    return instance;
}

ThirdTransportField::ThirdTransportField() :
    IDescription("ThirdTransportField"),
    fLength(20_cm) {}

G4Transform3D ThirdTransportField::GetTransform() const {
    auto&& secondBendField = SecondBendField::Instance();
    auto transX = secondBendField.GetTransform().dx() + secondBendField.GetBendRadius();
    auto transY = secondBendField.GetTransform().dy();
    auto transZ = secondBendField.GetTransform().dz() + fLength / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(transX, transY, transZ));
}

} // namespace MACE::Core::Geometry::Description
