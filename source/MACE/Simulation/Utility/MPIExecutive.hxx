#pragma once

namespace MACE::Simulation::Utility {

class MPIExecutive final {
public:
    static MPIExecutive& Instance();

private:
    MPIExecutive();
    ~MPIExecutive() = default;
    MPIExecutive(const MPIExecutive&) = delete;
    MPIExecutive& operator=(const MPIExecutive&) = delete;

public:
    void StartInteractiveSession(const int& argc, char** const& argv, const char* initializeMacro = nullptr);
    void StartBatchSession(const char* macro);
};

} // namespace MACE::Simulation::Utility
