#include "MACE/Extension/Geant4X/Physics/DecayChannel/MuoniumDecayChannel.h++"
#include "MACE/Extension/Geant4X/Physics/Particle/Muonium.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4DecayTable.hh"
#include "G4ParticleTable.hh"

namespace MACE::inline Extension::Geant4X::Physics::inline Particle {

using namespace MACE::PhysicalConstant;

Muonium::Muonium() :
    G4ParticleDefinition("M",
                         muonium_mass_c2,
                         hbar_Planck / muonium_lifetime,
                         0,
                         1,
                         0,
                         0,
                         0,
                         0,
                         0,
                         "lepton",
                         0,
                         0,
                         1311,
                         false,
                         muonium_lifetime,
                         nullptr,
                         false) {

    // Bohr magnetron of Muonium - T. Shiroka
    // The magnetic moment of Mu is the sum of those of mu+ and e- with
    // the respective gyromagnetic ratio anomalies as coefficients
    constexpr auto muBohrMu = 0.5 * eplus * hbar_Planck / (muon_mass_c2 / c_squared);
    constexpr auto muBohrE = -0.5 * eplus * hbar_Planck / (electron_mass_c2 / c_squared);
    constexpr auto muBohrM = 1.0011659208 * muBohrMu + 1.0011596521859 * muBohrE;
    this->SetPDGMagneticMoment(muBohrM);

    // create Decay Table
    auto table = new G4DecayTable;
    // create a decay channel
    table->Insert(new MuoniumDecayChannel("M", 1.00));
    this->SetDecayTable(table);
}

} // namespace MACE::inline Extension::Geant4X::Physics::inline Particle
