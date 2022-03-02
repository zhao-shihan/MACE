#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "Geometry/Description/DescendantsOfWorld/SecondTransportField.hxx"

using namespace MACE::Geometry::Description;

SecondTransportField& SecondTransportField::Instance() noexcept {
    static SecondTransportField instance;
    return instance;
}

G4Transform3D SecondTransportField::GetTransform() const {
    auto&& firstBendField = FirstBendField::Instance();
    auto transX = firstBendField.GetTransform().dx() + fLength / 2;
    auto transY = firstBendField.GetTransform().dy();
    auto transZ = firstBendField.GetTransform().dz() + firstBendField.GetBendRadius();
    return G4Transform3D(G4RotationMatrix(G4ThreeVector(0, 1, 0), M_PI_2), G4ThreeVector(transX, transY, transZ));
}
