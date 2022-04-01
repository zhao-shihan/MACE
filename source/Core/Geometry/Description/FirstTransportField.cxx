#include "Core/Geometry/Description/FirstTransportField.hxx"
#include "Utility/LiteralUnit.hxx"

#include "G4RotationMatrix.hh"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

FirstTransportField& FirstTransportField::Instance() noexcept {
    static FirstTransportField instance;
    return instance;
}

FirstTransportField::FirstTransportField() :
    IDescription("FirstTransportField"),
    fRadius(12.6_cm),
    fLength(20_cm) {}

G4Transform3D FirstTransportField::GetTransform() const {
    auto&& spectrometerField = SpectrometerField::Instance();
    auto transX = 0;
    auto transY = 0;
    auto transZ = spectrometerField.GetLength() / 2 + fLength / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(transX, transY, transZ));
}

} // namespace MACE::Core::Geometry::Description
