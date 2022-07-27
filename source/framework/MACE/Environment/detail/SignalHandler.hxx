#pragma once
#if MACE_SIGNAL_HANDLER

namespace MACE::Environment::Detail {

extern "C" {

/// @brief Handles: SIGINT
[[noreturn]] void MACE_ISOC99_SIGINT_Handler(int);
/// @brief Handles: SIGTERM
[[noreturn]] void MACE_ISOC99_SIGTERM_Handler(int);
/// @brief Handles: SIGABRT
[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int);
/// @brief Handles: SIGFPE, SIGILL, SIGSEGV
[[noreturn]] void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig);

} // extern "C"

} // namespace MACE::Environment::Detail

#endif
