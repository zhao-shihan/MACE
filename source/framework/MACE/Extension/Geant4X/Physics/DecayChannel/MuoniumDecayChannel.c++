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

#include "MACE/Extension/Geant4X/Physics/DecayChannel/MuoniumDecayChannel.h++"
#include "MACE/Math/FindRoot.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4DecayProducts.hh"
#include "G4LorentzRotation.hh"
#include "G4LorentzVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4VDecayChannel.hh"
#include "Randomize.hh"

namespace MACE::inline Extension::Geant4X::Physics::inline DecayChannel {

MuoniumDecayChannel::MuoniumDecayChannel(const G4String& parentName, G4double br, G4int verbose) :
    G4VDecayChannel("MuoniumDecay", verbose) {
    SetBR(br);
    SetParent(parentName);
    SetNumberOfDaughters(4);
    if (parentName == "M") {
        SetDaughter(0, "e+");
        SetDaughter(1, "nu_e");
        SetDaughter(2, "anti_nu_mu");
        SetDaughter(3, "e-");
    } else if (parentName == "anti_M") {
        SetDaughter(0, "e-");
        SetDaughter(1, "anti_nu_e");
        SetDaughter(2, "nu_mu");
        SetDaughter(3, "e+");
    } else {
#ifdef G4VERBOSE
        if (GetVerboseLevel() > 0) {
            G4cout << "MuoniumDecayChannel::(Constructor) says\n"
                      "\tParent particle is not muonium (M) or anti muonium (anti_m) but "
                   << parentName << G4endl;
        }
#endif
    }
}

G4DecayProducts* MuoniumDecayChannel::DecayIt(G4double) {
    using namespace MACE::PhysicalConstant;

    // this version neglects muon polarization, and electron mass
    //              assumes the pure V-A coupling
    //              the Neutrinos are correctly V-A

#ifdef G4VERBOSE
    if (GetVerboseLevel() > 1) {
        G4cout << "G4MuonDecayChannel::DecayIt ";
    }
#endif

    CheckAndFillParent();
    CheckAndFillDaughters();

    // parent mass (first 3 daughter, muon mass)
    constexpr auto parentmass = muon_mass_c2;

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

    products->PushProducts(new G4DynamicParticle(G4MT_daughters[0], direction0 * daughtermomentum[0]));

    // electronic neutrino  1

    daughtermomentum[1] = std::sqrt(Ene * Ene * EMax * EMax + 2.0 * Ene * EMax * daughtermass[1]);
    G4ThreeVector direction1(sintheta, 0.0, costheta);

    direction1 *= rot;

    products->PushProducts(new G4DynamicParticle(G4MT_daughters[1], direction1 * daughtermomentum[1]));

    // muonnic neutrino 2

    daughtermomentum[2] = std::sqrt(Enm * Enm * EMax * EMax + 2.0 * Enm * EMax * daughtermass[2]);
    G4ThreeVector direction2(-Ene / Enm * sintheta, 0, -Ee / Enm - Ene / Enm * costheta);

    direction2 *= rot;

    products->PushProducts(new G4DynamicParticle(G4MT_daughters[2], direction2 * daughtermomentum[2]));

    // atomic shell electron 3

    using namespace LiteralUnit::MathConstant;

    x = G4UniformRand();
    const auto atomicShellMomentum = fine_structure_const * muonium_reduced_mass_c2 *
                                     Math::FindRoot::Secant(
                                         // CDF - x
                                         [&x](const auto p) {
                                             const auto p2 = Math::Pow2(p);
                                             return (2 / 3_pi) *
                                                        (p * (p2 * (3 * p2 + 8) - 3) /
                                                             Math::Pow3(p2 + 1) +
                                                         3 * std::atan(p)) -
                                                    x;
                                         },
                                         // most probable p*
                                         27 / 8_pi)
                                         .first *
                                     G4RandomDirection();
    products->PushProducts(new G4DynamicParticle(G4MT_daughters[3], atomicShellMomentum));

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

} // namespace MACE::inline Extension::Geant4X::Physics::inline DecayChannel
