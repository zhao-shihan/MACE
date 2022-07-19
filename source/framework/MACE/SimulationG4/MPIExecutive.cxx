#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimulationG4/detail/CheckMPIAvailability.hxx"
#include "MACE/SimulationG4/MPIExecutive.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include <stdexcept>

namespace MACE::SimulationG4 {

using MACE::Environment::MPIEnvironment;

MPIExecutive::MPIExecutive() {
    Detail::CheckMPIAvailability();
}

void MPIExecutive::StartInteractiveSession(int argc, char* argv[], const char* initializeMacro) {
    Detail::CheckMPIAvailability();
    if (MPIEnvironment::IsParallelized()) {
        auto where = std::string(typeid(*this).name()).append("::").append(__func__);
        if (MPIEnvironment::IsWorldMaster()) {
            G4Exception(where.c_str(),
                        "InteractiveSessionMustBeSerial",
                        JustWarning,
                        "Interactive session must be run with only 1 process.\nThrowing an instance of std::logic_error.");
        }
        throw std::logic_error(where.append(": Interactive session must be serial"));
    }

    const auto uiExecutive = std::make_unique<G4UIExecutive>(argc, argv);
    const auto visExecutive = std::make_unique<G4VisExecutive>();
    visExecutive->Initialize();
    if (initializeMacro != nullptr) {
        G4UImanager::GetUIpointer()->ExecuteMacroFile(initializeMacro);
    }
    uiExecutive->SessionStart();
}

void MPIExecutive::StartBatchSession(const char* macro) {
    Detail::CheckMPIAvailability();
    G4UImanager::GetUIpointer()->ExecuteMacroFile(macro);
}

} // namespace MACE::SimulationG4
