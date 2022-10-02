#include "G4ChordFinder.hh"
#include "G4Exception.hh"
#include "G4FieldManager.hh"

namespace MACE::Core::Geometry {

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
void IEntity::RegisterField(gsl::index volumeIndex, gsl::not_null<AField*> field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const {
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
void IEntity::RegisterField(gsl::not_null<AField*> field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const {
    for (gsl::index i = 0; i < LogicalVolumeNum(); ++i) {
        RegisterField<AField, AEquation, AStepper, ADriver>(i, field, hMin, nVal, propagateToDescendants);
    }
}

template<std::derived_from<G4VSolid> ASolid>
gsl::not_null<ASolid*> IEntity::Make(auto&&... args) {
    const auto solid = new ASolid(std::forward<decltype(args)>(args)...);
    fSolidStore.emplace_back(solid);
    return solid;
}

template<std::derived_from<G4LogicalVolume> ALogical>
gsl::not_null<ALogical*> IEntity::Make(auto&&... args) {
    const auto logic = new ALogical(std::forward<decltype(args)>(args)...);
    fLogicalVolumes.emplace_back(logic);
    return logic;
}

template<std::derived_from<G4VPhysicalVolume> APhysical>
gsl::not_null<APhysical*> IEntity::Make(auto&&... args) {
    const auto physics = new APhysical(std::forward<decltype(args)>(args)...);
    fPhysicalVolumes.emplace_back(physics);
    return physics;
}

} // namespace MACE::Core::Geometry
