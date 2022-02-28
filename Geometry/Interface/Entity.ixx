#include "G4Exception.hh"

namespace MACE::Geometry::Interface {

    template<class Field_t, class Equation_t, class Stepper_t, class Driver_t>
    void Entity::RegisterField(size_t volumeIndex, Field_t* field, G4double hMin, G4int nVal) const {
        auto logicalVolume = GetLogicalVolume(volumeIndex);
        if (logicalVolume->GetFieldManager() == nullptr) {
            auto equation = new Equation_t(field);
            auto stepper = new Stepper_t(equation, nVal);
            auto driver = new Driver_t(hMin, stepper, nVal);
            auto chordFinder = new G4ChordFinder(driver);
            logicalVolume->SetFieldManager(new G4FieldManager(field, chordFinder), true);
        } else if (logicalVolume->GetFieldManager()->GetDetectorField() != field) {
            G4ExceptionDescription msg;
            msg << "Attempting to register field multiple times for \"" << logicalVolume->GetName() << "\" is not allowed, skipping.";
            G4Exception("MACE::Geometry::Interface::Entity::RegisterField", "-1", JustWarning, msg);
        }
    }

    template<class Field_t, class Equation_t, class Stepper_t, class Driver_t>
    void Entity::RegisterField(Field_t* field, G4double hMin, G4int nVal) const {
        for (size_t i = 0; i < GetPhysicalVolumeNum(); ++i) {
            RegisterField<Field_t, Equation_t, Stepper_t, Driver_t>(i, field, hMin, nVal);
        }
    }

    template<class Solid_t, typename... Args>
    std::enable_if_t<std::is_base_of_v<G4VSolid, Solid_t>,
        MACE::ObserverPtr<Solid_t>> Entity::Make(Args&&... args) {
        auto solid = new Solid_t(std::forward<Args>(args)...);
        fSolidStore.emplace_back(static_cast<G4VSolid*>(solid));
        return solid;
    }

    template<class Logical_t, typename... Args>
    std::enable_if_t<std::is_base_of_v<G4LogicalVolume, Logical_t>,
        MACE::ObserverPtr<Logical_t>> Entity::Make(Args&&... args) {
        auto logic = new Logical_t(std::forward<Args>(args)...);
        fLogicalVolumeStore.emplace_back(static_cast<G4LogicalVolume*>(logic));
        return logic;
    }

    template<class Physical_t, typename... Args>
    std::enable_if_t<std::is_base_of_v<G4VPhysicalVolume, Physical_t>,
        MACE::ObserverPtr<Physical_t>> Entity::Make(Args&&... args) {
        auto physics = new Physical_t(std::forward<Args>(args)...);
        fPhysicalVolumes.emplace_back(static_cast<G4VPhysicalVolume*>(physics));
        return physics;
    }

}
