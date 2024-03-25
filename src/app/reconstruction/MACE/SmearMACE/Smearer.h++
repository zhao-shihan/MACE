#pragma once

#include "MACE/Extension/MPIX/Execution/Executor.h++"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace MACE::SmearMACE {

class Smearer {
public:
    Smearer(std::vector<std::string> inputFile, std::string outputFile, unsigned batchSize, MPIX::Executor<unsigned>& executor);

    auto Smear(std::string_view treeName, const std::optional<std::unordered_map<std::string, std::string>>& smearingConfig) const -> void;

private:
    std::vector<std::string> fInputFile;
    std::string fOutputFile;

    unsigned fBatchSize;
    MPIX::Executor<unsigned>& fExecutor;
};

} // namespace MACE::SmearMACE
