namespace MACE::Math::Random::Generator {

constexpr Xoshiro256MM::ResultType Xoshiro256MM::operator()() {
    const auto result = std::rotl(fState[1] * 5, 7) * 9;
    Step();
    return result;
}

} // namespace MACE::Math::Random::Generator
