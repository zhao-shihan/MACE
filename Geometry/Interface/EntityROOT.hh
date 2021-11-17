#pragma once

#include "TGeoManager.h"

#include "Geometry/Global.hh"
#include "Geometry/Interface/Entity.hh"

class MACE::Geometry::Interface::EntityROOT :
    public MACE::Geometry::Interface::Entity<TGeoVolume> {
public:
    EntityROOT();
    virtual ~EntityROOT() = 0;
    EntityROOT(const EntityROOT&) = delete;
    EntityROOT& operator=(const EntityROOT&) = delete;

protected:
    static TGeoManager* fgGeoManager;
    static TGeoElementTable* fgElementTable;
};
