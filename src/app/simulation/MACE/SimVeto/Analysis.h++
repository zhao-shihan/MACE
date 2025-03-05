#pragma once

#include "MACE/Data/SensorHit.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/SimVertex.h++"
#include "MACE/SimVeto/Messenger/AnalysisMessenger.h++"

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
class VetoStripHit;
class VetoPMHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::SimVeto {

class Analysis final : public Mustard::Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }
    // auto CoincidenceWithECAL(G4bool val) -> void { fCoincidenceWithECAL = val; }
    // auto CoincidenceWithMCP(G4bool val) -> void { fCoincidenceWithMCP = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitPrimaryVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>& data) -> void { fPrimaryVertex = &data; }
    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitVetoStripHC(const std::vector<gsl::owner<VetoStripHit*>>& hc) -> void { fVetoStripHit = &hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = {}) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileMode;
    // G4bool fCoincidenceWithECAL;
    // G4bool fCoincidenceWithMCP;

    std::filesystem::path fLastUsedFullFilePath;

    gsl::owner<TFile*> fFile;
    std::optional<Mustard::Data::Output<Data::SimPrimaryVertex>> fPrimaryVertexOutput;
    std::optional<Mustard::Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Mustard::Data::Output<Data::VetoSimHit>> fVetoSimHitOutput;
    std::optional<Mustard::Data::Output<Data::VetoPMHit>> fVetoPMHitOutput;

    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>* fPrimaryVertex;
    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<VetoStripHit*>>* fVetoStripHit;
    const std::vector<gsl::owner<VetoPMHit*>>* fVetoPMHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimECAL
