#pragma once

#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

#include "SimG4Global.hh"


class MACE::SimG4::Geometry::VolumeSet {
public:
    VolumeSet();

    auto* GetSolidVolume() const { return fSolidVolume; }
    auto* GetLogicalVolume() const { return fLogicalVolume; }
    auto* GetPhysicalVolume() const { return fPhysicalVolume; }

    void Set(G4VSolid* solidVolume, G4LogicalVolume* logicalVolume, G4VPhysicalVolume* physicalVolume);
    void SetSolidVolume(G4VSolid* solidVolume) { fSolidVolume = solidVolume; }
    void SetLogicalVolume(G4LogicalVolume* logicalVolume) { fLogicalVolume = logicalVolume; }
    void SetPhysicalVolume(G4VPhysicalVolume* physicalVolume) { fPhysicalVolume = physicalVolume; }

private:
    G4VSolid* fSolidVolume;
    G4LogicalVolume* fLogicalVolume;
    G4VPhysicalVolume* fPhysicalVolume;
};
