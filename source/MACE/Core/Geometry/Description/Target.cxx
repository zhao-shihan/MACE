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
    fFineStructure(ConstructFormula("(z<-5 || x<-20||x>20 || y<-20||y>20) || ((x-(round((x-0.577350269189626*y)/0.101)+round(1.154700538379251*y/0.101)/2)*0.101)^2+(y-0.866025403784439*round(1.154700538379251*y/0.101)*0.101)^2>0.86*0.86/4)")) {}

bool Target::Contains(const Double_t* pos) const noexcept {
    return -fWidth / 2 < pos[0] and pos[0] < fWidth / 2 and
           -fWidth / 2 < pos[1] and pos[1] < fWidth / 2 and
           -fThickness < pos[2] and pos[2] < 0 and
           fFineStructure.EvalPar(pos) > 0.5;
}

HepGeom::Transform3D Target::CalcTransform() const {
    const auto& LinacField = LinacField::Instance();
    auto transZ = LinacField.GetLength() / 2 - LinacField.GetDownStreamLength() - fThickness / 2;
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
