#pragma once

#if MACE_SIGNAL_HANDLER

namespace MACE::Environment::Detail {

class SignalHandler final {
public:
    SignalHandler();
    SignalHandler(const SignalHandler&) = delete;
    SignalHandler& operator=(const SignalHandler&) = delete;

private:
    static bool fgInstantiated;
};

} // namespace MACE::Environment::Detail

#endif
