namespace MACE::Data {

template<std::size_t N>
    requires(N == 0 or N >= 2)
consteval CEvalNTSTA<N>::FixedString::FixedString(const char (&string)[N]) {
    std::ranges::copy(string, fString);
}

template<std::size_t N>
    requires(N == 0 or N >= 2)
consteval CEvalNTSTA<N>::CEvalNTSTA(const char (&string)[N]) :
    fPrivateStringNotAPI{string} {}

} // namespace MACE::Data
