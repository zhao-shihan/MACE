#include "detector/geometry/BaseInterface.hh"

MACE::SimG4::Geometry::BaseInterface::BaseInterface(size_t volumeCount) :
    fVolumeSetList(volumeCount) {}

MACE::SimG4::Geometry::BaseInterface::~BaseInterface() {}