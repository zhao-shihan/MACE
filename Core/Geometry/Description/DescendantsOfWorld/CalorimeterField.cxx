#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "Geometry/Description/DescendantsOfWorld/CalorimeterField.hxx"

using namespace MACE::Geometry::Description;

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
