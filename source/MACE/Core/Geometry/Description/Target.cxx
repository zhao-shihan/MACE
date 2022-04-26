#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Target& Target::Instance() noexcept {
    static Target instance;
    return instance;
}

Target::Target() :
    IDescription("Target"),
    fWidth(6_cm),
    fThickness(1_cm),
    fFineStructure(ConstructFormula("(z<-5 || x<-20||x>20 || y<-20||y>20) || "
                                    "((x-(round((x-y/sqrt(3))/0.101)+round(2/sqrt(3)*y/0.101)/2)*0.101)^2+(y-sqrt(3)/2*round(2/sqrt(3)*y/0.101)*0.101)^2>0.086*0.086/4)")) {}

bool Target::VolumeContains(const Double_t* pos) const noexcept {
    return std::abs(pos[0]) <= fWidth / 2 and
           std::abs(pos[1]) <= fWidth / 2 and
           -fThickness <= pos[2] and pos[2] <= 0;
}

HepGeom::Transform3D Target::CalcTransform() const {
    const auto& linacField = LinacField::Instance();
    const auto transZ = linacField.GetLength() / 2 - linacField.GetDownStreamLength() - fThickness / 2;
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
}

void Target::ReadImpl(const YAML::Node& node) {
    fWidth = node["Width"].as<decltype(fWidth)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
    fFineStructure = ConstructFormula(node["FineStructure"].as<std::string>().c_str());
}

void Target::WriteImpl(YAML::Node& node) const {
    node["Width"] = fWidth;
    node["Thickness"] = fThickness;
    node["FineStructure"] = fFineStructure.GetExpFormula().Data();
}

} // namespace MACE::Core::Geometry::Description
