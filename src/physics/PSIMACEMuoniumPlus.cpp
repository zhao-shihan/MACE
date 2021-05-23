#include "physics/PSIMACEMuoniumPlus.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

//#include "physics/MuDecayChannel.hh" 
#include "G4DecayTable.hh"

PSIMACEMuoniumPlus* PSIMACEMuoniumPlus::theInstance = 0;

PSIMACEMuoniumPlus* PSIMACEMuoniumPlus::Definition() {
    if (theInstance != 0) return theInstance;
    const G4String name = "Mu";
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
        //             shortlived      subType    anti_encoding
        anInstance = new G4ParticleDefinition(
            name, 0.1056584 * GeV, 2.99591e-16 * MeV, 0. * eplus,
            1, 0, 0,
            0, 0, 0,
            "lepton", -1, 0, -1313,
            false, 2197.03 * ns, NULL,
            false, "mu"
        );

        // Bohr magnetron of Muonium - T. Shiroka
        // The magnetic moment of Mu is the sum of those of mu+ and e- with
        // the respective gyromagnetic ratio anomalies as coefficients
        G4double muBmu = 0.5 * eplus * hbar_Planck / (0.10565840 * GeV / c_squared);
        G4double muBel = -0.5 * eplus * hbar_Planck / (0.51099906 * MeV / c_squared);
        G4double muB = 1.0011659208 * muBmu + 1.0011596521859 * muBel;

        anInstance->SetPDGMagneticMoment(muB);
    }

    // create Decay Table in the PhysicsList

    theInstance = reinterpret_cast<PSIMACEMuoniumPlus*>(anInstance);

    return theInstance;
}

PSIMACEMuoniumPlus* PSIMACEMuoniumPlus::MuoniumDefinition() {
    return Definition();
}

PSIMACEMuoniumPlus* PSIMACEMuoniumPlus::Muonium() {
    return Definition();
}



