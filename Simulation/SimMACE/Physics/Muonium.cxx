#include "Simulation/SimMACE/Physics/Muonium.hxx"
#include "Simulation/SimMACE/Physics/MuoniumDecayChannel.hxx"

#include "G4DecayTable.hh"
#include "G4ParticleTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

using MACE::Simulation::SimMACE::Physics::Muonium;
using namespace MACE::Utility::LiteralUnit;

Muonium* Muonium::fgInstance = nullptr;

Muonium* Muonium::Definition() {
    if (fgInstance == nullptr) {
        fgInstance = new Muonium();
    }
    return fgInstance;
}

Muonium::Muonium() :
    G4ParticleDefinition("M",
                         105.658369_MeV + 511_keV,
                         2.99591e-16_MeV,
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
                         -1313,
                         false,
                         2197.03_ns,
                         nullptr,
                         false) {

    // Bohr magnetron of Muonium - T. Shiroka
    // The magnetic moment of Mu is the sum of those of mu+ and e- with
    // the respective gyromagnetic ratio anomalies as coefficients
    constexpr auto muBohrMu = 0.5 * eplus * hbar_Planck / (0.10565840_GeV / c_squared);
    constexpr auto muBohrE = -0.5 * eplus * hbar_Planck / (0.51099906_MeV / c_squared);
    constexpr auto muBohrM = 1.0011659208 * muBohrMu + 1.0011596521859 * muBohrE;
    this->SetPDGMagneticMoment(muBohrM);

    // create Decay Table
    auto table = new G4DecayTable();
    // create a decay channel
    table->Insert(new MuoniumDecayChannel("M", 1.00));
    this->SetDecayTable(table);
}
