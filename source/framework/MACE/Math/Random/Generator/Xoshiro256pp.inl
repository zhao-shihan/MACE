namespace MACE::Math::Random::Generator {

constexpr Xoshiro256pp::ResultType Xoshiro256pp::operator()() {
    const auto result = std::rotl(fState[0] + fState[3], 23) + fState[0];
    Step();
    return result;
}

} // namespace MACE::Math::Random::Generator
