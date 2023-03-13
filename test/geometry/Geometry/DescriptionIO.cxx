#include "MACE/Compatibility/std2b/to_underlying.hxx"
#include "MACE/Geometry/Description/All.hxx"
#include "MACE/Geometry/DescriptionIO.hxx"
#include "MACE/Env/BasicEnv.hxx"

#include <random>

using namespace MACE::Geometry;
using namespace MACE::Env;
using namespace MACE::Compatibility;

int main(int argc, char* argv[]) {
    BasicEnv environment(argc, argv, {});

    std::mt19937 rand;
    std::uniform_real_distribution<double> flat;

    auto& transportLine = Description::TransportLine::Instance();
    std::cout << "Default:\n"
              << transportLine.FirstStraightLength() << '\n'
              << transportLine.FirstBendRadius() << '\n'
              << transportLine.SecondStraightLength() << '\n'
              << transportLine.SecondBendRadius() << '\n'
              << transportLine.ThirdStraightLength() << '\n'
              << transportLine.SolenoidInnerRadius() << '\n'
              << transportLine.SolenoidOuterRadius() << '\n'
              << transportLine.FieldRadius() << '\n'
              << std::endl;

    std::cout << "Shuffled!\n\n";
    transportLine.FirstStraightLength(flat(rand));
    transportLine.FirstBendRadius(flat(rand));
    transportLine.SecondStraightLength(flat(rand));
    transportLine.SecondBendRadius(flat(rand));
    transportLine.ThirdStraightLength(flat(rand));
    transportLine.SolenoidInnerRadius(flat(rand));
    transportLine.SolenoidOuterRadius(flat(rand));
    transportLine.FieldRadius(flat(rand));

    DescriptionIO::Export<Description::TransportLine>("tl.yaml");
    std::cout << "After write into yaml:\n"
              << transportLine.FirstStraightLength() << '\n'
              << transportLine.FirstBendRadius() << '\n'
              << transportLine.SecondStraightLength() << '\n'
              << transportLine.SecondBendRadius() << '\n'
              << transportLine.ThirdStraightLength() << '\n'
              << transportLine.SolenoidInnerRadius() << '\n'
              << transportLine.SolenoidOuterRadius() << '\n'
              << transportLine.FieldRadius() << '\n'
              << std::endl;

    std::cout << "Shuffled!\n\n";
    transportLine.FirstStraightLength(flat(rand));
    transportLine.FirstBendRadius(flat(rand));
    transportLine.SecondStraightLength(flat(rand));
    transportLine.SecondBendRadius(flat(rand));
    transportLine.ThirdStraightLength(flat(rand));
    transportLine.SolenoidInnerRadius(flat(rand));
    transportLine.SolenoidOuterRadius(flat(rand));
    transportLine.FieldRadius(flat(rand));

    DescriptionIO::ImportInstantiated("tl.yaml");
    std::cout << "After read from yaml:\n"
              << transportLine.FirstStraightLength() << '\n'
              << transportLine.FirstBendRadius() << '\n'
              << transportLine.SecondStraightLength() << '\n'
              << transportLine.SecondBendRadius() << '\n'
              << transportLine.ThirdStraightLength() << '\n'
              << transportLine.SolenoidInnerRadius() << '\n'
              << transportLine.SolenoidOuterRadius() << '\n'
              << transportLine.FieldRadius() << '\n'
              << std::endl;

    auto& target = Description::Target::Instance();
    std::cout << "Default:\n"
              << std2b::to_underlying(target.ShapeType()) << '\n'
              << target.Cuboid().Width() << '\n'
              << target.Cuboid().Thickness() << '\n'
              << std2b::to_underlying(target.Cuboid().DetailType()) << '\n'
              << target.Cuboid().Hole().Extent() << '\n'
              << target.Cuboid().Hole().Spacing() << '\n'
              << target.Cuboid().Hole().Diameter() << '\n'
              << target.Cuboid().Hole().Depth() << '\n'
              << std::endl;

    std::cout << "Shuffled!\n\n";
    // target.ShapeType();
    target.Cuboid().Width(flat(rand));
    target.Cuboid().Thickness(flat(rand));
    target.Cuboid().DetailType(Description::Target::CuboidTarget::ShapeDetailType::Flat);
    target.Cuboid().Hole().Extent(flat(rand));
    target.Cuboid().Hole().Spacing(flat(rand));
    target.Cuboid().Hole().Diameter(flat(rand));
    target.Cuboid().Hole().Depth(flat(rand));

    DescriptionIO::Export<Description::Target>("tg.yaml");
    std::cout << "After write into yaml:\n"
              << std2b::to_underlying(target.ShapeType()) << '\n'
              << target.Cuboid().Width() << '\n'
              << target.Cuboid().Thickness() << '\n'
              << std2b::to_underlying(target.Cuboid().DetailType()) << '\n'
              << target.Cuboid().Hole().Extent() << '\n'
              << target.Cuboid().Hole().Spacing() << '\n'
              << target.Cuboid().Hole().Diameter() << '\n'
              << target.Cuboid().Hole().Depth() << '\n'
              << std::endl;

    std::cout << "Shuffled!\n\n";
    // target.ShapeType();
    target.Cuboid().Width(flat(rand));
    target.Cuboid().Thickness(flat(rand));
    target.Cuboid().DetailType(Description::Target::CuboidTarget::ShapeDetailType::Hole);
    target.Cuboid().Hole().Extent(flat(rand));
    target.Cuboid().Hole().Spacing(flat(rand));
    target.Cuboid().Hole().Diameter(flat(rand));
    target.Cuboid().Hole().Depth(flat(rand));

    DescriptionIO::ImportInstantiated("tg.yaml");
    std::cout << "After read from yaml:\n"
              << std2b::to_underlying(target.ShapeType()) << '\n'
              << target.Cuboid().Width() << '\n'
              << target.Cuboid().Thickness() << '\n'
              << std2b::to_underlying(target.Cuboid().DetailType()) << '\n'
              << target.Cuboid().Hole().Extent() << '\n'
              << target.Cuboid().Hole().Spacing() << '\n'
              << target.Cuboid().Hole().Diameter() << '\n'
              << target.Cuboid().Hole().Depth() << '\n'
              << std::endl;

    return EXIT_SUCCESS;
}
