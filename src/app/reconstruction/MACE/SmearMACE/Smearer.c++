#include "MACE/Env/MPIEnv.h++"
#include "MACE/Env/Print.h++"
#include "MACE/SmearMACE/Smearer.h++"
#include "MACE/Utility/RDFEventSplitPoint.h++"

#include "ROOT/RDataFrame.hxx"

#include "fmt/format.h"

#include <algorithm>

namespace MACE::SmearMACE {

Smearer::Smearer(std::vector<std::string> inputFile, std::string outputFile, unsigned batchSize, MPIX::Executor<unsigned>& executor) :
    fInputFile{std::move(inputFile)},
    fOutputFile{std::move(outputFile)},
    fBatchSize{batchSize},
    fExecutor{executor} {}

auto Smearer::Smear(std::string_view treeName, const std::optional<std::unordered_map<std::string, std::string>>& smearingConfig) const -> void {
    ROOT::RDataFrame data{treeName, fInputFile};
    const auto esp{RDFEventSplitPoint(data)};

    ROOT::RDF::RNode newData{data};
    if (smearingConfig) {
        for (auto&& [var, smear] : *smearingConfig) {
            newData = newData.Redefine(var, smear);
        }
    }

    const auto nEvent{static_cast<unsigned>(esp.size() - 1)};
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    const auto nBatch{std::max(nEvent / fBatchSize + 1, static_cast<unsigned>(mpiEnv.CommWorldSize()))};
    if (static_cast<unsigned>(mpiEnv.CommWorldRank()) >= nEvent / fBatchSize + 1) {
        Env::PrintLnWarning("Warning: number of batches < size of MPI_COMM_WORLD. The result dataset are complete, but {} will not contain {}.", fOutputFile, treeName);
    }

    fExecutor.TaskName("Batch");
    fExecutor.ExecutionName(std::string{treeName});
    fExecutor.Execute(
        nBatch,
        [&](auto k) {
            const auto i{k * fBatchSize};
            if (i > nEvent) { return; }
            newData.Range(esp[i],
                          esp[std::min(i + fBatchSize, nEvent)])
                .Snapshot(treeName, fOutputFile, "", {"UPDATE", ROOT::kZSTD, 5, 0, 99, false, false});
        });
}

} // namespace MACE::SmearMACE
