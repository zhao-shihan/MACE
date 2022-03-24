#include "Geometry/Description/ThirdTransportField.hxx"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

using MACE::Geometry::Description::ThirdTransportField;

ThirdTransportField& ThirdTransportField::Instance() noexcept {
    static ThirdTransportField instance;
    return instance;
}

G4Transform3D ThirdTransportField::GetTransform() const {
    auto&& secondBendField = SecondBendField::Instance();
    auto transX = secondBendField.GetTransform().dx() + secondBendField.GetBendRadius();
    auto transY = secondBendField.GetTransform().dy();
    auto transZ = secondBendField.GetTransform().dz() + fLength / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(transX, transY, transZ));
}
