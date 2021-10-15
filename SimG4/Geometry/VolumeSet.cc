#include "SimG4/Geometry/VolumeSet.hh"

MACE::SimG4::Geometry::VolumeSet::VolumeSet() :
    fSolidVolume(nullptr),
    fLogicalVolume(nullptr),
    fPhysicalVolume(nullptr) {}

void MACE::SimG4::Geometry::VolumeSet::
Set(G4VSolid* solidVolume, G4LogicalVolume* logicalVolume, G4VPhysicalVolume* physicalVolume) {
    fSolidVolume = solidVolume;
    fLogicalVolume = logicalVolume;
    fPhysicalVolume = physicalVolume;
}