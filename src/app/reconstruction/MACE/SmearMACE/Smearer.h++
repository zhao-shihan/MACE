#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

namespace MACE::SmearMACE {

class Smearer {
public:
    Smearer(std::vector<std::string> inputFile, std::string outputFile);

    auto Smear(std::string_view treeName, const std::optional<std::unordered_map<std::string, std::string>>& smearingConfig) const -> void;

private:
    std::vector<std::string> fInputFile;
    std::string fOutputFile;
};

} // namespace MACE::SmearMACE
