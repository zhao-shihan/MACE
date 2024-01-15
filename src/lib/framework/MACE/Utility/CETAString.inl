namespace MACE::inline Utility {

template<std::size_t N>
consteval CETAString<N>::Data::Data(const CharString& string) {
    std::ranges::copy(string, fData);
}

template<std::size_t N>
consteval CETAString<N>::CETAString(const CharString& string) :
    fStringDataImNotAPI{string} {}

} // namespace MACE::inline Utility
