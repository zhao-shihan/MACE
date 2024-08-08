#pragma once

#include "MACE/Data/SensorHit.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/SimVertex.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Messenger/AnalysisMessenger.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <optional>
#include <utility>

class TFile;

namespace MACE::inline Simulation::inline Hit {
class ECalHit;
class ECalPMTHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::PhaseI::SimMACEPhaseI {

class Analysis final : public Mustard::Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }
    auto CoincidenceWithECal(G4bool val) -> void { fCoincidenceWithECal = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitPrimaryVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>& data) -> void { fPrimaryVertex = &data; }
    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitECalHC(const std::vector<gsl::owner<ECalHit*>>& hc) -> void { fECalHit = &hc; }
    auto SubmitECalPMTHC(const std::vector<gsl::owner<ECalPMTHit*>>& hc) -> void { fECalPMTHit = &hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = {}) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileMode;
    G4bool fCoincidenceWithECal;

    std::filesystem::path fLastUsedFullFilePath;

    gsl::owner<TFile*> fFile;
    std::optional<Mustard::Data::Output<Data::SimPrimaryVertex>> fPrimaryVertexOutput;
    std::optional<Mustard::Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Mustard::Data::Output<Data::ECalSimHit>> fECalSimHitOutput;
    std::optional<Mustard::Data::Output<Data::ECalPMTHit>> fECalPMTHitOutput;

    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>* fPrimaryVertex;
    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<ECalHit*>>* fECalHit;
    const std::vector<gsl::owner<ECalPMTHit*>>* fECalPMTHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::PhaseI::SimMACEPhaseI
