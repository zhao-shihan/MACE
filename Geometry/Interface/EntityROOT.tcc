template<class... RequiredDescriptions>
TGeoManager* MACE::Geometry::Interface::EntityROOT<RequiredDescriptions...>::fgGeoManager = nullptr;
template<class... RequiredDescriptions>
TGeoElementTable* MACE::Geometry::Interface::EntityROOT<RequiredDescriptions...>::fgElementTable = nullptr;

template<class... RequiredDescriptions>
MACE::Geometry::Interface::EntityROOT<RequiredDescriptions...>::EntityROOT() :
    EntityWithDescription<TGeoVolume, RequiredDescriptions...>() {
    if (fgGeoManager == nullptr) {
        fgGeoManager = new TGeoManager("GeomMACE", "Geometry of MACE");
        TGeoManager::LockDefaultUnits(false);
        TGeoManager::SetDefaultUnits(TGeoManager::kRootUnits);
        TGeoManager::LockDefaultUnits(true);
    }
    if (fgElementTable == nullptr) {
        fgElementTable = new TGeoElementTable();
        fgElementTable->BuildDefaultElements();
    }
}

template<class... RequiredDescriptions>
MACE::Geometry::Interface::EntityROOT<RequiredDescriptions...>::~EntityROOT() {}
