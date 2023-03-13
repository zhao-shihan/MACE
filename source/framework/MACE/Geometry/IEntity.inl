namespace MACE::Geometry {

template<std::derived_from<IEntity> AEntity>
AEntity& IEntity::NewDaughter(G4bool checkOverlaps) {
    if (typeid(AEntity) == typeid(*this)) {
        throw std::logic_error("Trying to add the same entity to itself as a daughter");
    }

    const auto [iterator, emplaced] = fDaughters.try_emplace(typeid(AEntity), std::make_unique_for_overwrite<AEntity>());
    if (not emplaced) {
        throw std::logic_error("Trying to add the same entity twice to the same mother");
    }
    const auto& daughter = iterator->second;
    daughter->fMother = *this;

    if (IsTop() and Enabled()) {
        Construct(checkOverlaps);
    }
    const auto hasEnabled = not fLogicalVolumes.empty();
    if (hasEnabled and daughter->Enabled()) {
        daughter->Construct(checkOverlaps);
    }

    return static_cast<AEntity&>(*daughter);
}

template<std::derived_from<IEntity> AEntity>
std::optional<std::reference_wrapper<AEntity>> IEntity::FindDaughter() const {
    if (const auto existedDaughter = fDaughters.find(typeid(AEntity));
        existedDaughter != fDaughters.cend()) {
        return static_cast<AEntity&>(*existedDaughter->second);
    } else {
        return std::nullopt;
    }
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
void IEntity::RegisterField(gsl::index volumeIndex, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool propagateToDescendants) const {
    const auto& logicalVolume = LogicalVolume(volumeIndex);
    const auto equation = new AEquation(field);
    const auto stepper =
        [&equation, &nVarStepper] {
            if constexpr (requires { AStepper(equation, nVarStepper); }) {
                return new AStepper(equation, nVarStepper);
            } else {
                return new AStepper(equation);
            }
        }();
    const auto driver = new ADriver(hMin, stepper, nVarDriver);
    const auto chordFinder = new G4ChordFinder(driver);
    logicalVolume->SetFieldManager(new G4FieldManager(field, chordFinder), propagateToDescendants);
    // if (logicalVolume->GetFieldManager() == nullptr) {
    //     DoRegistration();
    // } else if (logicalVolume->GetFieldManager()->GetDetectorField() != field) {
    //     DoRegistration();
    // } else {
    //     G4ExceptionDescription msg;
    //     msg << "Attempting to register the same field multiple times for \"" << logicalVolume->GetName() << "\", skipping.";
    //     G4Exception("MACE::Geometry::IEntity::RegisterSD", "-1", JustWarning, msg);
    // }
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
void IEntity::RegisterField(gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool propagateToDescendants) const {
    for (gsl::index i = 0; i < std::ssize(fLogicalVolumes); ++i) {
        RegisterField<AField, AEquation, AStepper, ADriver>(i, field, hMin, nVarStepper, nVarDriver, propagateToDescendants);
    }
}

template<std::derived_from<G4VSolid> ASolid>
ASolid* IEntity::Make(auto&&... args) {
    const auto solid = new ASolid(std::forward<decltype(args)>(args)...);
    fSolidStore.emplace_back(solid);
    return solid;
}

template<std::derived_from<G4LogicalVolume> ALogical>
ALogical* IEntity::Make(auto&&... args) {
    const auto logic = new ALogical(std::forward<decltype(args)>(args)...);
    fLogicalVolumes.emplace_back(logic);
    return logic;
}

template<std::derived_from<G4VPhysicalVolume> APhysical>
APhysical* IEntity::Make(auto&&... args) {
    const auto physics = new APhysical(std::forward<decltype(args)>(args)...);
    fPhysicalVolumes.emplace_back(physics);
    return physics;
}

} // namespace MACE::Geometry
