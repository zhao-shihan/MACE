#include "Geometry/Interface/EntityROOT.hh"

using namespace MACE::Geometry::Interface;

TGeoManager* EntityROOT::fgGeoManager = nullptr;
TGeoElementTable* EntityROOT::fgElementTable = nullptr;

EntityROOT::EntityROOT() :
    Entity<TGeoVolume>() {
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

EntityROOT::~EntityROOT() {}
