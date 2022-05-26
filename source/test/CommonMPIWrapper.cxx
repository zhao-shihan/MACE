#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"

#include <iostream>

using namespace MACE::Utility::MPIUtil;

int main(int argc, char* argv[]) {
    std::cout << "MPIInitialized(): " << MPIInitialized() << std::endl;
    std::cout << "MPIFinalized(): " << MPIFinalized() << std::endl;

    MPI_Init(&argc, &argv);

    std::cout << "MPIInitialized(): " << MPIInitialized() << std::endl;
    std::cout << "MPIFinalized(): " << MPIFinalized() << std::endl;

    const auto [processorName, nameLength] = MPIGetProcessorName<MPI_MAX_PROCESSOR_NAME>();
    std::cout << "MPIGetProcessorName<MPI_MAX_PROCESSOR_NAME>(): [" << processorName.data() << ", " << nameLength << ']' << std::endl;
    std::cout << "MPIGetProcessorNameString(): " << MPIGetProcessorNameString() << std::endl;

    MPI_Finalize();

    std::cout << "MPIInitialized(): " << MPIInitialized() << std::endl;
    std::cout << "MPIFinalized(): " << MPIFinalized() << std::endl;
}
