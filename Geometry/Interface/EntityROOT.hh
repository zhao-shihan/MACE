/* #pragma once

#include "TGeoManager.h"

#include "Geometry/Global.hh"
#include "Geometry/Interface/EntityWithDescription.hh"

// (Do not use for now. No way of making units consistent so far.)
template<class... RequiredDescriptions>
class MACE::Geometry::Interface::EntityROOT :
    public MACE::Geometry::Interface::EntityWithDescription<TGeoVolume, RequiredDescriptions...> {
public:
    EntityROOT();
    virtual ~EntityROOT() = 0;
    EntityROOT(const EntityROOT&) = delete;
    EntityROOT& operator=(const EntityROOT&) = delete;

protected:
    static TGeoManager* fgGeoManager;
    static TGeoElementTable* fgElementTable;
};

#include "Geometry/Interface/EntityROOT.icc"
 */