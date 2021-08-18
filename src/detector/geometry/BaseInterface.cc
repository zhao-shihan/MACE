#include "detector/geometry/BaseInterface.hh"

MACE::Geometry::BaseInterface::BaseInterface(size_t volumeCount) :
    fVolumeSetList(volumeCount) {}

MACE::Geometry::BaseInterface::~BaseInterface() {}