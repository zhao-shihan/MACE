namespace MACE::Detector::Geometry {

template<std::derived_from<GeometryBase> AGeometry>
auto GeometryBase::NewDaughter(G4bool checkOverlaps) -> AGeometry& {
    if (typeid(AGeometry) == typeid(*this)) {
        throw std::logic_error("MACE::Detector::Geometry::GeometryBase::AddDaughter: "
                               "Trying to add the same geometry to itself as a daughter");
    }

    const auto [iterator, emplaced]{fDaughters.try_emplace(typeid(AGeometry), std::make_unique_for_overwrite<AGeometry>())};
    if (not emplaced) {
        throw std::logic_error("MACE::Detector::Geometry::GeometryBase::AddDaughter: "
                               "Trying to add the same geometry to itself as a daughter");
    }
    const auto& daughter{iterator->second};
    daughter->fMother = this;

    if (Topmost() and Enabled()) {
        Construct(checkOverlaps);
    }
    if (Ready() and daughter->Enabled()) {
        daughter->Construct(checkOverlaps);
    }

    return static_cast<AGeometry&>(*daughter);
}

template<std::derived_from<GeometryBase> AGeometry>
auto GeometryBase::FindDaughter() const -> AGeometry* {
    if (const auto existedDaughter{fDaughters.find(typeid(AGeometry))};
        existedDaughter != fDaughters.cend()) {
        return static_cast<AGeometry*>(existedDaughter->second.get());
    } else {
        return {};
    }
}

namespace internal {
namespace {

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
auto RegisterField(const std::unique_ptr<G4LogicalVolume>& logic, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) -> void {
    const auto equation{new AEquation{field}};
    const auto stepper{[&equation, &nVarStepper] {
        if constexpr (requires { AStepper{equation, nVarStepper}; }) {
            return new AStepper{equation, nVarStepper};
        } else {
            return new AStepper{equation};
        }
    }()}; // clang-format off
    const auto driver{new ADriver{hMin, stepper, nVarDriver}}; // clang-format on
    const auto chordFinder{new G4ChordFinder{driver}};
    logic->SetFieldManager(new G4FieldManager{field, chordFinder}, forceToAllDaughters);
    // if (logic->GetFieldManager() == nullptr) {
    //     DoRegistration();
    // } else if (logic->GetFieldManager()->GetDetectorField() != field) {
    //     DoRegistration();
    // } else {
    //     G4ExceptionDescription msg;
    //     msg << "Attempting to register the same field multiple times for \"" << logic->GetName() << "\", skipping.";
    //     G4Exception("MACE::Geometry::EntityBase::RegisterSD", "-1", JustWarning, msg);
    // }
}

} // namespace
} // namespace internal

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
auto GeometryBase::RegisterField(gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes()};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterField<AField, AEquation, AStepper, ADriver>(lv, field, hMin, nVarStepper, nVarDriver, forceToAllDaughters);
    }
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
auto GeometryBase::RegisterField(std::string_view logicalVolumeName, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes(logicalVolumeName)};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterField<AField, AEquation, AStepper, ADriver>(lv, field, hMin, nVarStepper, nVarDriver, forceToAllDaughters);
    }
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
auto GeometryBase::RegisterField(gsl::index iLogicalVolume, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void {
    if (not Ready()) { return; }
    internal::RegisterField<AField, AEquation, AStepper, ADriver>(LogicalVolume(iLogicalVolume), field, hMin, nVarStepper, nVarDriver, forceToAllDaughters);
}

template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
auto GeometryBase::RegisterField(std::string_view logicalVolumeName, gsl::index iLogicalVolume, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void {
    if (not Ready()) { return; }
    internal::RegisterField<AField, AEquation, AStepper, ADriver>(LogicalVolume(logicalVolumeName, iLogicalVolume), field, hMin, nVarStepper, nVarDriver, forceToAllDaughters);
}

template<std::derived_from<G4VSolid> ASolid>
auto GeometryBase::Make(auto&&... args) -> gsl::not_null<ASolid*> {
    auto solid{std::make_unique<ASolid>(std::forward<decltype(args)>(args)...)};
    return static_cast<ASolid*>(fSolidStore.emplace_back(std::move(solid)).get());
}

template<std::derived_from<G4LogicalVolume> ALogical>
auto GeometryBase::Make(auto&&... args) -> gsl::not_null<ALogical*> {
    auto logic{std::make_unique<ALogical>(std::forward<decltype(args)>(args)...)};
    return static_cast<ALogical*>(fLogicalVolumes[logic->GetName()].emplace_back(std::move(logic)).get());
}

template<std::derived_from<G4VPhysicalVolume> APhysical>
auto GeometryBase::Make(auto&&... args) -> gsl::not_null<APhysical*> {
    auto physics{std::make_unique<APhysical>(std::forward<decltype(args)>(args)...)};
    return static_cast<APhysical*>(fPhysicalVolumes[physics->GetName()].emplace_back(std::move(physics)).get());
}

} // namespace MACE::Detector::Geometry
