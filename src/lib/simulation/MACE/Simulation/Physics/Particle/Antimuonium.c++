#include "MACE/Simulation/Physics/DecayChannel/MuoniumDecayChannel.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4DecayTable.hh"
#include "G4ParticleTable.hh"

namespace MACE::inline Simulation::inline Physics::inline Particle {

using namespace PhysicalConstant;

Antimuonium::Antimuonium() :
    Singleton{},
    G4ParticleDefinition{"anti_muonium",
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
                         -990013111,
                         false,
                         muonium_lifetime,
                         nullptr} {

    // Bohr magnetron of Muonium - T. Shiroka
    // The magnetic moment of Mu is the sum of those of mu+ and e- with
    // the respective gyromagnetic ratio anomalies as coefficients
    constexpr auto muBohrMu = 0.5 * eplus * hbar_Planck / (muon_mass_c2 / c_squared);
    constexpr auto muBohrE = -0.5 * eplus * hbar_Planck / (electron_mass_c2 / c_squared);
    constexpr auto muBohrM = 1.0011659208 * muBohrMu + 1.0011596521859 * muBohrE;
    // Negative for anti-muonium
    this->SetPDGMagneticMoment(-muBohrM);

    // create Decay Table
    auto table = new G4DecayTable;
    // create a decay channel
    table->Insert(new MuoniumDecayChannel{"anti_muonium", 1});
    this->SetDecayTable(table);
}

} // namespace MACE::inline Simulation::inline Physics::inline Particle
