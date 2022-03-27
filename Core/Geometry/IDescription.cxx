#include "Geometry/IDescription.hxx"

using MACE::Geometry::IDescription;

std::ostream& operator<<(std::ostream& out, const IDescription& geomDescp) {
    out << "Name:\n"
        << '\t' << geomDescp.GetName() << '\n'
        << "Is composed of multi-volume:\n"
        << '\t' << geomDescp.GetOverallDescription() << '\n'
        << "Material description:\n"
        << '\t' << geomDescp.GetMaterialDescription() << '\n'
        << "Shape description:\n"
        << '\t' << geomDescp.GetShapeDescription() << '\n'
        << "Mother geometry description:\n"
        << '\t' << geomDescp.GetMotherDescription() << '\n'
        << "Translation description:\n"
        << '\t' << geomDescp.GetTranslationDescription() << '\n'
        << "Rotation description:\n"
        << '\t' << geomDescp.GetRotationDescription() << '\n'
        << "Other description:\n"
        << '\t' << geomDescp.GetOtherDescription();
    return out;
}
