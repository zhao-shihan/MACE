#pragma once
#if MACE_SIGNAL_HANDLER

namespace MACE::Env::internal {

extern "C" {

/// @brief Handles: SIGINT, SIGTERM
void MACE_ISOC99_SIGINT_SIGTERM_Handler(int);
/// @brief Handles: SIGABRT
[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int);
/// @brief Handles: SIGFPE, SIGILL, SIGSEGV
void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig);

} // extern "C"

} // namespace MACE::Env::internal

#endif
