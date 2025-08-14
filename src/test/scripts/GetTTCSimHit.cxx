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
    std::clog << "Getting " << DataTupleName << " from module: " << moduleName << std::endl;
    dstFile->cd();
    dstDir->cd();

    auto df{df0.Define("xx", "x[0]")
                .Define("yy", "x[1]")
                .Define("zz", "x[2]")
                .Define("px", "p[0]")
                .Define("py", "p[1]")
                .Define("pz", "p[2]")
                .Define("p0x", "p0[0]")
                .Define("p0y", "p0[1]")
                .Define("p0z", "p0[2]")};

    std::vector<std::tuple<std::string, std::any, std::any>> histParameterList{
        {"TileID",  0,             4500                                                                                      },
        {"d",       0.,            df.Max("d")                                                                               },
        {"Ek",      0.,            df.Max("Ek")                                                                              },
        {"Ek0",     0.,            df.Max("Ek0")                                                                             },
        {"xx",      df.Min("xx"),  df.Max("xx")                                                                              },
        {"yy",      df.Min("yy"),  df.Max("yy")                                                                              },
        {"zz",      df.Min("zz"),  df.Max("zz")                                                                              },
        {"px",      df.Min("px"),  df.Max("px")                                                                              },
        {"py",      df.Min("py"),  df.Max("py")                                                                              },
        {"pz",      df.Min("pz"),  df.Max("pz")                                                                              },
        {"p0x",     df.Min("p0x"), df.Max("p0x")                                                                             },
        {"p0y",     df.Min("p0y"), df.Max("p0y")                                                                             },
        {"p0z",     df.Min("p0z"), df.Max("p0z")                                                                             },
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
                               return df.Histo1D({expression.data(), expression.data(), nBinsValueType, Cast(xLow), Cast(xUp)}, expression);
                           });

    for (auto aHist : histList) {
        aHist->Write();
    }
    dstDir->Write();
    dstFile->Close();

    return 0;
}