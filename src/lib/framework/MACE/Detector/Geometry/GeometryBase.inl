namespace MACE::Detector::Geometry {

template<std::derived_from<GeometryBase> AGeometry>
auto GeometryBase::NewDaughter(G4bool checkOverlaps) -> AGeometry& {
    if (typeid(AGeometry) == typeid(*this)) {
        throw std::logic_error("MACE::Detector::Geometry::GeometryBase::AddDaughter: "
                               "Trying to add the same geometry to itself as a daughter");
    }

    const auto [iterator, emplaced] = fDaughters.try_emplace(typeid(AGeometry), std::make_unique_for_overwrite<AGeometry>());
    if (not emplaced) {
        throw std::logic_error("MACE::Detector::Geometry::GeometryBase::AddDaughter: "
                               "Trying to add the same geometry to itself as a daughter");
    }
    const auto& daughter = iterator->second;
    daughter->fMother = *this;

    if (Topmost() and Enabled()) {
        Construct(checkOverlaps);
    }
    const auto hasEnabled = not fLogicalVolumes.empty();
    if (hasEnabled and daughter->Enabled()) {
        daughter->Construct(checkOverlaps);
    }

    return static_cast<AGeometry&>(*daughter);
}

template<std::derived_from<GeometryBase> AGeometry>
auto GeometryBase::FindDaughter() const -> std::optional<std::reference_wrapper<AGeometry>> {
    if (const auto existedDaughter = fDaughters.find(typeid(AGeometry));
        existedDaughter != fDaughters.cend()) {
        return static_cast<AGeometry&>(*existedDaughter->second);
    } else {
        return std::nullopt;
    }
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
auto GeometryBase::RegisterField(gsl::index volumeIndex, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void {
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
    logicalVolume->SetFieldManager(new G4FieldManager(field, chordFinder), forceToAllDaughters);
    // if (logicalVolume->GetFieldManager() == nullptr) {
    //     DoRegistration();
    // } else if (logicalVolume->GetFieldManager()->GetDetectorField() != field) {
    //     DoRegistration();
    // } else {
    //     G4ExceptionDescription msg;
    //     msg << "Attempting to register the same field multiple times for \"" << logicalVolume->GetName() << "\", skipping.";
    //     G4Exception("MACE::Geometry::EntityBase::RegisterSD", "-1", JustWarning, msg);
    // }
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
auto GeometryBase::RegisterField(std::string_view logicalVolumeName, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void {
    for (gsl::index i{}; i < ssize(fLogicalVolumes); ++i) {
        if (fLogicalVolumes[i]->GetName() == logicalVolumeName) {
            RegisterField<AField, AEquation, AStepper, ADriver>(i, field, hMin, nVarStepper, nVarDriver, forceToAllDaughters);
        }
    }
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
auto GeometryBase::RegisterField(gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void {
    if (fLogicalVolumes.empty()) {
        std::logic_error{"MACE::Detector::Geometry::GeometryBase::RegisterField: "
                         "No logical volumes (may be you forget to construct geometry, or did not construct volumes with GeometryBase::Make?)"};
    }
    for (gsl::index i = 0; i < std::ssize(fLogicalVolumes); ++i) {
        RegisterField<AField, AEquation, AStepper, ADriver>(i, field, hMin, nVarStepper, nVarDriver, forceToAllDaughters);
    }
}

template<std::derived_from<G4VSolid> ASolid>
ASolid* GeometryBase::Make(auto&&... args) {
    const auto solid = new ASolid(std::forward<decltype(args)>(args)...);
    fSolidStore.emplace_back(solid);
    return solid;
}

template<std::derived_from<G4LogicalVolume> ALogical>
ALogical* GeometryBase::Make(auto&&... args) {
    const auto logic = new ALogical(std::forward<decltype(args)>(args)...);
    fLogicalVolumes.emplace_back(logic);
    return logic;
}

template<std::derived_from<G4VPhysicalVolume> APhysical>
APhysical* GeometryBase::Make(auto&&... args) {
    const auto physics = new APhysical(std::forward<decltype(args)>(args)...);
    fPhysicalVolumes.emplace_back(physics);
    return physics;
}

} // namespace MACE::Detector::Geometry
