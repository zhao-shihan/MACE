#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimulationG4/MPIExecutive.hxx"

#include <stdexcept>

namespace MACE::SimulationG4 {

using MACE::Environment::MPIEnvironment;

void MPIExecutive::CheckSequential() const {
    if (MPIEnvironment::IsParallel()) {
        std::string where("MACE::SimulationG4::MPIExecutive::CheckSequential");
        if (MPIEnvironment::IsWorldMaster()) {
            G4Exception(where.c_str(),
                        "InteractiveSessionMustBeSequential",
                        JustWarning,
                        "Interactive session must be run with only 1 process.\nThrowing an instance of std::logic_error.");
        }
        throw std::logic_error(where.append(": Interactive session must be sequential"));
    }
}

void MPIExecutive::Execute(const std::string& macro) {
    if (not macro.empty()) {
        G4UImanager::GetUIpointer()->ExecuteMacroFile(macro.c_str());
    }
}

bool MPIExecutive::ExecuteCommand(const std::string& command) {
    if (command.empty() or
        std::ranges::all_of(command.substr(0, command.find_first_of('#')),
                            [](unsigned char ch) {
                                return std::isspace(ch);
                            })) {
        MACE_ENVIRONMENT_CONTROLLED_OUT(Error, G4cout) << command << G4endl;
        return true;
    }
    if (const auto commandStatus = G4UImanager::GetUIpointer()->ApplyCommand(command);
        commandStatus == fCommandSucceeded) [[likely]] {
        return true;
    } else {
        MACE_ENVIRONMENT_CONTROLLED_OUT(Error, G4cerr)
            << "MACE::SimulationG4::MPIExecutive::Execute: Command \"" << command << "\" failed (G4UIcommandStatus: " << commandStatus << ')' << std::endl;
        return false;
    }
}

} // namespace MACE::SimulationG4
