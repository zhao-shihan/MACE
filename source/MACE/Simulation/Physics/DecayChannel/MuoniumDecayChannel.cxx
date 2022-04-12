// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: MuDecayChannel.cc,v 1.17 2006/06/29 19:25:34 gunter Exp $
// GEANT4 tag $Name: geant4-09-00 $
//
//
// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      History: first implementation, based on object model of
//      30 May  1997 H.Kurashige
//
//      Fix bug in calcuration of electron energy in DecayIt 28 Feb. 01 H.Kurashige
//
//  2005
//      M. Melissas ( melissas AT cppm.in2p3.fr)
//      J. Brunner ( brunner AT cppm.in2p3.fr)
//      Adding V-A fluxes for neutrinos using a new algortithm :
//
//  2008-05
//      Modified for the muonium decay by Toni SHIROKA, Paul Scherrer Institut, PSI
// ------------------------------------------------------------

#include "MACE/Simulation/Physics/DecayChannel/MuoniumDecayChannel.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4DecayProducts.hh"
#include "G4LorentzRotation.hh"
#include "G4LorentzVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4VDecayChannel.hh"
#include "Randomize.hh"

namespace MACE::Simulation::Physics::DecayChannel {

MuoniumDecayChannel::MuoniumDecayChannel(const G4String& theParentName, G4double theBR, G4int verbose) :
    G4VDecayChannel("MuoniumDecay", verbose) {
    if (theParentName == "M") {
        SetBR(theBR);
        SetParent(theParentName);
        SetNumberOfDaughters(4);
        SetDaughter(0, "e+");
        SetDaughter(1, "nu_e");
        SetDaughter(2, "anti_nu_mu");
        SetDaughter(3, "e-");
    } else if (theParentName == "anti_M") {
        SetBR(theBR);
        SetParent(theParentName);
        SetNumberOfDaughters(4);
        SetDaughter(0, "e-");
        SetDaughter(1, "anti_nu_e");
        SetDaughter(2, "nu_mu");
        SetDaughter(3, "e+");
    } else {
#ifdef G4VERBOSE
        if (GetVerboseLevel() > 0) {
            G4cout << "MuoniumDecayChannel::(Constructor) says\n"
                      "\tParent particle is not muonium (M) or anti muonium (anti_m) but "
                   << theParentName << G4endl;
        }
#endif
    }
}

G4DecayProducts* MuoniumDecayChannel::DecayIt(G4double) {
    using namespace MACE::Utility::PhysicalConstant;

    // this version neglects muon polarization,and electron mass
    //              assumes the pure V-A coupling
    //              the Neutrinos are correctly V-A

#ifdef G4VERBOSE
    if (GetVerboseLevel() > 1) G4cout << "G4MuonDecayChannel::DecayIt ";
#endif

    CheckAndFillParent();
    CheckAndFillDaughters();

    // parent mass
    G4double parentmass = G4MT_parent->GetPDGMass();

    // daughters'mass
    G4double daughtermass[3];
    for (G4int index = 0; index < 3; ++index) {
        daughtermass[index] = G4MT_daughters[index]->GetPDGMass();
    }

    // create G4Decayproducts with parent G4DynamicParticle at rest
    auto products = new G4DecayProducts(G4DynamicParticle(G4MT_parent, G4ThreeVector(), 0.0));

    // calculate daughter momentum
    G4double daughtermomentum[3];
    // calculate electron energy
    G4double xmax = (1.0 + daughtermass[0] * daughtermass[0] / (parentmass * parentmass));
    G4double x;

    G4double Ee, Ene;

    G4double gam;
    G4double EMax = parentmass / 2 - daughtermass[0];

    const std::size_t MAX_LOOP = 1000;
    // Generating Random Energy
    for (std::size_t loop1 = 0; loop1 < MAX_LOOP; ++loop1) {
        Ee = G4UniformRand();
        for (std::size_t loop2 = 0; loop2 < MAX_LOOP; ++loop2) {
            x = xmax * G4UniformRand();
            gam = G4UniformRand();
            if (gam <= x * (1. - x)) break;
            x = xmax;
        }
        Ene = x;
        if (Ene >= (1. - Ee)) break;
        Ene = 1. - Ee;
    }
    G4double Enm = (2. - Ee - Ene);

    // initialisation of rotation parameters

    G4double costheta, sintheta, rphi, rtheta, rpsi;
    costheta = 1. - 2. / Ee - 2. / Ene + 2. / Ene / Ee;
    sintheta = std::sqrt(1. - costheta * costheta);

    rphi = twopi * G4UniformRand() * rad;
    rtheta = std::acos(2. * G4UniformRand() - 1.);
    rpsi = twopi * G4UniformRand() * rad;

    G4RotationMatrix rot(rphi, rtheta, rpsi);

    // electron 0
    daughtermomentum[0] = std::sqrt(Ee * Ee * EMax * EMax + 2.0 * Ee * EMax * daughtermass[0]);
    G4ThreeVector direction0(0.0, 0.0, 1.0);

    direction0 *= rot;

    auto daughterparticle = new G4DynamicParticle(G4MT_daughters[0], direction0 * daughtermomentum[0]);

    products->PushProducts(daughterparticle);

    // electronic neutrino  1

    daughtermomentum[1] = std::sqrt(Ene * Ene * EMax * EMax + 2.0 * Ene * EMax * daughtermass[1]);
    G4ThreeVector direction1(sintheta, 0.0, costheta);

    direction1 *= rot;

    auto daughterparticle1 = new G4DynamicParticle(G4MT_daughters[1], direction1 * daughtermomentum[1]);
    products->PushProducts(daughterparticle1);

    // muonnic neutrino 2

    daughtermomentum[2] = std::sqrt(Enm * Enm * EMax * EMax + 2.0 * Enm * EMax * daughtermass[2]);
    G4ThreeVector direction2(-Ene / Enm * sintheta, 0, -Ee / Enm - Ene / Enm * costheta);

    direction2 *= rot;

    auto daughterparticle2 = new G4DynamicParticle(G4MT_daughters[2], direction2 * daughtermomentum[2]);
    products->PushProducts(daughterparticle2);

    // atomic shell electron 3
    // energy distribution
    constexpr double ProbTable[100] = {0.0579448, 0.0820584, 0.0822704, 0.0764795, 0.0690145, 0.0614549, 0.054404, 0.0480648, 0.0424683, 0.0375724, 0.0333076, 0.0295981, 0.0263708, 0.0235596, 0.0211061, 0.0189599, 0.0170777, 0.0154228, 0.0139636, 0.0126736, 0.01153, 0.0105136, 0.0096078, 0.00879855, 0.00807379, 0.00742315, 0.00683769, 0.00630972, 0.00583257, 0.00540044, 0.0050083, 0.00465176, 0.00432698, 0.00403061, 0.00375967, 0.00351158, 0.00328404, 0.00307501, 0.0028827, 0.00270552, 0.00254203, 0.00239098, 0.00225124, 0.00212178, 0.00200171, 0.0018902, 0.00178653, 0.00169004, 0.00160012, 0.00151625, 0.00143793, 0.00136472, 0.00129622, 0.00123207, 0.00117194, 0.00111552, 0.00106253, 0.00101274, 0.000965894, 0.000921796, 0.000880247, 0.000841072, 0.000804106, 0.0007692, 0.000736214, 0.000705023, 0.000675507, 0.00064756, 0.000621079, 0.000595972, 0.000572154, 0.000549544, 0.000528069, 0.000507659, 0.000488251, 0.000469786, 0.000452208, 0.000435466, 0.000419511, 0.0004043, 0.000389789, 0.000375941, 0.000362718, 0.000350087, 0.000338015, 0.000326472, 0.000315431, 0.000304866, 0.00029475, 0.000285062, 0.000275778, 0.00026688, 0.000258347, 0.000250162, 0.000242306, 0.000234765, 0.000227523, 0.000220565, 0.000213878, 0.000207449};
    double probsum3 = 0.;
    double seed3 = G4UniformRand();
    G4double kineticE3 = 0.;
    for (int i = 0; i < 100; i++) {
        probsum3 += ProbTable[i];
        if (seed3 < probsum3) {
            kineticE3 = (i + G4UniformRand()) * eV;
            break;
        }
    }

    // Set Direction
    auto r3 = G4UniformRand();
    auto a3 = 2.0 * sqrt(r3 * (1.0 - r3));
    auto b3 = 2 * M_PI * G4UniformRand();
    auto daughterparticle3 = new G4DynamicParticle(
        G4MT_daughters[3], G4ThreeVector(a3 * cos(b3), a3 * sin(b3), 1.0 - 2.0 * r3), kineticE3);
    products->PushProducts(daughterparticle3);

    // output message
#ifdef G4VERBOSE
    if (GetVerboseLevel() > 1) {
        G4cout << "MuoniumDecayChannel::DecayIt\n"
                  "\tCreate decay products in rest frame."
               << G4endl;
        products->DumpInfo();
    }
#endif
    return products;
}

} // namespace MACE::Simulation::Physics::DecayChannel
