#include "ROOT/RDataFrame.hxx"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

const auto nBinsValueType{100};
auto DataTupleName{"TTCSimHit"};

auto GetTTCSimHit(auto moduleName, auto srcFileName, auto dstFileName) -> int {
    ROOT::RDataFrame df0{Form("G4Run0/%s", DataTupleName), srcFileName};
    const auto dstFile{new TFile(dstFileName, "UPDATE")};
    auto moduleDir{static_cast<TDirectory*>(dstFile->Get(moduleName))};
    if (!moduleDir) {
        std::clog << "DST File: Directory named " << moduleName << " is a new dir, create it." << std::endl;
        moduleDir = dstFile->mkdir(moduleName);
    }
    auto dstDir{moduleDir->mkdir(DataTupleName)};
    if (!dstDir) {
        std::cout << "Make TDirectory " << DataTupleName << " Failed. ";
        if (moduleDir->Get(DataTupleName)) {
            std::cout << "Already exist." << std::endl;
            return 1;
        }
    }
    std::clog << "Getting " << DataTupleName << " from module: " << moduleName << std::endl;
    dstFile->cd();
    dstDir->cd();

    auto df{df0.Define("x[0]", "x[0]")
                .Define("x[1]", "x[1]")
                .Define("x[2]", "x[2]")
                .Define("p[0]", "p[0]")
                .Define("p[1]", "p[1]")
                .Define("p[2]", "p[2]")
                .Define("p0[0]", "p0[0]")
                .Define("p0[1]", "p0[1]")
                .Define("p0[2]", "p0[2]")};

    std::vector<std::tuple<std::string, std::any, std::any>> histParameterList{
        {"TileID",  0.,            4000.                                                                                     },
        {"Ek",      0.,            df.Max("Ek")                                                                              },
        {"Ek0",     0.,            df.Max("Ek0")                                                                             },
        {"x[0]",      df.Min("x[0]"),  df.Max("x[0]")                                                                              },
        {"x[1]",      df.Min("x[1]"),  df.Max("x[1]")                                                                              },
        {"x[2]",      df.Min("x[2]"),  df.Max("x[2]")                                                                              },
        {"p[0]",      df.Min("p[0]"),  df.Max("p[0]")                                                                              },
        {"p[1]",      df.Min("p[1]"),  df.Max("p[1]")                                                                              },
        {"p[2]",      df.Min("p[2]"),  df.Max("p[2]")                                                                              },
        {"p0[0]",     df.Min("p0[0]"), df.Max("p0[0]")                                                                             },
        {"p0[1]",     df.Min("p0[1]"), df.Max("p0[1]")                                                                             },
        {"p0[2]",     df.Min("p0[2]"), df.Max("p0[2]")                                                                             },
        {"t",       0,             std::function([&]() -> double { return *df.Mean("t") + 5 * *df.StdDev("t"); })            },
        {"nOptPho", 0,             std::function([&]() -> double { return *df.Mean("nOptPho") + 5 * *df.StdDev("nOptPho"); })},
        {"Edep",    0.,            std::function([&]() -> double { return *df.Mean("Edep") + 5 * *df.StdDev("Edep"); })      }
    };

    std::vector<ROOT::RDF::RResultPtr<TH1>> histList;
    std::ranges::transform(histParameterList, std::back_inserter(histList),
                           [&](auto&& parameter) -> ROOT::RDF::RResultPtr<TH1> {
                               auto&& [expression, xLow, xUp]{parameter};
                               constexpr auto Cast{[](std::any& any) -> double {
                                   if (const auto x{std::any_cast<ROOT::RDF::RResultPtr<double>>(&any)}) {
                                       return **x;
                                   } else if (const auto x{std::any_cast<double>(&any)}) {
                                       return *x;
                                   } else if (const auto x{std::any_cast<std::function<double()>>(&any)}) {
                                       return (*x)();
                                   }
                                   return 0;
                               }};
                               std::clog << "Hist: " << expression << std::endl;
                               auto xMin{Cast(xLow)};
                               auto xMax{Cast(xUp)};
                               auto margin{(xMax - xMin) / nBinsValueType};
                               return df.Histo1D({expression.data(), expression.data(), nBinsValueType, xMin - margin, xMax + margin}, expression);
                           });

    for (auto aHist : histList) {
        aHist->Write();
    }
    dstDir->Write();
    dstFile->Close();

    return 0;
}