namespace MACE::Environment {

template<typename... Args>
void MPIEnvironment::CheckedMPICall(const char* funcName, int (*MPIFunc)(std::decay_t<Args>...), Args&&... args) {
    int error = MPIFunc(std::forward<Args>(args)...);
    if (error != 0) {
        throw std::runtime_error(std::string("MACE::Environment::MPIEnvironment: Error calling ")
                                     .append(funcName)
                                     .append(" (Error code: ")
                                     .append(std::to_string(error))
                                     .append(")"));
    }
}

} // namespace MACE::Environment
