#include "MACE/Extension/Geant4X/Generator/SurfaceMuon.hxx"
#include "MACE/Extension/Geant4X/Generator/SurfaceMuonMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"

namespace MACE::inline Extension::Geant4X::Generator {

using namespace LiteralUnit::Energy;
using namespace LiteralUnit::Length;
using namespace PhysicalConstant;

SurfaceMuon::SurfaceMuon() :
    G4VPrimaryGenerator(),
    fMuonPlus(G4MuonPlus::Definition()),
    fMomentum(28_MeV),
    fMomentumSpreadRMS(0.05 * fMomentum),
    fBeamProfileRMS(5_mm),
    fVertexTime(0),
    fVertexZ(-1.5_m) {
    SurfaceMuonMessenger::Instance().AssignTo(this);
}

void SurfaceMuon::GeneratePrimaryVertex(G4Event* event) {
    const auto randEng = G4Random::getTheEngine();

    const auto position = G4ThreeVector(G4RandGauss::shoot(randEng, 0, fBeamProfileRMS),
                                        G4RandGauss::shoot(randEng, 0, fBeamProfileRMS),
                                        fVertexZ);
    const auto momentum = G4RandGauss::shoot(randEng, fMomentum, fMomentumSpreadRMS);
    const auto kineticEnergy = std::sqrt(momentum * momentum + muon_mass_c2 * muon_mass_c2) - muon_mass_c2;

    const auto primaryParticle = new G4PrimaryParticle(fMuonPlus);
    primaryParticle->SetKineticEnergy(kineticEnergy);
    primaryParticle->SetMass(muon_mass_c2);
    primaryParticle->SetMomentumDirection(CLHEP::HepZHat);
    primaryParticle->SetCharge(+1);

    const auto primaryVertex = new G4PrimaryVertex(position, fVertexTime);
    primaryVertex->SetPrimary(primaryParticle);

    event->AddPrimaryVertex(primaryVertex);
}

} // namespace MACE::inline Extension::Geant4X::Generator
