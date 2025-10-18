#pragma once

#include "MACE/Data/SensorHit.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/SimVertex.h++"
#include "MACE/SimVeto/Messenger/AnalysisMessenger.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Simulation/AnalysisBase.h++"

#include "muc/ptrvec"

#include "gsl/gsl"

#include <filesystem>
#include <utility>
#include <vector>

class TFile;

namespace MACE::inline Simulation::inline Hit {
class VetoHit;
class VetoPMHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::SimVeto {

class Analysis final : public Mustard::Simulation::AnalysisBase<Analysis, "SimVeto"> {
public:
    Analysis();

    // auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    // auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }

    auto SubmitPrimaryVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>& data) -> void { fPrimaryVertex = &data; }
    // auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitVetoHC(const std::vector<gsl::owner<VetoHit*>>& hc) -> void { fVetoHit = &hc; }
    auto SubmitVetoPMHC(const std::vector<gsl::owner<VetoPMHit*>>& hc) -> void { fVetoPMHit = &hc; }
    auto CoincidenceWithVeto(bool var) -> void { fCoincidenceWithVeto = var; }

    auto RunBeginUserAction(int runID) -> void override;
    auto EventEndUserAction() -> void override;
    auto RunEndUserAction(int) -> void override;

private:
    // std::filesystem::path fFilePath;
    // std::string fFileMode;
    bool fCoincidenceWithVeto;

    // std::filesystem::path fLastUsedFullFilePath;

    // gsl::owner<TFile*> fFile;
    std::optional<Mustard::Data::Output<Data::SimPrimaryVertex>> fPrimaryVertexOutput;
    // std::optional<Mustard::Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Mustard::Data::Output<Data::VetoSimHit>> fVetoSimHitOutput;
    std::optional<Mustard::Data::Output<Data::VetoPMHit>> fVetoPMHitOutput;

    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>* fPrimaryVertex;
    // const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<VetoHit*>>* fVetoHit;
    const std::vector<gsl::owner<VetoPMHit*>>* fVetoPMHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimVeto
