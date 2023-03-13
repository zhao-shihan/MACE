#include "MACE/DataModel/DataFactory.hxx"

#include <stdexcept>

namespace MACE::DataModel {

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
    if (const auto index = format.find_first_of(fgIndexer);
        index == std::string_view::npos) {
        return {false,
                std::pair(std::string(format),
                          std::string())};
    } else if (const auto indexEnd = index + fgIndexer.length();
               format.find_first_of(fgIndexer, indexEnd) == std::string_view::npos) {
        return {true,
                std::pair(std::string(format.begin(), format.begin() + index),
                          std::string(format.begin() + indexEnd, format.end()))};
    } else {
        throw std::logic_error(std::string("DataFactory::SplitPrefixOrSuffixFormat: "
                                           "Two or more indexer (the \"{}\") found in the tree name format \"")
                                   .append(format)
                                   .append("\""));
    }
}

} // namespace MACE::DataModel
