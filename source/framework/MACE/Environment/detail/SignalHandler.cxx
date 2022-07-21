#if MACE_SIGNAL_HANDLER

#    include "MACE/Environment/detail/SignalHandler.hxx"

#    include "TSystem.h"

#    include <csignal>
#    include <cstdlib>

namespace MACE::Environment::Detail {

extern "C" {

[[noreturn]] void MACESignalSIGABRTHandler(int) {
    std::puts("\n *** ABORT ***\n");
    gSystem->StackTrace();
    std::_Exit(EXIT_FAILURE);
}

[[noreturn]] void MACESignalSIGFPEHandler(int) {
    std::puts("\n *** ERRONEOUS ARITHMETIC OPERATION ***");
    std::abort();
}

[[noreturn]] void MACESignalSIGILLHandler(int) {
    std::puts("\n *** ILLEGAL INSTRUCTION ***");
    std::abort();
}

[[noreturn]] void MACESignalSIGINTHandler(int) {
    std::puts("\n *** INTERRUPT ***\n");
    gSystem->StackTrace();
    std::quick_exit(EXIT_FAILURE);
}

[[noreturn]] void MACESignalSIGSEGVHandler(int) {
    std::puts("\n *** SEGMENTATION VIOLATION ***");
    std::abort();
}

[[noreturn]] void MACESignalSIGTERMHandler(int) {
    std::puts("\n *** TERMINATE ***");
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
