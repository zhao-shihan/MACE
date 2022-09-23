#include "MACE/Core/DataFactory.hxx"

#include <ranges>
#include <stdexcept>

namespace MACE::Core {

DataFactory::DataFactory() :
    MerelyMoveableBase(),
    fPrefixHasIndex(true),
    fSuffixHasIndex(false),
    fPrefix("#", "_"),
    fSuffix("", ""),
    fPrefixFormat("#{}_"),
    fSuffixFormat("") {}

void DataFactory::TreeNamePrefixFormat(std::string_view prefix) {
    std::tie(fPrefixHasIndex, fPrefix) = SplitPrefixOrSuffixFormat(prefix);
    fPrefixFormat = prefix;
}

void DataFactory::TreeNameSuffixFormat(std::string_view suffix) {
    std::tie(fSuffixHasIndex, fSuffix) = SplitPrefixOrSuffixFormat(suffix);
    fSuffixFormat = suffix;
}

std::pair<bool, std::pair<std::string, std::string>> DataFactory::SplitPrefixOrSuffixFormat(std::string_view format) {
    auto splitFormatView = std::views::split(format, fgIndexer);
    std::string_view first;
    std::string_view second;
    int splitCount = 0;
    for (auto&& part : splitFormatView) {
        switch (++splitCount) {
        case 1:
            first = {part.begin(), part.end()};
            break;
        case 2:
            second = {part.begin(), part.end()};
            break;
        default:
            throw std::logic_error(std::string("DataFactory::SplitPrefixOrSuffixFormat: "
                                               "Two or more indexer (the \"{}\") found in the tree name format \"")
                                       .append(format)
                                       .append("\""));
        };
    }
    return {splitCount == 2, std::pair<std::string, std::string>(first, second)};
}

} // namespace MACE::Core
