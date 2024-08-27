#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/SimMACE/PhysicsList.h++"

#include "Mustard/Extension/Geant4X/DecayChannel/MuonInternalConversionDecayChannel.h++"
#include "Mustard/Extension/Geant4X/DecayChannel/MuoniumInternalConversionDecayChannel.h++"
#include "Mustard/Extension/Geant4X/Particle/Muonium.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPrecisionDecayPhysics.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/PhysicalConstant.h++"

#include "G4DecayTable.hh"
#include "G4MuonPlus.hh"

#include "fmt/core.h"

#include <stdexcept>
#include <typeinfo>

namespace MACE::SimMACE {

using namespace Mustard::LiteralUnit::Energy;

PhysicsList::PhysicsList() :
    PassiveSingleton<PhysicsList>{},
    StandardPhysicsListBase{},
    fMACECutMaxLowerPositronEk{10_keV},
    fMessengerRegister{this} {}

auto PhysicsList::ApplyMACECut(bool apply) -> void {
    auto& muonPlusICDecay{FindICDecayChannel<Mustard::Geant4X::MuonInternalConversionDecayChannel>(G4MuonPlus::Definition())};
    auto& muoniumICDecay{FindICDecayChannel<Mustard::Geant4X::MuoniumInternalConversionDecayChannel>(Mustard::Geant4X::Muonium::Definition())};
    if (apply) {
        const auto PxyCut{
            [this](auto&& event) {
                using Mustard::PhysicalConstant::c_light;
                using Mustard::PhysicalConstant::electron_mass_c2;

                const auto mmsB{Detector::Description::MMSField::Instance().FastField()};
                const auto& cdc{Detector::Description::CDC::Instance()};
                const auto cdcInnerPxyCut{(cdc.GasInnerRadius() / 2) * mmsB * c_light};
                const auto cdcOuterPxyCut{((cdc.GasOuterRadius() - cdc.GasInnerRadius()) / 2) * mmsB * c_light};

                // .         e+ e-  e+  v   v
                const auto& [p, p1, p2, k1, k2]{event};

                // electronPxy > cdcOuterPxyCut and
                // ((positron1Pxy < cdcInnerPxyCut and positron2Ek < fMACECutMaxLowerPositronEk) or
                //  (positron2Pxy < cdcInnerPxyCut and positron1Ek < fMACECutMaxLowerPositronEk));
                return muc::hypot(p1.x(), p1.y()) > cdcOuterPxyCut and
                       ((muc::hypot(p.x(), p.y()) < cdcInnerPxyCut and p2.e() - electron_mass_c2 < fMACECutMaxLowerPositronEk) or
                        (muc::hypot(p2.x(), p2.y()) < cdcInnerPxyCut and p.e() - electron_mass_c2 < fMACECutMaxLowerPositronEk));
            }};
        muonPlusICDecay.PassCut(PxyCut);
        muoniumICDecay.PassCut(PxyCut);
    } else {
        muonPlusICDecay.PassCut([](auto&&) { return true; });
        muoniumICDecay.PassCut([](auto&&) { return true; });
    }
}

template<std::derived_from<G4VDecayChannel> C, std::derived_from<G4ParticleDefinition> P>
auto PhysicsList::FindICDecayChannel(const P* particle) -> C& {
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
