/// @brief The test of MACE::Geometry::DescriptionIO.

#include "MACE/Core/Geometry/Description/All.hxx"
#include "MACE/Core/Geometry/DescriptionIO.hxx"

int main() {
    using namespace MACE::Core::Geometry;

    auto& transportLine = Description::TransportLine::Instance();
    std::cout << "Default:\n"
              << transportLine.GetFirstStraightLength() << '\n'
              << transportLine.GetFirstBendRadius() << '\n'
              << transportLine.GetSecondStraightLength() << '\n'
              << transportLine.GetSecondBendRadius() << '\n'
              << transportLine.GetThirdStraightLength() << '\n'
              << transportLine.GetSolenoidInnerRadius() << '\n'
              << transportLine.GetSolenoidOuterRadius() << '\n'
              << transportLine.GetFieldRadius() << '\n'
              << std::endl;

    DescriptionIO::WriteInstantiated("mace_geom.yaml");
    std::cout << "After write into yaml:\n"
              << transportLine.GetFirstStraightLength() << '\n'
              << transportLine.GetFirstBendRadius() << '\n'
              << transportLine.GetSecondStraightLength() << '\n'
              << transportLine.GetSecondBendRadius() << '\n'
              << transportLine.GetThirdStraightLength() << '\n'
              << transportLine.GetSolenoidInnerRadius() << '\n'
              << transportLine.GetSolenoidOuterRadius() << '\n'
              << transportLine.GetFieldRadius() << '\n'
              << std::endl;

    DescriptionIO::ReadInstantiated("mace_geom.yaml");
    std::cout << "After read from yaml:\n"
              << transportLine.GetFirstStraightLength() << '\n'
              << transportLine.GetFirstBendRadius() << '\n'
              << transportLine.GetSecondStraightLength() << '\n'
              << transportLine.GetSecondBendRadius() << '\n'
              << transportLine.GetThirdStraightLength() << '\n'
              << transportLine.GetSolenoidInnerRadius() << '\n'
              << transportLine.GetSolenoidOuterRadius() << '\n'
              << transportLine.GetFieldRadius() << '\n'
              << std::endl;

    return EXIT_SUCCESS;
}
