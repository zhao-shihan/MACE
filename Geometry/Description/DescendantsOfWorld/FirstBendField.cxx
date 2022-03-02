#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "Geometry/Description/DescendantsOfWorld/FirstBendField.hxx"

using namespace MACE::Geometry::Description;

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
