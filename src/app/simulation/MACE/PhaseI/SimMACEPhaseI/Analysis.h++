#pragma once

#include "MACE/Data/SensorHit.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/SimVertex.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Messenger/AnalysisMessenger.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Simulation/AnalysisBase.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <optional>
#include <utility>

class TFile;

namespace MACE::inline Simulation::inline Hit {
class MRPCHit;
class ECALHit;
class ECALPMHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::PhaseI::SimMACEPhaseI {

class Analysis final : public Mustard::Simulation::AnalysisBase<Analysis, "SimMACEPhaseI"> {
public:
    Analysis();

    auto CoincidenceWithMRPC(G4bool val) -> void { fCoincidenceWithMRPC = val; }
    auto CoincidenceWithECAL(G4bool val) -> void { fCoincidenceWithECAL = val; }

    auto SubmitPrimaryVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>& data) -> void { fPrimaryVertex = &data; }
    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitMRPCHC(const std::vector<gsl::owner<MRPCHit*>>& hc) -> void { fMRPCHit = &hc; }
    auto SubmitECALHC(const std::vector<gsl::owner<ECALHit*>>& hc) -> void { fECALHit = &hc; }
    auto SubmitECALPMHC(const std::vector<gsl::owner<ECALPMHit*>>& hc) -> void { fECALPMHit = &hc; }

    auto RunBeginUserAction(int runID) -> void override;
    auto EventEndUserAction() -> void override;
    auto RunEndUserAction(int) -> void override;

private:
    G4bool fCoincidenceWithMRPC;
    G4bool fCoincidenceWithECAL;

    std::optional<Mustard::Data::Output<Data::SimPrimaryVertex>> fPrimaryVertexOutput;
    std::optional<Mustard::Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Mustard::Data::Output<Data::MRPCSimHit>> fMRPCSimHitOutput;
    std::optional<Mustard::Data::Output<Data::ECALSimHit>> fECALSimHitOutput;
    std::optional<Mustard::Data::Output<Data::ECALPMHit>> fECALPMHitOutput;

    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>* fPrimaryVertex;
    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<MRPCHit*>>* fMRPCHit;
    const std::vector<gsl::owner<ECALHit*>>* fECALHit;
    const std::vector<gsl::owner<ECALPMHit*>>* fECALPMHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::PhaseI::SimMACEPhaseI
