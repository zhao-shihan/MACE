#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "Mustard/Extension/Geant4X/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "Mustard/Extension/Geant4X/DecayChannel/MuoniumInternalPairProductionDecayChannel.h++"
#include "Mustard/Extension/Geant4X/Particle/Antimuonium.h++"
#include "Mustard/Extension/Geant4X/Particle/Muonium.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPrecisionDecayPhysics.h++"
#include "MACE/SimMACE/PhysicsList.h++"

#include "G4DecayTable.hh"
#include "G4MuonPlus.hh"

#include "fmt/core.h"

#include <stdexcept>
#include <typeinfo>

namespace MACE::SimMACE {

PhysicsList::PhysicsList() :
    PassiveSingleton<PhysicsList>{},
    StandardPhysicsListBase{},
    fMessengerRegister{this} {}

auto PhysicsList::ApplyMACEPxyCut(bool apply) -> void {
    auto& muonPlusIPPDecay{FindIPPDecayChannel<Mustard::Geant4X::MuonInternalPairProductionDecayChannel>(G4MuonPlus::Definition())};
    auto& antimuoniumIPPDecay{FindIPPDecayChannel<Mustard::Geant4X::MuoniumInternalPairProductionDecayChannel>(Mustard::Geant4X::Antimuonium::Definition())};
    if (apply) {
        constexpr auto PxyCut{
            [](auto&& event) {
                using Mustard::PhysicalConstant::c_light;

                const auto& [p, p1, p2, k1, k2]{event.state};

                auto passCut1{true};
                auto passCut2{true};

                const auto mmsB{Detector::Description::MMSField::Instance().FastField()};
                const auto cdcInnerRadius{Detector::Description::CDC::Instance().GasInnerRadius()};
                const auto cdcPxyCut{(cdcInnerRadius / 2) * mmsB * c_light};

                const auto& filter{Detector::Description::Filter::Instance()};
                const auto& solenoid{Detector::Description::Solenoid::Instance()};
                const auto maxPositronRxy{filter.Enabled() ? 5 * filter.Pitch() : solenoid.InnerRadius()};
                const auto maxPositronPxy{maxPositronRxy * solenoid.FastField() * c_light};

                const auto positron1Pxy{muc::hypot(p.x(), p.y())};
                const auto electronPxy{muc::hypot(p1.x(), p1.y())};
                const auto positron2Pxy{muc::hypot(p2.x(), p2.y())};

                passCut1 &= electronPxy > cdcPxyCut and positron1Pxy < cdcPxyCut and positron2Pxy < maxPositronPxy;
                passCut2 &= electronPxy > cdcPxyCut and positron2Pxy < cdcPxyCut and positron1Pxy < maxPositronPxy;

                return passCut1 or passCut2;
            }};
        muonPlusIPPDecay.PassCut(PxyCut);
        antimuoniumIPPDecay.PassCut(PxyCut);
    } else {
        muonPlusIPPDecay.PassCut([](auto&&) { return true; });
        antimuoniumIPPDecay.PassCut([](auto&&) { return true; });
    }
}

template<std::derived_from<G4VDecayChannel> C, std::derived_from<G4ParticleDefinition> P>
auto PhysicsList::FindIPPDecayChannel(const P* particle) -> C& {
    const auto decayTable{particle->GetDecayTable()};
    C* ippDecay{};
    for (int i{}; i < decayTable->entries(); ++i) {
        const auto decay{dynamic_cast<C*>(decayTable->GetDecayChannel(i))};
        if (decay) {
            ippDecay = decay;
            break;
        }
    }
    if (ippDecay == nullptr) {
        throw std::logic_error{fmt::format(
            "MACE::SimMACE::PhysicsList: No decay channel '{}' in particle '{}'",
            typeid(C).name(), typeid(P).name())};
    }
    return *ippDecay;
}

} // namespace MACE::SimMACE
