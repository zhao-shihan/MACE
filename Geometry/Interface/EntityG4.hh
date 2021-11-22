#pragma once

#include "G4VPhysicalVolume.hh"

#include "Geometry/Interface/EntityWithDescription.hh"

namespace MACE::Geometry::Interface {
    using EntityG4 = EntityWithDescription<G4VPhysicalVolume>;
}