#pragma once

#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4GDMLParser.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"

#include "Geometry/Interface/EntityWithDescription.hh"

template<class... RequiredDescriptions>
class MACE::Geometry::Interface::EntityG4 :
    public MACE::Geometry::Interface::EntityWithDescription<G4VPhysicalVolume, RequiredDescriptions...> {
public:
    EntityG4();
    virtual ~EntityG4() = 0;
    EntityG4(const EntityG4&) = delete;
    EntityG4& operator=(const EntityG4&) = delete;

    void WriteSelfAndDesendentsToGDML(const char* fileName) const;

protected:
    static G4NistManager* fgG4Nist;
    static G4bool fgCheckOverlaps;
};

#include "Geometry/Interface/EntityG4.tcc"