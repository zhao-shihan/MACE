template<class... RequiredDescriptions>
G4NistManager* MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::fgG4Nist = nullptr;
template<class... RequiredDescriptions>
G4bool MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::fgCheckOverlaps = true;

template<class... RequiredDescriptions>
MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::EntityG4() :
    EntityWithDescription<G4VPhysicalVolume, RequiredDescriptions...>() {
    if (fgG4Nist == nullptr) {
        fgG4Nist = G4NistManager::Instance();
    }
}

template<class... RequiredDescriptions>
MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::~EntityG4() {}

template<class... RequiredDescriptions>
void MACE::Geometry::Interface::EntityG4<RequiredDescriptions...>::WriteSelfAndDesendentsToGDML(const char* fileName) const {
    G4GDMLParser gdml;
    gdml.SetAddPointerToName(false);
    gdml.SetOutputFileOverwrite(true);
    gdml.Write(fileName, this->GetVolume());
}