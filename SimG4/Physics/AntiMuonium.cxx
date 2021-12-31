#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"

#include "SimG4/Physics/AntiMuonium.hxx"
#include "SimG4/Physics/AntiMuoniumDecayChannel.hxx"

using namespace MACE::SimG4::Physics;

AntiMuonium* AntiMuonium::instance = nullptr;

AntiMuonium* AntiMuonium::Definition() {
    if (instance != nullptr) {
        return instance;
    }
    const G4String name = "-M";
    // search in particle table
    G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* anInstance = pTable->FindParticle(name);
    if (anInstance == nullptr) {
        // create particle
        //
        //
        //    Arguments for constructor are as follows
        //               name             mass          width         charge
        //             2*spin           parity  C-conjugation
        //          2*Isospin       2*Isospin3       G-parity
        //               type    lepton number  baryon number   PDG encoding
        //             stable         lifetime    decay table
        //             shortlived
        anInstance = new G4ParticleDefinition(
            name, 105.658369 * MeV + 511 * keV, 2.99591e-16 * MeV, 0,
            1, 0, 0,
            0, 0, 0,
            "lepton", 0, 0, -1313,
            false, 2197.03 * ns, NULL,
            false
        );

        // Bohr magnetron of Muonium - T. Shiroka
        // The magnetic moment of Mu is the sum of those of mu+ and e- with
        // the respective gyromagnetic ratio anomalies as coefficients
        G4double muBmu = 0.5 * eplus * hbar_Planck / (0.10565840 * GeV / c_squared);
        G4double muBel = -0.5 * eplus * hbar_Planck / (0.51099906 * MeV / c_squared);
        G4double muB = 1.0011659208 * muBmu + 1.0011596521859 * muBel;
        // !  Anti-muonium: is negative
        anInstance->SetPDGMagneticMoment(-muB);

        // create Decay Table 
        auto table = new G4DecayTable();
        // create a decay channel
        auto mode = new AntiMuoniumDecayChannel("-M", 1.00);
        table->Insert(mode);
        anInstance->SetDecayTable(table);
    }
    instance = static_cast<AntiMuonium*>(anInstance);
    return instance;
}

AntiMuonium* AntiMuonium::AntiMuoniumDefinition() {
    return Definition();
}
