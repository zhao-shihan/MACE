#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "Geometry/Description/DescendantsOfWorld/FirstTransportField.hxx"

using namespace MACE::Geometry::Description;

FirstTransportField& FirstTransportField::Instance() noexcept {
    static FirstTransportField instance;
    return instance;
}

G4Transform3D FirstTransportField::GetTransform() const {
    auto&& spectrometerField = SpectrometerField::Instance();
    auto transX = 0;
    auto transY = 0;
    auto transZ = spectrometerField.GetLength() / 2 + fLength / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(transX, transY, transZ));
}
