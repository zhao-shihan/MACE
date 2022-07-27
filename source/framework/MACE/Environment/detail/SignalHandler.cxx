#if MACE_SIGNAL_HANDLER

    #include "MACE/Environment/detail/SignalHandler.hxx"
    #include "MACE/Cxx2b/PrintStackTrace.hxx"

    #include <csignal>
    #include <cstdlib>
    #include <iostream>

namespace MACE::Environment::Detail {

extern "C" {

[[noreturn]] void MACE_ISOC99_SIGINT_Handler(int) {
    std::cerr << "\n *** INTERRUPT (SIGINT) ***\n"
              << std::endl;
    Cxx2b::PrintStackTrace();
    std::cerr << std::endl;
    std::exit(EXIT_FAILURE);
}

[[noreturn]] void MACE_ISOC99_SIGTERM_Handler(int) {
    std::cerr << "\n *** TERMINATE (SIGTERM) ***\n"
              << std::endl;
    Cxx2b::PrintStackTrace();
    std::cerr << std::endl;
    std::quick_exit(EXIT_FAILURE);
}

[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int) {
    std::signal(SIGABRT, SIG_DFL);
    std::cerr << "\n *** ABORT (SIGABRT) ***\n"
              << std::endl;
    Cxx2b::PrintStackTrace();
    std::cerr << std::endl;
    std::abort();
}

[[noreturn]] void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) {
    switch (sig) {
    case SIGFPE:
        std::cerr << "\n *** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) ***" << std::endl;
        break;
    case SIGILL:
        std::cerr << "\n *** ILLEGAL INSTRUCTION (SIGILL) ***" << std::endl;
        break;
    case SIGSEGV:
        std::cerr << "\n *** SEGMENTATION VIOLATION (SIGSEGV) ***" << std::endl;
        break;
    }
    std::abort();
}

} // extern "C"

} // namespace MACE::Environment::Detail

#endif
