#pragma once

#include "MACE/Math/FindRoot.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/CETAString.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4DecayProducts.hh"
#include "G4Electron.hh"
#include "G4ParticleDefinition.hh"
#include "G4Positron.hh"
#include "G4RandomDirection.hh"
#include "G4VDecayChannel.hh"
#include "Randomize.hh"

#include "gsl/gsl"

#include "fmt/format.h"

#include <cmath>
#include <concepts>
#include <cstdio>
#include <stdexcept>
#include <vector>

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

template<std::derived_from<G4VDecayChannel> AMuonDecayChannel, CETAString AName>
class WrapAsMuoniumDecayChannel : public AMuonDecayChannel {
public:
    WrapAsMuoniumDecayChannel(const G4String& parentName, G4double br, G4int verbose = 1);

    auto DecayIt(G4double) -> G4DecayProducts* override;

private:
    int fAtomicShellProductIndex;
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel

#include "MACE/Simulation/Physics/DecayChannel/WrapAsMuoniumDecayChannel.inl"
