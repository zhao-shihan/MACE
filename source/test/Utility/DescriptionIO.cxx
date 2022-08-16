#include "MACE/Core/Geometry/Description/All.hxx"
#include "MACE/Core/Geometry/DescriptionIO.hxx"
#include "MACE/Compatibility/Std2b/ToUnderlying.hxx"
#include "MACE/Environment/BasicEnvironment.hxx"

#include <random>

namespace Std2b = MACE::Compatibility::Std2b;
using namespace MACE::Core::Geometry;
using namespace MACE::Environment;

int main(int argc, char* argv[]) {
    BasicEnvironment environment(argc, argv, {});

    std::mt19937 rand;
    std::uniform_real_distribution<double> flat;

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

    std::cout << "Shuffled!\n\n";
    transportLine.SetFirstStraightLength(flat(rand));
    transportLine.SetFirstBendRadius(flat(rand));
    transportLine.SetSecondStraightLength(flat(rand));
    transportLine.SetSecondBendRadius(flat(rand));
    transportLine.SetThirdStraightLength(flat(rand));
    transportLine.SetSolenoidInnerRadius(flat(rand));
    transportLine.SetSolenoidOuterRadius(flat(rand));
    transportLine.SetFieldRadius(flat(rand));

    DescriptionIO::Export<Description::TransportLine>("tl.yaml");
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

    std::cout << "Shuffled!\n\n";
    transportLine.SetFirstStraightLength(flat(rand));
    transportLine.SetFirstBendRadius(flat(rand));
    transportLine.SetSecondStraightLength(flat(rand));
    transportLine.SetSecondBendRadius(flat(rand));
    transportLine.SetThirdStraightLength(flat(rand));
    transportLine.SetSolenoidInnerRadius(flat(rand));
    transportLine.SetSolenoidOuterRadius(flat(rand));
    transportLine.SetFieldRadius(flat(rand));

    DescriptionIO::ImportInstantiated("tl.yaml");
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

    auto& target = Description::Target::Instance();
    std::cout << "Default:\n"
              << Std2b::ToUnderlying(target.GetShapeType()) << '\n'
              << target.GetCuboid().GetWidth() << '\n'
              << target.GetCuboid().GetThickness() << '\n'
              << Std2b::ToUnderlying(target.GetCuboid().GetDetailType()) << '\n'
              << target.GetCuboid().GetHole().GetExtent() << '\n'
              << target.GetCuboid().GetHole().GetSpacing() << '\n'
              << target.GetCuboid().GetHole().GetDiameter() << '\n'
              << target.GetCuboid().GetHole().GetDepth() << '\n'
              << std::endl;

    std::cout << "Shuffled!\n\n";
    // target.SetShapeType();
    target.GetCuboid().SetWidth(flat(rand));
    target.GetCuboid().SetThickness(flat(rand));
    target.GetCuboid().SetDetailType(Description::Target::Cuboid::DetailType::Flat);
    target.GetCuboid().GetHole().SetExtent(flat(rand));
    target.GetCuboid().GetHole().SetSpacing(flat(rand));
    target.GetCuboid().GetHole().SetDiameter(flat(rand));
    target.GetCuboid().GetHole().SetDepth(flat(rand));

    DescriptionIO::Export<Description::Target>("tg.yaml");
    std::cout << "After write into yaml:\n"
              << Std2b::ToUnderlying(target.GetShapeType()) << '\n'
              << target.GetCuboid().GetWidth() << '\n'
              << target.GetCuboid().GetThickness() << '\n'
              << Std2b::ToUnderlying(target.GetCuboid().GetDetailType()) << '\n'
              << target.GetCuboid().GetHole().GetExtent() << '\n'
              << target.GetCuboid().GetHole().GetSpacing() << '\n'
              << target.GetCuboid().GetHole().GetDiameter() << '\n'
              << target.GetCuboid().GetHole().GetDepth() << '\n'
              << std::endl;

    std::cout << "Shuffled!\n\n";
    // target.SetShapeType();
    target.GetCuboid().SetWidth(flat(rand));
    target.GetCuboid().SetThickness(flat(rand));
    target.GetCuboid().SetDetailType(Description::Target::Cuboid::DetailType::Hole);
    target.GetCuboid().GetHole().SetExtent(flat(rand));
    target.GetCuboid().GetHole().SetSpacing(flat(rand));
    target.GetCuboid().GetHole().SetDiameter(flat(rand));
    target.GetCuboid().GetHole().SetDepth(flat(rand));

    DescriptionIO::ImportInstantiated("tg.yaml");
    std::cout << "After read from yaml:\n"
              << Std2b::ToUnderlying(target.GetShapeType()) << '\n'
              << target.GetCuboid().GetWidth() << '\n'
              << target.GetCuboid().GetThickness() << '\n'
              << Std2b::ToUnderlying(target.GetCuboid().GetDetailType()) << '\n'
              << target.GetCuboid().GetHole().GetExtent() << '\n'
              << target.GetCuboid().GetHole().GetSpacing() << '\n'
              << target.GetCuboid().GetHole().GetDiameter() << '\n'
              << target.GetCuboid().GetHole().GetDepth() << '\n'
              << std::endl;

    return EXIT_SUCCESS;
}
