#include "Geometry/Description/CalorimeterField.hxx"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

using MACE::Geometry::Description::CalorimeterField;

CalorimeterField& CalorimeterField::Instance() noexcept {
    static CalorimeterField instance;
    return instance;
}

G4Transform3D MACE::Geometry::Description::CalorimeterField::GetTransform() const {
    auto&& thirdTransportField = ThirdTransportField::Instance();
    auto transX = thirdTransportField.GetTransform().dx();
    auto transY = thirdTransportField.GetTransform().dy();
    auto transZ = thirdTransportField.GetTransform().dz() + thirdTransportField.GetLength() / 2 + fLength / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(transX, transY, transZ));
}
