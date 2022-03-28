#pragma once

#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Track/PhysicsTrack.hxx"

namespace MACE::Core::DataModel::Track {

template<class Track_t>
concept IsTrack = IsHelixTrack or IsPhysicsTrack;

} // namespace MACE::Core::DataModel::Track
