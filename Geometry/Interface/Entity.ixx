namespace MACE::Geometry::Interface {

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
