#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannelMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

MuonInternalPairProductionDecayChannelMessenger::MuonInternalPairProductionDecayChannelMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fMetropolisDelta{},
    fMetropolisDiscard{},
    fApplyMACESpecificPxyCut{},
    fApplyMACESpecificPzCut{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuonDecay/IPPDecay/");
    fDirectory->SetGuidance("Muon(ium) internal pair production decay channel (mu->eeevv / M->eeevve).");

    fMetropolisDelta = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuonDecay/IPPDecay/MetropolisDelta", this);
    fMetropolisDelta->SetGuidance("Set the 1D-displacement (20 dimensions in total) of the random walk in the Metropolis algorithm. "
                                  "Smaller values enhance autocorrelation, while larger values decrease performance and lead to biased results. "
                                  "The typical value is below 0.05.");
    fMetropolisDelta->SetParameterName("delta", false);
    fMetropolisDelta->SetRange("0 < delta && delta < 0.5");
    fMetropolisDelta->AvailableForStates(G4State_Idle);

    fMetropolisDiscard = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Physics/MuonDecay/IPPDecay/MetropolisDiscard", this);
    fMetropolisDiscard->SetGuidance("Set how many samples are discarded between two outputs in the Metropolis algorithm. "
                                    "The more samples are discarded, the less significant the autocorrelation is, but it will reduce the performance of sampling. "
                                    "When the total number of samples (number of IPP decay events) is small, a larger number of discards should be set. "
                                    "When the number of samples is large, the number of discards can be appropriately reduced. "
                                    "This value is also related to the delta of the random walk, and the smaller the delta, the more samples that should be discarded.");
    fMetropolisDiscard->SetParameterName("n", false);
    fMetropolisDiscard->SetRange("n >= 0");
    fMetropolisDiscard->AvailableForStates(G4State_Idle);

    fApplyMACESpecificPxyCut = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuonDecay/IPPDecay/ApplyMACESpecificPxyCut", this);
    fApplyMACESpecificPxyCut->SetGuidance("If true, apply MACE specific transverse momentum cut to mu+ IPP decay products. Check source code for details.");
    fApplyMACESpecificPxyCut->SetParameterName("apply", false);
    fApplyMACESpecificPxyCut->AvailableForStates(G4State_Idle);

    fApplyMACESpecificPzCut = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuonDecay/IPPDecay/ApplyMACESpecificPzCut", this);
    fApplyMACESpecificPzCut->SetGuidance("If true, apply MACE specific longtitude momentum cut to mu+ IPP decay products. Check source code for details.");
    fApplyMACESpecificPzCut->SetParameterName("apply", false);
    fApplyMACESpecificPzCut->AvailableForStates(G4State_Idle);
}

MuonInternalPairProductionDecayChannelMessenger::~MuonInternalPairProductionDecayChannelMessenger() = default;

auto MuonInternalPairProductionDecayChannelMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fMetropolisDelta.get()) {
        Deliver<MuonInternalPairProductionDecayChannel>([&](auto&& r) {
            r.MetropolisDelta(fMetropolisDelta->GetNewDoubleValue(value));
        });
    } else if (command == fMetropolisDiscard.get()) {
        Deliver<MuonInternalPairProductionDecayChannel>([&](auto&& r) {
            r.MetropolisDiscard(fMetropolisDiscard->GetNewIntValue(value));
        });
    } else if (command == fApplyMACESpecificPxyCut.get()) {
        Deliver<MuonInternalPairProductionDecayChannel>([&](auto&& r) {
            r.ApplyMACESpecificPxyCut(fApplyMACESpecificPxyCut->GetNewBoolValue(value));
        });
    } else if (command == fApplyMACESpecificPzCut.get()) {
        Deliver<MuonInternalPairProductionDecayChannel>([&](auto&& r) {
            r.ApplyMACESpecificPzCut(fApplyMACESpecificPzCut->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
