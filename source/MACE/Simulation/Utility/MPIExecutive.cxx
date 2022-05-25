#include "MACE/Simulation/Utility/CheckMPIAvailability.hxx"
#include "MACE/Simulation/Utility/MPIExecutive.hxx"
#include "MACE/Utility/MPITool/CommonMPIWrapper.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "mpi.h"

namespace MACE::Simulation::Utility {

MPIExecutive::MPIExecutive(int argc, char** argv) :
    fArgc(argc),
    fArgv(argv) {
    CheckMPIAvailability();
}

void MPIExecutive::StartInteractiveSession(const char* initializeMacro) {
    CheckMPIAvailability();

    if (MACE::Utility::MPITool::MPICommSize(MPI_COMM_WORLD) > 1) {
        G4Exception("MACE::Simulation::Utility::MPIExecutive::StartInteractiveSession(...)",
                    "InteractiveSessionMustBeSerial",
                    FatalException,
                    "Interactive session must be run with only 1 process.");
    }

    const auto uiExecutive = std::make_unique<G4UIExecutive>(fArgc, fArgv);
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

} // namespace MACE::Simulation::Utility
