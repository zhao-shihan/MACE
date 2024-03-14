#include "MACE/SmearMACE/Smearer.h++"

#include "ROOT/RDFHelpers.hxx"
#include "ROOT/RDataFrame.hxx"

#include "fmt/format.h"

namespace MACE::SmearMACE {

Smearer::Smearer(std::vector<std::string> inputFile, std::string outputFile) :
    fInputFile{std::move(inputFile)},
    fOutputFile{std::move(outputFile)} {}

auto Smearer::Smear(std::string_view treeName, const std::optional<std::unordered_map<std::string, std::string>>& smearingConfig) const -> void {
    ROOT::RDataFrame df{treeName, fInputFile};
    ROOT::RDF::Experimental::AddProgressBar(df);
    if (smearingConfig) {
        auto&& [firstVar, firstSmear]{*smearingConfig->cbegin()};
        auto ir{df.Redefine(firstVar, firstSmear)};
        for (auto i{smearingConfig->cbegin()}; i != smearingConfig->cend(); ++i) {
            ir = ir.Redefine(i->first, i->second);
        }
        ir.Snapshot(treeName, fOutputFile, "", {"UPDATE", ROOT::kZSTD, 5, 0, 99, false, false});
    } else {
        df.Snapshot(treeName, fOutputFile, "", {"UPDATE", ROOT::kZSTD, 5, 0, 99, false, false});
    }
}

} // namespace MACE::SmearMACE
