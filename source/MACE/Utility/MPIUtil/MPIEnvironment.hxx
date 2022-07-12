#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include <string>

namespace MACE::Utility::MPIUtil {

/// @brief Helper class manages MPI environment in RAII style.
/// @details The constructor calls MPI_Init and destructor calls MPI_Finalize.
/// Thus the MPI environment is bound to MPIEnvironment object's lifetime, or
/// we say this class handles MPI environment in RAII style.
/// The usage is clear: define (usually at the very beginning of main function)
/// a MPIEnvironment object in the main function, and MPI is accessible in the
/// program.
/// Example:
///   In balabala.cxx:
///     int main(int argc, char* argv[]) {
///         MPIEnvironment mpiEnvironment(argc, argv);
///
///         ( ... program code, MPI routine is already available. )
///
///     }
/// This class also provides some static member function for accessing some
/// properties inside MPI_COMM_WORLD (e.g. size, rank), they are initialized
/// in the main function. These value is cached and access them should be
/// faster than call MPI_comm_rank(...) or MPI_Get_processor_name(...), etc.
/// (and apparently more convenient). Static member functions:
/// IsWorldMaster/IsWorldWorker identifies current rank is master/worker by
/// checking its rank inside world communicator (master == 0, worker > 1). 
/// IsSerialized/IsParallelized identifies whether the program actually running
/// "truly parallelized" (that is, starts with mpirun or etc.) by checking the
/// size of the world communicator (serialized == 1, parallelized > 1).
/// @attention The constructor should only be called only ONCE, during the
/// whole period of execution. Otherwise it will throw an instance of 
/// std::logic_error. Or we could say this class is a implitic singleton, and
/// should have only one instance in the whole program space-time period.
/// @attention Call to any static member function other than Available() out of
/// the lifetime of the MPIEnvironment instance has undefined behavior
/// (null pointer dereference).
/// @attention Do not declare MPIEnvironment as a global static object, since
/// MPI_init needs to be called after main is called. Other behavior results in
/// the constructor of MPIEnvironment is called before main is called should be
/// carefully avoided.
///
class MPIEnvironment final {
public:
    MPIEnvironment(int& argc, char**& argv);
    ~MPIEnvironment();
    MPIEnvironment(const MPIEnvironment&) = delete;
    MPIEnvironment& operator=(const MPIEnvironment&) = delete;

    static auto Available() { return fgInstance != nullptr; }
    static const auto& WorldCommRank() { return fgInstance->fWorldCommRank; }
    static const auto& WorldCommSize() { return fgInstance->fWorldCommSize; }
    static const auto& ProcessorName() { return fgInstance->fProcessorName; }
    static auto IsWorldMaster() { return WorldCommRank() == 0; }
    static auto IsWorldWorker() { return WorldCommRank() > 0; }
    static auto IsSerialized() { return WorldCommSize() == 1; }
    static auto IsParallelized() { return WorldCommSize() > 1; }

private:
    int fWorldCommRank;
    int fWorldCommSize;
    std::string fProcessorName;

    static ObserverPtr<MPIEnvironment> fgInstance;
};

} // namespace MACE::Utility::MPIUtil
