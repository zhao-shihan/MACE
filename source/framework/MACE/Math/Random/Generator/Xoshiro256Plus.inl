namespace MACE::Math::Random::Generator {

constexpr Xoshiro256Plus::ResultType Xoshiro256Plus::operator()() {
    const auto result = fState[0] + fState[3];
    Step();
    return result;
}

} // namespace MACE::Math::Random::Generator
