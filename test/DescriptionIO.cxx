/// @brief The test of MACE::Geometry::DescriptionIO.
/// @author Shi-Han Zhao

#include "Core/Geometry/Description/All.hxx"
#include "Core/Geometry/DescriptionIO.hxx"

int main() {
    using namespace MACE::Core::Geometry;

    DescriptionIO::Write("mace_geom.yaml");

    auto& linacField = Description::AcceleratorField::Instance();
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
