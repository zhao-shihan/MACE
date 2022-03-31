#include "Core/Geometry/Description/AcceleratorField.hxx"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

using MACE::Core::Geometry::Description::AcceleratorField;

AcceleratorField& AcceleratorField::Instance() noexcept {
    static AcceleratorField instance;
    return instance;
}

G4Transform3D AcceleratorField::GetTransform() const {
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, 0, fDownStreamLength - fLength / 2));
}
