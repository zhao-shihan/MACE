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

} // namespace MACE::SimulationG4
