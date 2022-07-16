#include "MACE/Environment/MPIEnvironment.hxx"

#include "mpi.h"

#include <iostream>
#include <stdexcept>

namespace MACE::Environment {

ObserverPtr<MPIEnvironment> MPIEnvironment::fgMPIEnvironmentInstance = nullptr;
bool MPIEnvironment::fgMPIEnvironmentFinalized = false;

MPIEnvironment::MPIEnvironment(int& argc, char**& argv, VerboseLevel verboseLevel, bool printStartupMessage) :
    BasicEnvironment(argc, argv, verboseLevel, false),
    fWorldCommRank(-1),
    fWorldCommSize(-1),
    fProcessorName() {
    // Confirm MPI condition
    int mpiInitialized;
    MPI_Initialized(&mpiInitialized);
    if (mpiInitialized) {
        throw std::logic_error("MACE::Environment::MPIEnvironment: Trying to call MPI_Init twice");
    }
    // Initialize MPI
    MPI_Init(&argc, &argv);
    // Initialize fWorldCommRank
    MPI_Comm_rank(MPI_COMM_WORLD, &fWorldCommRank);
    // Initialize fWorldCommSize
    MPI_Comm_size(MPI_COMM_WORLD, &fWorldCommSize);
    // Initialize fProcessorName
    char processorName[MPI_MAX_PROCESSOR_NAME];
    int processorNameLength;
    MPI_Get_processor_name(processorName, &processorNameLength);
    fProcessorName.assign(processorName, processorNameLength);
    fProcessorName.shrink_to_fit();
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
    MPI_Finalize();
    // Update status
    fgMPIEnvironmentFinalized = true;
}

void MPIEnvironment::PrintStartupMessageBody(int argc, char* argv[]) const {
    BasicEnvironment::PrintStartupMessageBody(argc, argv);
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(std::cout, Error, GetVerboseLevel())
        << '\n'
        << " Parallelized by MPI " << MPI_VERSION << '.' << MPI_SUBVERSION << '\n'
        << " Size of the MPI world communicator: " << fWorldCommSize << std::endl;
}

} // namespace MACE::Environment
