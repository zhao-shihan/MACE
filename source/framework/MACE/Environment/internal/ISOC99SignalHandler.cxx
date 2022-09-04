#if MACE_SIGNAL_HANDLER

    #include "MACE/Environment/internal/ISOC99SignalHandler.hxx"
    #include "MACE/Utility/PrintStackTrace.hxx"

    #include <csignal>
    #include <cstdlib>
    #include <iostream>

namespace MACE::Environment::internal {

extern "C" {

[[noreturn]] void MACE_ISOC99_SIGINT_SIGTERM_Handler(int sig) {
    switch (sig) {
    case SIGINT:
        std::cerr << "\n ***** INTERRUPT (SIGINT) *****\n";
        break;
    case SIGTERM:
        std::cerr << "\n ***** TERMINATE (SIGTERM) *****\n";
        break;
    }
    std::cerr << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
    #ifndef __MINGW32__
    std::quick_exit(EXIT_FAILURE);
    #else
    std::_Exit(EXIT_FAILURE);
    #endif
}

[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int) {
    std::signal(SIGABRT, SIG_DFL);
    std::cerr << "\n ***** ABORT (SIGABRT) *****\n"
              << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
    std::abort();
}

[[noreturn]] void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) {
    std::signal(SIGABRT, SIG_DFL);
    switch (sig) {
    case SIGFPE:
        std::cerr << "\n ***** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) *****\n";
        break;
    case SIGILL:
        std::cerr << "\n ***** ILLEGAL INSTRUCTION (SIGILL) *****\n";
        break;
    case SIGSEGV:
        std::cerr << "\n ***** SEGMENTATION VIOLATION (SIGSEGV) *****\n";
        break;
    }
    std::cerr << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
    std::abort();
}

} // extern "C"

} // namespace MACE::Environment::internal

#endif
