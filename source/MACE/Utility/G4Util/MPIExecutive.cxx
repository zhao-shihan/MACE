#include "MACE/Utility/G4Util/CheckMPIAvailability.hxx"
#include "MACE/Utility/G4Util/MPIExecutive.hxx"
#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "mpi.h"

namespace MACE::Utility::G4Util {

using namespace MPIUtil;

MPIExecutive::MPIExecutive(int argc, char** argv) :
    fCommRank((CheckMPIAvailability(), MPICommRank(MPI_COMM_WORLD))),
    fCommSize(MPICommSize(MPI_COMM_WORLD)),
    fArgc(argc),
    fArgv(argv) {}

void MPIExecutive::StartInteractiveSession(const char* initializeMacro) {
    CheckMPIAvailability();

    if (fCommSize > 1) {
        if (fCommRank == 0) {
            G4Exception("MACE::Utility::G4Util::MPIExecutive::StartInteractiveSession(...)",
                        "InteractiveSessionMustBeSerial",
                        FatalException,
                        "Interactive session must be run with only 1 process.");
        }
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

} // namespace MACE::Utility::G4Util
