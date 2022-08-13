#pragma once
#if MACE_SIGNAL_HANDLER

namespace MACE::Environment::Internal {

extern "C" {

/// @brief Handles: SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM
[[noreturn]] void MACE_ISOC99SignalHandler(int sig);

} // extern "C"

} // namespace MACE::Environment::Internal

#endif
