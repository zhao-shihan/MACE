#include "Mustard/Env/CLI/BasicCLI.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Utility/Print.h++"

#include "ROOT/RDF/ActionHelpers.hxx"
#include "ROOT/RDataFrame.hxx"
#include "TDirectory.h"
#include "TFile.h"

#include "fmt/format.h"

#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    Mustard::Env::CLI::BasicCLI<> cli;
    cli->add_argument("n").help("Number of input files.").nargs(1).scan<'i', unsigned int>();
    cli->add_argument("-m", "--module").help("Tested module.").required().nargs(1);
    cli->add_argument("-ip", "--input-path").help("Input path(directory) of the input files.").default_value("./").required().nargs(1);
    cli->add_argument("-op", "--output-path").help("Output path(directory) of the output file.").default_value("./").nargs(1);
    cli->add_argument("-ifn", "--input-filename").help("Input filename (the same prefixes).").required().nargs(1);
    cli->add_argument("-ofn", "--output-filename").help("Out put filename.").default_value("test_sum_untitled.root").nargs(1);
    cli->add_argument("-tr", "--tree").help("The selected tree's name.").required().nargs(1);
    cli->add_argument("-br", "--branch").help("The selected branch's name.").required().nargs(1);
    Mustard::Env::MPIEnv env{argc, argv, {}};

    auto testedModuleName{cli->get("-m")};
    auto inputDir{cli->get("-ip")};
    auto outputDir{cli->get("-op")};
    auto inputFileNameBsc{cli->get("-ifn")};
    auto inputFileNumber{cli->get<unsigned int>("n")};
    auto selectedTreeName{cli->get("-tr")};
    auto selectedBranchName{cli->get("-br")};
    auto outputFileName{cli->get("-ofn")};

    std::string inputPath = inputDir;
    if (inputPath.back() != '/') {
        inputPath += "/";
    }
    std::string outputPath = outputDir;
    if (outputPath.back() != '/') {
        outputPath += "/";
    }

    std::vector<std::string> inputFiles;
    for (unsigned int i{1}; i <= inputFileNumber; ++i) {
        inputFiles.push_back(inputPath + inputFileNameBsc + std::to_string(i) + ".root");
    }

    ROOT::RDataFrame df(selectedTreeName, inputFiles);

    auto outputFile = TFile::Open((outputPath + outputFileName).c_str(), "RECREATE");
    auto dirA = outputFile->mkdir(testedModuleName.c_str());
    dirA->cd();

    auto outputTreePath{fmt::format("{}/{}", testedModuleName, selectedTreeName)};
    df.Snapshot(outputTreePath, outputFile->GetName(), {selectedBranchName});

    outputFile->Close();

    Mustard::MasterPrintLn("Sampling object merged : Running {} : testing {}/{}.", testedModuleName, selectedTreeName, selectedBranchName);
    return 0;
}
