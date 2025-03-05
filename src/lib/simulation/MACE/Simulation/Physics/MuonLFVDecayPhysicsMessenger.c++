// -*- C++ -*-
//
// Copyright 2020-2024  The Mustard development team
//
// This file is part of Mustard, an offline software framework for HEP experiments.
//
// Mustard is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Mustard is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Mustard. If not, see <https://www.gnu.org/licenses/>.

#include "MACE/Simulation/Physics/MuonLFVDecayPhysics.h++"
#include "MACE/Simulation/Physics/MuonLFVDecayPhysicsMessenger.h++"

#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Physics {

MuonLFVDecayPhysicsMessenger::MuonLFVDecayPhysicsMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fDoubleRadiativeDecayBR{},
    fUpdateDecayBR{},
    fResetDecayBR{} {

    fDirectory = std::make_unique<G4UIdirectory>("/Mustard/Physics/MuonDecay/");
    fDirectory->SetGuidance("About muon(ium) decay channel and decay generators.");

    fDoubleRadiativeDecayBR = std::make_unique<G4UIcmdWithADouble>("/Mustard/Physics/MuonDecay/DoubleRadiativeDecay/BR", this);
    fDoubleRadiativeDecayBR->SetGuidance("Set branching ratio for muon double radiative decay channel.");
    fDoubleRadiativeDecayBR->SetParameterName("BR", false);
    fDoubleRadiativeDecayBR->SetRange("0 <= BR && BR <= 1");
    fDoubleRadiativeDecayBR->AvailableForStates(G4State_PreInit, G4State_Idle);

    fUpdateDecayBR = std::make_unique<G4UIcmdWithoutParameter>("/Mustard/Physics/MuonDecay/UpdateDecayBR", this);
    fUpdateDecayBR->SetGuidance("Update decay branching ratios.");
    fUpdateDecayBR->AvailableForStates(G4State_Idle);

    fResetDecayBR = std::make_unique<G4UIcmdWithoutParameter>("/Mustard/Physics/MuonDecay/ResetDecayBR", this);
    fResetDecayBR->SetGuidance("Reset decay branching ratios.");
    fResetDecayBR->AvailableForStates(G4State_Idle);
}

MuonLFVDecayPhysicsMessenger::~MuonLFVDecayPhysicsMessenger() = default;

auto MuonLFVDecayPhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fDoubleRadiativeDecayBR.get()) {
        Deliver<MuonLFVDecayPhysics>([&](auto&& r) {
            r.DoubleRadiativeDecayBR(fDoubleRadiativeDecayBR->GetNewDoubleValue(value));
        });
    } else if (command == fUpdateDecayBR.get()) {
        Deliver<MuonLFVDecayPhysics>([&](auto&& r) {
            r.UpdateDecayBR();
        });
    } else if (command == fResetDecayBR.get()) {
        Deliver<MuonLFVDecayPhysics>([&](auto&& r) {
            r.ResetDecayBR();
        });
    }
}

} // namespace MACE::inline Simulation::inline Physics
