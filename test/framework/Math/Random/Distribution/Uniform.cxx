#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/Distribution/UniformRectangle.hxx"
#include "MACE/Math/Random/Generator/MT1993764.hxx"
#include "MACE/stdx/array_alias.hxx"

#include "ROOT/RDataFrame.hxx"

namespace stdx = MACE::stdx;
using namespace MACE::Math::Random;

int main(int argc, char* argv[]) {
    Generator::MT1993764 mt1993764;

    const auto n = std::stod(argv[1]);
    const auto a1 = argc > 2 ? std::stod(argv[2]) : 0;
    const auto b1 = argc > 3 ? std::stod(argv[3]) : 1;
    const auto a2 = argc > 4 ? std::stod(argv[4]) : 0;
    const auto b2 = argc > 5 ? std::stod(argv[5]) : 1;
    // const auto a3 = argc > 6 ? std::stod(argv[6]) : 0;
    // const auto b3 = argc > 7 ? std::stod(argv[7]) : 1;

    ROOT::RDataFrame dataFrame(n);
    dataFrame
        .Define("uc",
                [&] { return Distribution::UniformCompact<double>(a1, b1)(mt1993764); })
        .Define("ur",
                [&] { return Distribution::Uniform<double>(a1, b1)(mt1993764); })
        .Define("ui",
                [&] { return Distribution::Uniform<int>(a1, b1)(mt1993764); })

        .Define("ucr",
                [&] { return Distribution::UniformCompactRectangle<stdx::array2d>({a1, b1}, {a2, b2})(mt1993764); })
        .Define("urr",
                [&] { return Distribution::UniformRectangle<stdx::array2d>({a1, b1}, {a2, b2})(mt1993764); })
        .Define("uir",
                [&] { return Distribution::UniformRectangle<stdx::array2i>({(int)a1, (int)b1}, {(int)a2, (int)b2})(mt1993764); })

        // .Define("ucc",
        //         [&] { return Distribution::UniformCompactCuboid<stdx::array3d>({a1, b1}, {a2, b2}, {a3, b3})(mt1993764); })
        // .Define("urc",
        //         [&] { return Distribution::UniformCuboid<stdx::array3d>({a1, b1}, {a2, b2}, {a3, b3})(mt1993764); })
        // .Define("uic",
        //         [&] { return Distribution::UniformCuboid<stdx::array3i>({(int)a1, (int)b1}, {(int)a2, (int)b2}, {(int)a3, (int)b3})(mt1993764); })

        .Snapshot("uniform", "uniform.root");

    return EXIT_SUCCESS;
}
