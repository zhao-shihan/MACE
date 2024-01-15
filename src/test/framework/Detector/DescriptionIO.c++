#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/BasicEnv.h++"

#include <random>

using namespace MACE::Detector;
using namespace MACE::Env;
using namespace MACE::Compatibility;

int main(int argc, char* argv[]) {
    BasicEnv environment(argc, argv, {});

    std::mt19937 rand;
    std::uniform_real_distribution<double> flat;

    auto& transportLine = Description::Solenoid::Instance();
    std::cout << "Default:\n"
              << transportLine.S1Length() << '\n'
              << transportLine.B1Radius() << '\n'
              << transportLine.S2Length() << '\n'
              << transportLine.B2Radius() << '\n'
              << transportLine.S3Length() << '\n'
              << transportLine.InnerRadius() << '\n'
              << transportLine.OuterRadius() << '\n'
              << transportLine.FieldRadius() << '\n'
              << std::endl;

    std::cout << "Shuffled!\n\n";
    transportLine.S1Length(flat(rand));
    transportLine.B1Radius(flat(rand));
    transportLine.S2Length(flat(rand));
    transportLine.B2Radius(flat(rand));
    transportLine.S3Length(flat(rand));
    transportLine.InnerRadius(flat(rand));
    transportLine.OuterRadius(flat(rand));
    transportLine.FieldRadius(flat(rand));

    Description::DescriptionIO::Export<Description::Solenoid>("tl.yaml");
    std::cout << "After write into yaml:\n"
              << transportLine.S1Length() << '\n'
              << transportLine.B1Radius() << '\n'
              << transportLine.S2Length() << '\n'
              << transportLine.B2Radius() << '\n'
              << transportLine.S3Length() << '\n'
              << transportLine.InnerRadius() << '\n'
              << transportLine.OuterRadius() << '\n'
              << transportLine.FieldRadius() << '\n'
              << std::endl;

    std::cout << "Shuffled!\n\n";
    transportLine.S1Length(flat(rand));
    transportLine.B1Radius(flat(rand));
    transportLine.S2Length(flat(rand));
    transportLine.B2Radius(flat(rand));
    transportLine.S3Length(flat(rand));
    transportLine.InnerRadius(flat(rand));
    transportLine.OuterRadius(flat(rand));
    transportLine.FieldRadius(flat(rand));

    Description::DescriptionIO::ImportInstantiated("tl.yaml");
    std::cout << "After read from yaml:\n"
              << transportLine.S1Length() << '\n'
              << transportLine.B1Radius() << '\n'
              << transportLine.S2Length() << '\n'
              << transportLine.B2Radius() << '\n'
              << transportLine.S3Length() << '\n'
              << transportLine.InnerRadius() << '\n'
              << transportLine.OuterRadius() << '\n'
              << transportLine.FieldRadius() << '\n'
              << std::endl;

    auto& target = Description::Target::Instance();
    std::cout << "Default:\n"
              << std23::to_underlying(target.ShapeType()) << '\n'
              << target.Cuboid().Width() << '\n'
              << target.Cuboid().Thickness() << '\n'
              << std23::to_underlying(target.Cuboid().DetailType()) << '\n'
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

    Description::DescriptionIO::Export<Description::Target>("tg.yaml");
    std::cout << "After write into yaml:\n"
              << std23::to_underlying(target.ShapeType()) << '\n'
              << target.Cuboid().Width() << '\n'
              << target.Cuboid().Thickness() << '\n'
              << std23::to_underlying(target.Cuboid().DetailType()) << '\n'
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

    Description::DescriptionIO::ImportInstantiated("tg.yaml");
    std::cout << "After read from yaml:\n"
              << std23::to_underlying(target.ShapeType()) << '\n'
              << target.Cuboid().Width() << '\n'
              << target.Cuboid().Thickness() << '\n'
              << std23::to_underlying(target.Cuboid().DetailType()) << '\n'
              << target.Cuboid().Hole().Extent() << '\n'
              << target.Cuboid().Hole().Spacing() << '\n'
              << target.Cuboid().Hole().Diameter() << '\n'
              << target.Cuboid().Hole().Depth() << '\n'
              << std::endl;

    return EXIT_SUCCESS;
}
