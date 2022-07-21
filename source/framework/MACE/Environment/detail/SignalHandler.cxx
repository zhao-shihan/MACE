#if MACE_SIGNAL_HANDLER

    #include "MACE/Environment/detail/SignalHandler.hxx"

    #include <csignal>
    #include <cstdlib>
    #include <iostream>
    #include <version>

    #ifdef __cpp_lib_stacktrace // C++23
        #include <stacktrace>
    #else // fallback to ROOT stacktrace
        #include "TSystem.h"
    #endif

namespace MACE::Environment::Detail {

extern "C" {

[[noreturn]] void MACESignalSIGABRTHandler(int) {
    std::cerr << "\n *** ABORT ***\n"
              << std::endl;
    #ifdef __cpp_lib_stacktrace // C++23
    std::clog << std::stacktrace::current() << std::endl;
    #else // fallback to ROOT stacktrace
    if (gSystem != nullptr) { // not destructed
        gSystem->StackTrace();
    }
    #endif
    std::_Exit(EXIT_FAILURE);
}

[[noreturn]] void MACESignalSIGFPEHandler(int) {
    std::cerr << "\n *** ERRONEOUS ARITHMETIC OPERATION ***" << std::endl;
    std::abort();
}

[[noreturn]] void MACESignalSIGILLHandler(int) {
    std::cerr << "\n *** ILLEGAL INSTRUCTION ***" << std::endl;
    std::abort();
}

[[noreturn]] void MACESignalSIGINTHandler(int) {
    std::cerr << "\n *** INTERRUPT ***\n"
              << std::endl;
    #ifdef __cpp_lib_stacktrace // C++23
    std::clog << std::stacktrace::current() << std::endl;
    #else // fallback to ROOT stacktrace
    if (gSystem != nullptr) { // not destructed
        gSystem->StackTrace();
    }
    #endif
    std::quick_exit(EXIT_FAILURE);
}

[[noreturn]] void MACESignalSIGSEGVHandler(int) {
    std::cerr << "\n *** SEGMENTATION VIOLATION ***" << std::endl;
    std::abort();
}

[[noreturn]] void MACESignalSIGTERMHandler(int) {
    std::cerr << "\n *** TERMINATE ***" << std::endl;
    std::terminate();
}

} // extern "C"

bool SignalHandler::fgInstantiated = false;

SignalHandler::SignalHandler() {
    if (fgInstantiated) {
        throw std::logic_error("MACE::Environment::Detail::SignalHandler: Trying to construct twice");
    }

    std::signal(SIGABRT, MACESignalSIGABRTHandler);
    std::signal(SIGFPE, MACESignalSIGFPEHandler);
    std::signal(SIGILL, MACESignalSIGILLHandler);
    std::signal(SIGINT, MACESignalSIGINTHandler);
    std::signal(SIGSEGV, MACESignalSIGSEGVHandler);
    std::signal(SIGTERM, MACESignalSIGTERMHandler);

    fgInstantiated = true;
}

} // namespace MACE::Environment::Detail

#endif
