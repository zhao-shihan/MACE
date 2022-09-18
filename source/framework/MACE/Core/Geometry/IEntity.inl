#include "G4ChordFinder.hh"
#include "G4Exception.hh"
#include "G4FieldManager.hh"

namespace MACE::Core::Geometry {

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
void IEntity::RegisterField(std::size_t volumeIndex, AField* field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const {
    auto logicalVolume = LogicalVolume(volumeIndex);
    auto DoRegistration = [&field, &hMin, &nVal, &logicalVolume, &propagateToDescendants] {
        auto equation = new AEquation(field);
        auto stepper = new AStepper(equation, nVal);
        auto driver = new ADriver(hMin, stepper, nVal);
        auto chordFinder = new G4ChordFinder(driver);
        logicalVolume->SetFieldManager(new G4FieldManager(field, chordFinder), propagateToDescendants);
    };
    if (logicalVolume->GetFieldManager() == nullptr) {
        DoRegistration();
    } else if (logicalVolume->GetFieldManager()->GetDetectorField() != field) {
        DoRegistration();
    } else {
        G4ExceptionDescription msg;
        msg << "Attempting to register the same field multiple times for \"" << logicalVolume->GetName() << "\", skipping.";
        G4Exception("MACE::Core::Geometry::IEntity::RegisterSD", "-1", JustWarning, msg);
    }
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
void IEntity::RegisterField(AField* field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const {
    for (std::size_t i = 0; i < LogicalVolumeNum(); ++i) {
        RegisterField<AField, AEquation, AStepper, ADriver>(i, field, hMin, nVal, propagateToDescendants);
    }
}

template<std::derived_from<G4VSolid> ASolid, typename... Args>
ObserverPtr<ASolid> IEntity::Make(Args&&... args) {
    auto solid = new ASolid(std::forward<Args>(args)...);
    fSolidStore.emplace_back(static_cast<G4VSolid*>(solid));
    return solid;
}

template<std::derived_from<G4LogicalVolume> ALogical, typename... Args>
ObserverPtr<ALogical> IEntity::Make(Args&&... args) {
    auto logic = new ALogical(std::forward<Args>(args)...);
    fLogicalVolumes.emplace_back(static_cast<G4LogicalVolume*>(logic));
    return logic;
}

template<std::derived_from<G4VPhysicalVolume> APhysical, typename... Args>
ObserverPtr<APhysical> IEntity::Make(Args&&... args) {
    auto physics = new APhysical(std::forward<Args>(args)...);
    fPhysicalVolumes.emplace_back(static_cast<G4VPhysicalVolume*>(physics));
    return physics;
}

} // namespace MACE::Core::Geometry
