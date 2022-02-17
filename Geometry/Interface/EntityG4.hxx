#pragma once

#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4GDMLParser.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"

#include "Geometry/Interface/EntityWithDescription.hxx"
#include "Utility/ObserverPtr.hxx"

template<class... RequiredDescriptions>
class MACE::Geometry::Interface::EntityG4 :
    public MACE::Geometry::Interface::EntityWithDescription<G4VPhysicalVolume, RequiredDescriptions...> {
public:
    EntityG4();
    virtual ~EntityG4() noexcept = 0;
    EntityG4(const EntityG4&) = delete;
    EntityG4& operator=(const EntityG4&) = delete;

    void SetCheckOverlaps(G4bool val);
    void WriteSelfAndDesendentsToGDML(std::string_view fileName, size_t volumeIndex = 0) const;

protected:
    G4bool fCheckOverlaps = true;

    static ObserverPtr<G4NistManager> fgG4Nist;
};

#include "Geometry/Interface/EntityG4.ixx"
