#include "G4ChordFinder.hh"
#include "G4Exception.hh"
#include "G4FieldManager.hh"

namespace MACE::Core::Geometry {

template<std::derived_from<G4Field> FieldT, std::derived_from<G4EquationOfMotion> EquationT, class StepperT, std::derived_from<G4VIntegrationDriver> DriverT>
void IEntity::RegisterField(size_t volumeIndex, FieldT* field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const {
    auto logicalVolume = GetLogicalVolume(volumeIndex);
    auto DoRegistration = [&field, &hMin, &nVal, &logicalVolume, &propagateToDescendants] {
        auto equation = new EquationT(field);
        auto stepper = new StepperT(equation, nVal);
        auto driver = new DriverT(hMin, stepper, nVal);
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

template<std::derived_from<G4Field> FieldT, std::derived_from<G4EquationOfMotion> EquationT, class StepperT, std::derived_from<G4VIntegrationDriver> DriverT>
void IEntity::RegisterField(FieldT* field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const {
    for (size_t i = 0; i < GetLogicalVolumeNum(); ++i) {
        RegisterField<FieldT, EquationT, StepperT, DriverT>(i, field, hMin, nVal, propagateToDescendants);
    }
}

template<std::derived_from<G4VSolid> SolidT, typename... Args>
ObserverPtr<SolidT> IEntity::Make(Args&&... args) {
    auto solid = new SolidT(std::forward<Args>(args)...);
    fSolidStore.emplace_back(static_cast<G4VSolid*>(solid));
    return solid;
}

template<std::derived_from<G4LogicalVolume> LogicalT, typename... Args>
ObserverPtr<LogicalT> IEntity::Make(Args&&... args) {
    auto logic = new LogicalT(std::forward<Args>(args)...);
    fLogicalVolumes.emplace_back(static_cast<G4LogicalVolume*>(logic));
    return logic;
}

template<std::derived_from<G4VPhysicalVolume> PhysicalT, typename... Args>
ObserverPtr<PhysicalT> IEntity::Make(Args&&... args) {
    auto physics = new PhysicalT(std::forward<Args>(args)...);
    fPhysicalVolumes.emplace_back(static_cast<G4VPhysicalVolume*>(physics));
    return physics;
}

} // namespace MACE::Core::Geometry
