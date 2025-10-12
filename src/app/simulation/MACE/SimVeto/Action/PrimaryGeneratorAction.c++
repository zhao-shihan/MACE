#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/SimVeto/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimVeto/Analysis.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Env/BasicEnv.h++"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"

namespace MACE::SimVeto::inline Action {
using namespace Mustard::Utility::LiteralUnit;
PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{this},
    G4VUserPrimaryGeneratorAction{},
    fAvailableGenerator{},
    fGenerator{&fAvailableGenerator.ecoMug},
    fSavePrimaryVertexData{true},
    fPrimaryVertexData{},
    fAnalysisMessengerRegister{this},
    fPrimaryGeneratorActionMessengerRegister{this} {
    fAvailableGenerator.ecoMug.UseHSphere();
    fAvailableGenerator.ecoMug.HSphereRadius(2_m);
    if (Mustard::Env::VerboseLevelReach<'V'>()) {
        std::cout << "=====>estimated time of 10000000 CR muon: " << fAvailableGenerator.ecoMug.EstimatedTime(10000000) << " ns" << std::endl;
    }
}
auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    fGenerator->GeneratePrimaryVertex(event);
    if (fSavePrimaryVertexData) {
        UpdatePrimaryVertexData(*event);
    }
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
} // namespace MACE::SimVeto::inline Action
