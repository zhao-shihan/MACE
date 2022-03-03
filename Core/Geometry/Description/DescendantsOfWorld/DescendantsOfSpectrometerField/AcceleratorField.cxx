#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"

using namespace MACE::Geometry::Description;

AcceleratorField& AcceleratorField::Instance() noexcept {
    static AcceleratorField instance;
    return instance;
}

G4Transform3D AcceleratorField::GetTransform() const {
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, 0, fDownStreamLength - fLength / 2));
}
