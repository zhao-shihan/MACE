#if MACE_SIGNAL_HANDLER

    #include "MACE/Cxx2b/PrintStackTrace.hxx"
    #include "MACE/Environment/internal/ISOC99SignalHandler.hxx"

    #include <csignal>
    #include <cstdlib>
    #include <iostream>

namespace MACE::Environment::Internal {

extern "C" {

[[noreturn]] void MACE_ISOC99SignalHandler(int sig) {
    switch (sig) {
    case SIGABRT:
        std::cerr << "\n ***** ABORT (SIGABRT) *****\n";
        break;
    case SIGFPE:
        std::cerr << "\n ***** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) *****\n";
        break;
    case SIGILL:
        std::cerr << "\n ***** ILLEGAL INSTRUCTION (SIGILL) *****\n";
        break;
    case SIGINT:
        std::cerr << "\n ***** INTERRUPT (SIGINT) *****\n";
        break;
    case SIGSEGV:
        std::cerr << "\n ***** SEGMENTATION VIOLATION (SIGSEGV) *****\n";
        break;
    case SIGTERM:
        std::cerr << "\n ***** TERMINATE (SIGTERM) *****\n";
        break;
    }
    std::cerr << std::endl;
    Cxx2b::PrintStackTrace();
    std::cerr << std::endl;
    std::quick_exit(sig);
}

} // extern "C"

} // namespace MACE::Environment::Internal

#endif
