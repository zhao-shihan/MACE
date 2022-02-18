template<class... RequiredDescriptions>
MACE::ObserverPtr<G4NistManager> MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::
fgG4Nist = nullptr;

template<class... RequiredDescriptions>
MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::
EntityG4() :
    EntityWithDescription<G4VPhysicalVolume, RequiredDescriptions...>() {
    if (fgG4Nist == nullptr) {
        fgG4Nist = G4NistManager::Instance();
    }
}

template<class... RequiredDescriptions>
MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::
~EntityG4() noexcept = default;

template<class... RequiredDescriptions>
void MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::
WriteSelfAndDesendentsToGDML(std::string_view fileName, size_t volumeIndex) const {
    G4GDMLParser gdml;
    gdml.SetAddPointerToName(false);
    gdml.SetOutputFileOverwrite(true);
    gdml.Write(fileName.data(), this->GetVolume(volumeIndex));
}
