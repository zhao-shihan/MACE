#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/UtilMPI/CheckedMPICall.hxx"
#include "MACE/Utility/UtilMPI/CheckedMPICallNoExcept.hxx"

#include "mpi.h"

#include <iostream>

namespace MACE::Environment {

ObserverPtr<MPIEnvironment> MPIEnvironment::fgMPIEnvironmentInstance = nullptr;
bool MPIEnvironment::fgMPIEnvironmentFinalized = false;

MPIEnvironment::MPIEnvironment(int argc, char* argv[], std::optional<std::reference_wrapper<CLI::BasicCLI>> optCLI,
                               VerboseLevel verboseLevel, bool printStartupMessage) :
    BasicEnvironment(argc, argv, optCLI, verboseLevel, false),
    fWorldCommRank(-1),
    fWorldCommSize(-1),
    fProcessorName() {
    // Initialize MPI and properties of MPI_COMM_WORLD
    InitializeMPIAndWorldProperties(argc, argv);
    // Set instance pointer, initialize check has been performed at BasicEnvironment constructor
    fgMPIEnvironmentInstance = this;
    // Print startup message
    if (printStartupMessage and IsWorldMaster()) {
        PrintStartupMessageSplitLine();
        PrintStartupMessageBody(argc, argv);
        PrintStartupMessageSplitLine();
    }
}

MPIEnvironment::~MPIEnvironment() {
    // Finalize MPI
    MACE_CHECKED_MPI_CALL_NOEXCEPT(MPI_Finalize)
    // Update status
    fgMPIEnvironmentFinalized = true;
}

void MPIEnvironment::PrintStartupMessageBody(int argc, char* argv[]) const {
    BasicEnvironment::PrintStartupMessageBody(argc, argv);
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(GetVerboseLevel(), Error, std::cout)
        << '\n'
        << " Parallelized by MPI " << MPI_VERSION << '.' << MPI_SUBVERSION << '\n'
        << " Size of the MPI world communicator: " << fWorldCommSize << std::endl;
}

void MPIEnvironment::InitializeMPIAndWorldProperties(int argc, char** argv) {
    // Confirm MPI condition
    int mpiInitialized;
    MACE_CHECKED_MPI_CALL(MPI_Initialized, &mpiInitialized)
    if (mpiInitialized) {
        throw std::logic_error("MACE::Environment::MPIEnvironment: Trying to call MPI_Init twice");
    }
    // Initialize MPI
    MACE_CHECKED_MPI_CALL(MPI_Init, &argc, &argv)
    // Initialize fWorldCommRank
    MACE_CHECKED_MPI_CALL(MPI_Comm_rank, MPI_COMM_WORLD, &fWorldCommRank)
    // Initialize fWorldCommSize
    MACE_CHECKED_MPI_CALL(MPI_Comm_size, MPI_COMM_WORLD, &fWorldCommSize)
    // Initialize fProcessorName
    char processorName[MPI_MAX_PROCESSOR_NAME];
    int processorNameLength;
    MACE_CHECKED_MPI_CALL(MPI_Get_processor_name, processorName, &processorNameLength)
    fProcessorName.assign(processorName, processorNameLength);
    fProcessorName.shrink_to_fit();
}

} // namespace MACE::Environment
