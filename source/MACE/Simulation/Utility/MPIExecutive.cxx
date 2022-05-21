#include "MACE/Simulation/Utility/CheckMPIAvailability.hxx"
#include "MACE/Simulation/Utility/MPIExecutive.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "mpi.h"

namespace MACE::Simulation::Utility {

MPIExecutive& MPIExecutive::Instance() {
    static MPIExecutive instance;
    return instance;
}

MPIExecutive::MPIExecutive() {
    CheckMPIAvailability();
}

void MPIExecutive::StartInteractiveSession(const int& argc, char** const& argv, const char* initializeMacro) {
    CheckMPIAvailability();

    int commSize;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    if (commSize > 1) {
        G4Exception("MACE::Simulation::Utility::MPIExecutive::StartInteractiveSession(...)",
                    "InteractiveSessionMustBeSerial",
                    FatalException,
                    "Interactive session must be run with only 1 process.");
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

} // namespace MACE::Simulation::Utility
