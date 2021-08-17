#include "detector/geometry/Base.hh"

MACE::Geometry::Base::Base(size_t volumeCount) :
    fVolumeSetList(volumeCount) {}

MACE::Geometry::Base::~Base() {}