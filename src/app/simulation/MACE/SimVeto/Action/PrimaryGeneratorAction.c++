#include <type_traits>

#include "MACE/SimVeto/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimVeto/Action/TrackingAction.h++"
#include "MACE/SimVeto/Analysis.h++"

#include "MACE/Detector/Description/ECALField.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"

namespace MACE::SimVeto::inline Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fAvailableGenerator{},
    fGenerator{&fAvailableGenerator.ecoMug},
    fSavePrimaryVertexData{true},
    fPrimaryVertexData{},
    fAnalysisMessengerRegister{this},
    fPrimaryGeneratorActionMessengerRegister{this} {}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    fGenerator->GeneratePrimaryVertex(event);
    if (fSavePrimaryVertexData) { UpdatePrimaryVertexData(*event); }
}

auto PrimaryGeneratorAction::UpdatePrimaryVertexData(const G4Event& event) -> void {
    fPrimaryVertexData.clear();
    fPrimaryVertexData.reserve(event.GetNumberOfPrimaryVertex());
    for (const auto* pv{event.GetPrimaryVertex()}; pv; pv = pv->GetNext()) {
        for (const auto* pp{pv->GetPrimary()}; pp; pp = pp->GetNext()) {
            const auto& v{fPrimaryVertexData.emplace_back(std::make_unique_for_overwrite<Mustard::Data::Tuple<Data::SimPrimaryVertex>>())};
            Get<"EvtID">(*v) = event.GetEventID();
            Get<"PDGID">(*v) = pp->GetPDGcode();
            Get<"t0">(*v) = pv->GetT0();
            Get<"x0">(*v) = pv->GetPosition();
            Get<"Ek0">(*v) = pp->GetKineticEnergy();
            Get<"p0">(*v) = pp->GetMomentum();
        }
    }
    Analysis::Instance().SubmitPrimaryVertexData(fPrimaryVertexData);
}
auto PrimaryGeneratorAction::SetEcoMugPrimaryVertex()->void{
    const auto& ecalField{Description::ECALField::Instance()};
    const auto x0{Mustard::VectorCast<G4ThreeVector>(ecalField.Center())};
    fGenerator->UseHSphere();
    fGenerator->HSphereCenterPosition(x0);
    fGenerator->HSphereRadius(2_m);
    }
} // namespace MACE::SimVeto::inline Action
