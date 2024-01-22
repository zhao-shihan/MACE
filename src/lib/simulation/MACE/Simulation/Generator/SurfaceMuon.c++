#include "MACE/Simulation/Generator/SurfaceMuon.h++"
#include "MACE/Simulation/Generator/SurfaceMuonMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"

#include "gsl/gsl"

namespace MACE::inline Simulation::Generator {

using namespace LiteralUnit::Energy;
using namespace LiteralUnit::Length;
using namespace PhysicalConstant;

SurfaceMuon::SurfaceMuon() :
    NonMoveableBase{},
    G4VPrimaryGenerator{},
    fMuonPlus{gsl::not_null{G4MuonPlus::Definition()}},
    fMomentum{28_MeV},
    fMomentumRMS{0.05 * fMomentum},
    fPositionRMS{5_mm},
    fTime{0},
    fPositionZ{-1.5_m} {
    SurfaceMuonMessenger::Instance().Register(this);
}

void SurfaceMuon::GeneratePrimaryVertex(G4Event* event) {
    const auto randEng = G4Random::getTheEngine();

    const auto position = G4ThreeVector(G4RandGauss::shoot(randEng, 0, fPositionRMS),
                                        G4RandGauss::shoot(randEng, 0, fPositionRMS),
                                        fPositionZ);
    const auto momentum = G4RandGauss::shoot(randEng, fMomentum, fMomentumRMS);
    const auto kineticEnergy = std::sqrt(momentum * momentum + muon_mass_c2 * muon_mass_c2) - muon_mass_c2;

    const auto primaryParticle = new G4PrimaryParticle(fMuonPlus);
    primaryParticle->SetKineticEnergy(kineticEnergy);
    primaryParticle->SetMass(muon_mass_c2);
    primaryParticle->SetMomentumDirection(CLHEP::HepZHat);
    primaryParticle->SetCharge(+1);

    const auto primaryVertex = new G4PrimaryVertex(position, fTime);
    primaryVertex->SetPrimary(primaryParticle);

    event->AddPrimaryVertex(primaryVertex);
}

} // namespace MACE::inline Simulation::Generator
