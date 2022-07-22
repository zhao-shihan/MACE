#pragma once

namespace MACE::Environment {

class BasicEnvironment;

namespace Detail {

class SignalHandler final {
    friend class Environment::BasicEnvironment;

private:
    SignalHandler();
    SignalHandler(const SignalHandler&) = delete;
    SignalHandler& operator=(const SignalHandler&) = delete;
};

} // namespace Detail

} // namespace MACE::Environment
