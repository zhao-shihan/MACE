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
auto DataTupleName{"MMSSimTrack"};

auto GetMMSSimTrack(auto moduleName, auto srcFileName, auto dstFileName) -> int {
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

    auto df{df0.Define("x0x", "x0[0]")
                .Define("x0y", "x0[1]")
                .Define("x0z", "x0[2]")
                .Define("c0x", "c0[0]")
                .Define("c0y", "c0[1]")
                .Define("c0z", "c0[2]")
                .Define("p0x", "p0[0]")
                .Define("p0y", "p0[1]")
                .Define("p0z", "p0[2]")};

    std::vector<std::tuple<std::string, std::any, std::any>> histParameterList{
        {"phi0",   df.Min("phi0"),   df.Max("phi0")  },
        {"z0",     df.Min("z0"),     df.Max("z0")    },
        {"theta0", df.Min("theta0"), df.Max("theta0")},
        {"chi2",   0.,               df.Max("chi2")  },
        {"Ek0",    0.,               df.Max("Ek0")   },
        {"r0",     0.,               df.Max("r0")    },
        {"t0",     0,                df.Max("t0")    },
        {"p0x",    df.Min("p0x"),    df.Max("p0x")   },
        {"p0y",    df.Min("p0y"),    df.Max("p0y")   },
        {"p0z",    df.Min("p0z"),    df.Max("p0z")   },
        {"x0x",    df.Min("x0x"),    df.Max("x0x")   },
        {"x0y",    df.Min("x0y"),    df.Max("x0y")   },
        {"x0z",    df.Min("x0z"),    df.Max("x0z")   },
        {"c0x",    df.Min("c0x"),    df.Max("c0x")   },
        {"c0y",    df.Min("c0y"),    df.Max("c0y")   },
        {"c0z",    df.Min("c0z"),    df.Max("c0z")   }
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