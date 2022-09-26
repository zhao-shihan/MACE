#if MACE_SIGNAL_HANDLER

#    include "MACE/Environment/internal/ISOC99SignalHandler.hxx"
#    include "MACE/Environment/MPIEnvironment.hxx"
#    include "MACE/Utility/PrintStackTrace.hxx"

#    include <chrono>
#    include <csignal>
#    include <cstdlib>
#    include <ctime>
#    include <iomanip>
#    include <iostream>
#    include <string_view>

namespace MACE::Environment::internal {

extern "C" {

[[noreturn]] void MACE_ISOC99_SIGINT_SIGTERM_Handler(int sig) {
    using namespace std::string_view_literals;
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << '\n';
    switch (sig) {
    case SIGINT:
        std::cerr << " ***** INTERRUPT (SIGINT) received\n"sv;
        break;
    case SIGTERM:
        std::cerr << " ***** TERMINATE (SIGTERM) received\n"sv;
        break;
    }
    if (MPIEnvironment::Available()) {
        std::cerr << " ***** on "sv << MPIEnvironment::Instance().GetNodeName() << '\n';
    }
    std::cerr << " ***** at "sv << std::put_time(std::localtime(&now), "%FT%T%z") << '\n'
              << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
#    ifndef __MINGW32__
    std::quick_exit(EXIT_FAILURE);
#    else
    std::_Exit(EXIT_FAILURE);
#    endif
}

[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int) {
    using namespace std::string_view_literals;
    std::signal(SIGABRT, SIG_DFL);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << "\n"sv
                 " ***** ABORT (SIGABRT) received\n"sv;
    if (MPIEnvironment::Available()) {
        std::cerr << " ***** on "sv << MPIEnvironment::Instance().GetNodeName() << '\n';
    }
    std::cerr << " ***** at "sv << std::put_time(std::localtime(&now), "%FT%T%z") << '\n'
              << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
    std::abort();
}

[[noreturn]] void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) {
    using namespace std::string_view_literals;
    std::signal(SIGABRT, SIG_DFL);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << '\n';
    switch (sig) {
    case SIGFPE:
        std::cerr << " ***** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) received\n"sv;
        break;
    case SIGILL:
        std::cerr << " ***** ILLEGAL INSTRUCTION (SIGILL) received\n"sv;
        break;
    case SIGSEGV:
        std::cerr << " ***** SEGMENTATION VIOLATION (SIGSEGV) received\n"sv;
        break;
    }
    if (MPIEnvironment::Available()) {
        std::cerr << " ***** on "sv << MPIEnvironment::Instance().GetNodeName() << '\n';
    }
    std::cerr << " ***** at "sv << std::put_time(std::localtime(&now), "%FT%T%z") << '\n'
              << std::endl;
    Utility::PrintStackTrace();
    std::cerr << std::endl;
    std::abort();
}

} // extern "C"

} // namespace MACE::Environment::internal

#endif
