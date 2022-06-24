namespace MACE::Utility {

template<std::constructible_from<std::string_view> StringT, SplitStringOption OptionV>
std::vector<StringT> SplitString(std::string_view string, char delimiter) {
    std::vector<StringT> result;
    if (string.empty()) { return result; }
    if constexpr (std::same_as<StringT, std::string_view>) {
        const auto end = string.end();
        const auto overEnd = end + 1;
        auto head = string.begin();
        auto tail = head + 1;
        do {
            if constexpr (OptionV == kAll) {
                while (head != end and *head == delimiter) { ++head; }
                tail = head;
                if (tail != end) { ++tail; }
            }
            while (tail != end and *tail != delimiter) { ++tail; }
            if constexpr (OptionV == kLast) {
                while (tail != end and *tail == delimiter) { ++tail; }
                if (tail != end) { --tail; }
            }
            result.emplace_back(head, tail);
            head = ++tail;
        } while (tail != overEnd);
    } else {
        const auto viewResult = SplitString<std::string_view, OptionV>(string, delimiter);
        result.reserve(viewResult.size());
        for (auto&& view : viewResult) {
            result.emplace_back(view);
        }
    }
    return result;
}

} // namespace MACE::Utility
