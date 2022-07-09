#include "MACE/Utility/G4Util/CheckMPIAvailability.hxx"
#include "MACE/Utility/G4Util/MPIExecutive.hxx"
#include "MACE/Utility/MPIUtil/MPIEnvironment.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include <stdexcept>

namespace MACE::Utility::G4Util {

using MPIUtil::MPIEnvironment;

MPIExecutive::MPIExecutive() {
    CheckMPIAvailability();
}

void MPIExecutive::StartInteractiveSession(int argc, char* argv[], const char* initializeMacro) {
    CheckMPIAvailability();
    if (MPIEnvironment::IsParallelized()) {
        auto where = std::string(typeid(*this).name()).append("::").append(__func__).append("(...)");
        if (MPIEnvironment::IsWorldMaster()) {
            G4Exception(where.c_str(),
                        "InteractiveSessionMustBeSerial",
                        JustWarning,
                        "Interactive session must be run with only 1 process.\nThrowing a std::logic_error.");
        }
        throw std::logic_error(where.append(": Interactive session must be serial!"));
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
    CheckMPIAvailability();
    G4UImanager::GetUIpointer()->ExecuteMacroFile(macro);
}

} // namespace MACE::Utility::G4Util
