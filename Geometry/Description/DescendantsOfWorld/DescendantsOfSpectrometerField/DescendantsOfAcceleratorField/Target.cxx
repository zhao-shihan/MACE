#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hxx"

using namespace MACE::Geometry::Description;

Target& Target::Instance() noexcept {
    static Target instance;
    return instance;
}

G4Transform3D Target::GetTransform() const {
    const auto& acceleratorField = AcceleratorField::Instance();
    auto transZ = acceleratorField.GetLength() / 2 - acceleratorField.GetDownStreamLength() - fThickness / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, 0, transZ));
}
