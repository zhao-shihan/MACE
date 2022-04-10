/// @brief The test of MACE::Geometry::DescriptionIO.
/// @author Shi-Han Zhao

#include "MACE/Core/Geometry/Description/All.hxx"
#include "MACE/Core/Geometry/DescriptionIO.hxx"

int main() {
    using namespace MACE::Core::Geometry;

    DescriptionIO::Write("mace_geom.yaml");

    auto& linacField = Description::LinacField::Instance();
    std::cout << linacField.GetRadius() << '\n'
              << linacField.GetLength() << '\n'
              << linacField.GetDownStreamLength() << '\n'
              << std::endl;
    DescriptionIO::Read("mace_geom.yaml");
    std::cout << linacField.GetRadius() << '\n'
              << linacField.GetLength() << '\n'
              << linacField.GetDownStreamLength() << '\n'
              << std::endl;

    return EXIT_SUCCESS;
}
