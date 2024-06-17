#include "MACE/Detector/Description/TTC.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Time;
using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::LiteralUnit::Angle;
using namespace Mustard::LiteralUnit::Density;

TTC::TTC() :
    DescriptionBase{"TTC"},
    // Geometry
    fLength{15_cm},
    fWidth{10_cm},
    fThickness{1_cm},
    fRadius{48_cm},
    fSlantAngle{15_deg},
    fNAlongPhi{42},
    fNAlongZ{18},
    // Material
    fDensity{1.023_g_cm3},
    fRIndexEnergyBin{3.100_eV, 2.385_eV},
    fRIndex{1.58, 1.58},
    fAbsLengthEnergyBin{3.100_eV, 2.385_eV},
    fAbsLength{210_cm, 210_cm},
    fScintillationComponent1EnergyBin{2.38513_eV, 2.39658_eV, 2.40813_eV, 2.42251_eV, 2.43249_eV, 2.44255_eV, 2.46668_eV,
                                      2.48034_eV, 2.49176_eV, 2.50667_eV, 2.52421_eV, 2.54498_eV, 2.56205_eV, 2.57833_eV,
                                      2.58809_eV, 2.59741_eV, 2.61099_eV, 2.62365_eV, 2.63643_eV, 2.65096_eV, 2.6662_eV,
                                      2.68549_eV, 2.7017_eV, 2.7062_eV, 2.71468_eV, 2.72322_eV, 2.73124_eV, 2.74104_eV, 2.74975_eV,
                                      2.76085_eV, 2.77442_eV, 2.78991_eV, 2.80377_eV, 2.81532_eV, 2.82881_eV, 2.84679_eV,
                                      2.85744_eV, 2.86753_eV, 2.87642_eV, 2.88537_eV, 2.89373_eV, 2.90019_eV, 2.90538_eV,
                                      2.91124_eV, 2.91713_eV, 2.92369_eV, 2.93228_eV, 2.93891_eV, 2.94491_eV, 2.94892_eV,
                                      2.95429_eV, 2.95765_eV, 2.96035_eV, 2.96237_eV, 2.9644_eV, 2.96847_eV, 2.97323_eV,
                                      2.97732_eV, 2.98073_eV, 2.98416_eV, 2.98622_eV, 2.99034_eV, 2.9931_eV, 2.99793_eV,
                                      3.00209_eV, 3.00487_eV, 3.00905_eV, 3.01324_eV, 3.01814_eV, 3.02517_eV, 3.03649_eV,
                                      3.05219_eV, 3.07677_eV, 3.0988_eV},
    fScintillationComponent1{0.0687575_eV, 0.0735826_eV, 0.0784077_eV, 0.0832328_eV, 0.0856454_eV, 0.0904704_eV,
                             0.101327_eV, 0.107358_eV, 0.117008_eV, 0.124246_eV, 0.141134_eV, 0.158022_eV, 0.172497_eV,
                             0.185766_eV, 0.193004_eV, 0.206273_eV, 0.227986_eV, 0.244873_eV, 0.261761_eV, 0.285887_eV,
                             0.305187_eV, 0.33655_eV, 0.363088_eV, 0.396864_eV, 0.430639_eV, 0.464415_eV, 0.498191_eV,
                             0.536791_eV, 0.565742_eV, 0.60193_eV, 0.633293_eV, 0.659831_eV, 0.681544_eV, 0.700844_eV,
                             0.711701_eV, 0.716526_eV, 0.73462_eV, 0.768396_eV, 0.802171_eV, 0.838359_eV, 0.874548_eV,
                             0.903498_eV, 0.927624_eV, 0.951749_eV, 0.971049_eV, 0.987937_eV, 0.996381_eV, 0.992762_eV,
                             0.983112_eV, 0.968637_eV, 0.949337_eV, 0.913148_eV, 0.879373_eV, 0.84801_eV, 0.814234_eV,
                             0.761158_eV, 0.710495_eV, 0.652593_eV, 0.599517_eV, 0.553679_eV, 0.510253_eV, 0.45959_eV,
                             0.416164_eV, 0.370326_eV, 0.329312_eV, 0.300362_eV, 0.266586_eV, 0.244873_eV, 0.22316_eV,
                             0.193004_eV, 0.167672_eV, 0.137515_eV, 0.102533_eV, 0.0711701_eV},
    fScintillationYield{17400 * 0.64},
    fScintillationTimeConstant1{2.4_ns},
    fResolutionScale{1} {}

auto TTC::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fLength, "Length");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fRadius, "DistanceToCDC");
    ImportValue(node, fSlantAngle, "SlantAngle");
    ImportValue(node, fNAlongPhi, "NAlongPhi");
    ImportValue(node, fNAlongZ, "NAlongZ");
    // Material
    ImportValue(node, fDensity, "Density");
    ImportValue(node, fRIndexEnergyBin, "RIndexEnergyBin");
    ImportValue(node, fRIndex, "RIndex");
    ImportValue(node, fAbsLengthEnergyBin, "AbsLengthEnergyBin");
    ImportValue(node, fAbsLength, "AbsLength");
    ImportValue(node, fScintillationComponent1EnergyBin, "ScintillationComponent1EnergyBin");
    ImportValue(node, fScintillationComponent1, "ScintillationComponent1");
    ImportValue(node, fScintillationYield, "ScintillationYield");
    ImportValue(node, fScintillationTimeConstant1, "ScintillationTimeConstant1");
    ImportValue(node, fResolutionScale, "ResolutionScale");
}

auto TTC::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fLength, "Length");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fRadius, "DistanceToCDC");
    ExportValue(node, fSlantAngle, "SlantAngle");
    ExportValue(node, fNAlongPhi, "NAlongPhi");
    ExportValue(node, fNAlongZ, "NAlongZ");
    // Material
    ExportValue(node, fDensity, "Density");
    ExportValue(node, fRIndexEnergyBin, "RIndexEnergyBin");
    ExportValue(node, fRIndex, "RIndex");
    ExportValue(node, fAbsLengthEnergyBin, "AbsLengthEnergyBin");
    ExportValue(node, fAbsLength, "AbsLength");
    ExportValue(node, fScintillationComponent1EnergyBin, "ScintillationComponent1EnergyBin");
    ExportValue(node, fScintillationComponent1, "ScintillationComponent1");
    ExportValue(node, fScintillationYield, "ScintillationYield");
    ExportValue(node, fScintillationTimeConstant1, "ScintillationTimeConstant1");
    ExportValue(node, fResolutionScale, "ResolutionScale");
}

} // namespace MACE::Detector::Description
