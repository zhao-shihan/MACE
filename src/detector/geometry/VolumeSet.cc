#include "detector/geometry/VolumeSet.hh"

MACE::Geometry::VolumeSet::VolumeSet() :
    fSolidVolume(nullptr),
    fLogicalVolume(nullptr),
    fPhysicalVolume(nullptr) {}

void MACE::Geometry::VolumeSet::
Set(G4VSolid* solidVolume, G4LogicalVolume* logicalVolume, G4VPhysicalVolume* physicalVolume) {
    fSolidVolume = solidVolume;
    fLogicalVolume = logicalVolume;
    fPhysicalVolume = physicalVolume;
}