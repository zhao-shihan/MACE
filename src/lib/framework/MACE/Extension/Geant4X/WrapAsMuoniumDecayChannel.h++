#pragma once

#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/Print.h++"
#include "MACE/Math/FindRoot.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Math/QinAlgorithm.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4DecayProducts.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"
#include "G4String.hh"
#include "G4VDecayChannel.hh"
#include "Randomize.hh"

#include "muc/ceta_string"

#include "gsl/gsl"

#include "fmt/format.h"

#include <cmath>
#include <concepts>
#include <cstdio>
#include <stdexcept>
#include <vector>

namespace MACE::inline Extension::Geant4X {

template<std::derived_from<G4VDecayChannel> AMuonDecayChannel, muc::ceta_string AName>
class WrapAsMuoniumDecayChannel : public AMuonDecayChannel {
public:
    WrapAsMuoniumDecayChannel(const G4String& parentName, G4double br, G4int verbose = 1);

    auto DecayIt(G4double) -> G4DecayProducts* override;

private:
    int fAtomicShellProductIndex;
};

} // namespace MACE::inline Extension::Geant4X

#include "MACE/Extension/Geant4X/WrapAsMuoniumDecayChannel.inl"
