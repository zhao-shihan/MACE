#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimulationG4/MPIExecutive.hxx"

#include <stdexcept>

namespace MACE::SimulationG4 {

using MACE::Environment::MPIEnvironment;

MPIExecutive::MPIExecutive() :
    fG4UIManager(G4UImanager::GetUIpointer()) {}

void MPIExecutive::CheckSequential() const {
    if (MPIEnvironment::IsParallel()) {
        auto where = std::string(typeid(*this).name()).append("::").append(__func__);
        if (MPIEnvironment::IsWorldMaster()) {
            G4Exception(where.c_str(),
                        "InteractiveSessionMustBeSerial",
                        JustWarning,
                        "Interactive session must be run with only 1 process.\nThrowing an instance of std::logic_error.");
        }
        throw std::logic_error(where.append(": Interactive session must be serial"));
    }
}

} // namespace MACE::SimulationG4
