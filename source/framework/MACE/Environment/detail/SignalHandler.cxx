#include "MACE/Environment/detail/SignalHandler.hxx"

#if MACE_SIGNAL_HANDLER

    #include "MACE/Utility/PrintStackTrace.hxx"

    #include <csignal>
    #include <cstdlib>
    #include <iostream>

namespace MACE::Environment::Detail {

extern "C" {

/// @brief Handles: SIGINT
[[noreturn]] void MACE_ISOC99_SIGINT_Handler(int) {
    std::cerr << "\n *** INTERRUPT (SIGINT) ***\n"
              << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
    std::exit(EXIT_FAILURE);
}

/// @brief Handles: SIGTERM
[[noreturn]] void MACE_ISOC99_SIGTERM_Handler(int) {
    std::cerr << "\n *** TERMINATE (SIGTERM) ***\n"
              << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
    std::quick_exit(EXIT_FAILURE);
}

/// @brief Handles: SIGABRT
[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int) {
    std::signal(SIGABRT, SIG_DFL);
    std::cerr << "\n *** ABORT (SIGABRT) ***\n"
              << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
    std::abort();
}

/// @brief Handles: SIGFPE, SIGILL, SIGSEGV
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

SignalHandler::SignalHandler() {
    if (static bool gInstantiated = false; gInstantiated) {
        throw std::logic_error("MACE::Environment::Detail::SignalHandler: Trying to construct twice");
    } else {
        gInstantiated = true;
    }

    std::signal(SIGABRT, MACE_ISOC99_SIGABRT_Handler);
    std::signal(SIGFPE, MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGILL, MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGINT, MACE_ISOC99_SIGINT_Handler);
    std::signal(SIGSEGV, MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGTERM, MACE_ISOC99_SIGTERM_Handler);
}

} // namespace MACE::Environment::Detail

#else

namespace MACE::Environment::Detail {

SignalHandler::SignalHandler() = default;

} // namespace MACE::Environment::Detail

#endif
