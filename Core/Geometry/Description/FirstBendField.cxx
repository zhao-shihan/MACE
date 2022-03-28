#include "Core/Geometry/Description/FirstBendField.hxx"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

using MACE::Geometry::Description::FirstBendField;

FirstBendField& FirstBendField::Instance() noexcept {
    static FirstBendField instance;
    return instance;
}

G4Transform3D FirstBendField::GetTransform() const {
    auto&& firstTransportField = FirstTransportField::Instance();
    auto transX = firstTransportField.GetTransform().dx() + fBendRadius;
    auto transY = firstTransportField.GetTransform().dy();
    auto transZ = firstTransportField.GetTransform().dz() + firstTransportField.GetLength() / 2;
    return G4Transform3D(G4RotationMatrix(G4ThreeVector(1, 0, 0), M_PI_2), G4ThreeVector(transX, transY, transZ));
}
