#include "Core/Geometry/Description/SpectrometerField.hxx"
#include "Core/Geometry/Description/TransportLine.hxx"
#include "Utility/LiteralUnit.hxx"
#include "Utility/PhysicalConstant.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;
using namespace Utility::PhysicalConstant;

TransportLine& TransportLine::Instance() noexcept {
    static TransportLine instance;
    return instance;
}

TransportLine::TransportLine() :
    IDescription("TransportLine"),
    fFirstStraightLength(20_cm),
    fFirstBendRadius(50_cm),
    fSecondStraightLength(100_cm),
    fSecondBendRadius(50_cm),
    fThirdStraightLength(20_cm),
    fSolenoidInnerRadius(7.5_cm),
    fSolenoidOuterRadius(12.5_cm),
    fFieldRadius(12.6_cm) {}

G4Transform3D TransportLine::FirstStraightTransform() const {
    const auto& spectrometerField = SpectrometerField::Instance();
    const auto transX = 0;
    const auto transY = 0;
    const auto transZ = spectrometerField.GetLength() / 2 + fFirstStraightLength / 2;
    return G4Transform3D(G4RotationMatrix(),
                         G4ThreeVector(transX, transY, transZ));
}

G4Transform3D TransportLine::FirstBendTransform() const {
    const auto localTransX = fFirstBendRadius;
    const auto localTransY = 0;
    const auto localTransZ = fFirstStraightLength / 2;
    const auto translation = FirstStraightTransform().getTranslation() +
                             G4ThreeVector(localTransX, localTransY, localTransZ);
    return G4Transform3D(G4RotationMatrix(CLHEP::HepXHat, halfpi), translation);
}

G4Transform3D TransportLine::SecondStraightTransform() const {
    const auto localTransX = fSecondStraightLength / 2;
    const auto localTransY = 0;
    const auto localTransZ = fFirstBendRadius;
    const auto translation = FirstBendTransform().getTranslation() +
                             G4ThreeVector(localTransX, localTransY, localTransZ);
    return G4Transform3D(G4RotationMatrix(CLHEP::HepYHat, halfpi), translation);
}

G4Transform3D TransportLine::SecondBendTransform() const {
    const auto localTransX = fSecondStraightLength / 2;
    const auto localTransY = 0;
    const auto localTransZ = fSecondBendRadius;
    const auto translation = SecondStraightTransform().getTranslation() +
                             G4ThreeVector(localTransX, localTransY, localTransZ);
    return G4Transform3D(G4RotationMatrix(CLHEP::HepXHat, halfpi), translation);
}

G4Transform3D TransportLine::ThirdStraightTransform() const {
    auto localTransX = fSecondBendRadius;
    auto localTransY = 0;
    auto localTransZ = fThirdStraightLength / 2;
    const auto translation = SecondBendTransform().getTranslation() +
                             G4ThreeVector(localTransX, localTransY, localTransZ);
    return G4Transform3D(G4RotationMatrix(), translation);
}

} // namespace MACE::Core::Geometry::Description
