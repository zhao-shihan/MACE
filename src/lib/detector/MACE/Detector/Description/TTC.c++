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
    fLength{this, 7_cm},
    fWidthDown{this, 3_cm},
    fWidthUp{this, 5_cm},
    fThickness{this, 0.5_cm},
    fRadius{this, 48_cm},
    fSlantAngle{this, 46_deg},
    fNAlongPhi{this, 122},
    fBarrelLength{this, 180_cm},

    fPCBLength{this, 3_cm},
    fPCBWidth{this, 1_cm},
    fPCBThickness{this, 0.1_cm},

    fWindowLength{this, 0.3_cm},
    fWindowWidth{this, 0.3_cm},
    fWindowThickness{this, 0.05_cm},

    fLightCouplerLength{this, 0.3_cm},
    fLightCouplerWidth{this, 0.3_cm},
    fLightCouplerThickness{this, 0.01_cm},

    fSiliconeLength{this, 0.2_cm},
    fSiliconeWidth{this, 0.2_cm},
    fSiliconeThickness{this, 0.03_cm},

    fWidth{this, [this] { return CalculateWidth(); }},
    fPosition{this, [this] { return CalculatePosition(); }},
    // Material
    //Scintillator
    fDensity{this, 1.023_g_cm3},
    fRIndexEnergyBin{this, {3.100_eV, 2.385_eV}},
    fRIndex{this, {1.58, 1.58}},
    fAbsLengthEnergyBin{this, {3.100_eV, 2.385_eV}},
    fAbsLength{this, {210_cm, 210_cm}},
    fScintillationComponent1EnergyBin{this, {2.38513_eV, 2.39658_eV, 2.40813_eV, 2.42251_eV, 2.43249_eV, 2.44255_eV, 2.46668_eV, 2.48034_eV, 2.49176_eV, 2.50667_eV, 2.52421_eV, 2.54498_eV, 2.56205_eV, 2.57833_eV, 2.58809_eV, 2.59741_eV, 2.61099_eV, 2.62365_eV, 2.63643_eV, 2.65096_eV, 2.6662_eV, 2.68549_eV, 2.7017_eV, 2.7062_eV, 2.71468_eV, 2.72322_eV, 2.73124_eV, 2.74104_eV, 2.74975_eV, 2.76085_eV, 2.77442_eV, 2.78991_eV, 2.80377_eV, 2.81532_eV, 2.82881_eV, 2.84679_eV, 2.85744_eV, 2.86753_eV, 2.87642_eV, 2.88537_eV, 2.89373_eV, 2.90019_eV, 2.90538_eV, 2.91124_eV, 2.91713_eV, 2.92369_eV, 2.93228_eV, 2.93891_eV, 2.94491_eV, 2.94892_eV, 2.95429_eV, 2.95765_eV, 2.96035_eV, 2.96237_eV, 2.9644_eV, 2.96847_eV, 2.97323_eV, 2.97732_eV, 2.98073_eV, 2.98416_eV, 2.98622_eV, 2.99034_eV, 2.9931_eV, 2.99793_eV, 3.00209_eV, 3.00487_eV, 3.00905_eV, 3.01324_eV, 3.01814_eV, 3.02517_eV, 3.03649_eV, 3.05219_eV, 3.07677_eV, 3.0988_eV}},
    fScintillationComponent1{this, {0.0687575_eV, 0.0735826_eV, 0.0784077_eV, 0.0832328_eV, 0.0856454_eV, 0.0904704_eV, 0.101327_eV, 0.107358_eV, 0.117008_eV, 0.124246_eV, 0.141134_eV, 0.158022_eV, 0.172497_eV, 0.185766_eV, 0.193004_eV, 0.206273_eV, 0.227986_eV, 0.244873_eV, 0.261761_eV, 0.285887_eV, 0.305187_eV, 0.33655_eV, 0.363088_eV, 0.396864_eV, 0.430639_eV, 0.464415_eV, 0.498191_eV, 0.536791_eV, 0.565742_eV, 0.60193_eV, 0.633293_eV, 0.659831_eV, 0.681544_eV, 0.700844_eV, 0.711701_eV, 0.716526_eV, 0.73462_eV, 0.768396_eV, 0.802171_eV, 0.838359_eV, 0.874548_eV, 0.903498_eV, 0.927624_eV, 0.951749_eV, 0.971049_eV, 0.987937_eV, 0.996381_eV, 0.992762_eV, 0.983112_eV, 0.968637_eV, 0.949337_eV, 0.913148_eV, 0.879373_eV, 0.84801_eV, 0.814234_eV, 0.761158_eV, 0.710495_eV, 0.652593_eV, 0.599517_eV, 0.553679_eV, 0.510253_eV, 0.45959_eV, 0.416164_eV, 0.370326_eV, 0.329312_eV, 0.300362_eV, 0.266586_eV, 0.244873_eV, 0.22316_eV, 0.193004_eV, 0.167672_eV, 0.137515_eV, 0.102533_eV, 0.0711701_eV}},
    fScintillationYield{this, 17400 * 0.64},
    fScintillationTimeConstant1{this, 2.4_ns},
    fResolutionScale{this, 1.},
    //LightCoupler
    fLightCouplerDensity{this, 1.06_g_cm3},
    fLightCouplerCarbonElement{this, 2.},
    fLightCouplerHydrogenElement{this, 6.},
    fLightCouplerOxygenElement{this, 1.},
    fLightCouplerSiliconElement{this, 1.},
    fLightCouplerRIndex{this, {1.46, 1.46}},
    fLightCouplerAbsLength{this, {100_cm, 100_cm}},
    //Window
    fWindowDensity{this, 1.18_g_cm3},
    fWindowCarbonElement{this, 0.7362},
    fWindowHydrogenElement{this,0.0675},
    fWindowOxygenElement{this, 0.1963},
    fWindowRIndex{this, {1.57, 1.57}},

    fSiPMEnergyBin{this,{1.391655126_eV,1.413303953_eV,1.436778788_eV,1.461046623_eV,1.486148332_eV,1.512127645_eV,1.533451437_eV,
                       1.553243676_eV,1.579239384_eV,1.601331725_eV,1.618380329_eV,1.644070091_eV,1.668575932_eV,1.695332333_eV,
                       1.722960822_eV,1.750124077_eV,1.769418592_eV,1.796139112_eV,1.823679036_eV,1.850275906_eV,1.880443107_eV,
                       1.905389876_eV,1.927096598_eV,1.948591293_eV,1.968750142_eV,1.989552718_eV,2.012699006_eV,2.044509747_eV,
                       2.086746867_eV,2.108593697_eV,2.13196381_eV,2.162065168_eV,2.196197125_eV,2.211510324_eV,2.240146328_eV,
                       2.277682676_eV,2.31087249_eV,2.342157708_eV,2.374301646_eV,2.410389305_eV,2.452932479_eV,2.507137915_eV,
                       2.565089699_eV,2.6485729_eV,2.732230683_eV,2.795153262_eV,2.842415847_eV,2.907557927_eV,2.975755876_eV,
                       3.029226473_eV,3.073774257_eV,3.139907148_eV,3.179961838_eV,3.207163267_eV,3.244659512_eV,3.289219352_eV,
                       3.307290247_eV,3.327878491_eV,3.363166032_eV,3.399209944_eV,3.435444057_eV,3.46043183_eV,3.48852431_eV,
                       3.516457699_eV,3.550580722_eV,3.563879348_eV,3.57404697_eV,3.587160946_eV,3.60984247_eV,3.628195256_eV,
                       3.637441808_eV,3.651400344_eV,3.670179231_eV,3.684390646_eV,3.696659746_eV,3.720794081_eV,3.721383683_eV,
                       3.742354188_eV,3.755013028_eV,3.787037996_eV,3.809782448_eV,3.840536792_eV}},
    fSiPMEfficiency{this,{0.038361565,0.043881036,0.050158203,0.056879188,0.063896051,0.071245776,0.077096023,0.082806497,0.09049302,
                    0.096846043,0.102167517,0.110439587,0.118523116,0.127329437,0.136497387,0.144697087,0.152101728,0.160383488,
                    0.169784037,0.17901796,0.189932435,0.197788503,0.2061559,0.215114701,0.226013151,0.23524354,0.244663368,
                    0.255647156,0.270165176,0.278993559,0.28798576,0.297864503,0.310058789,0.315182084,0.324696839,0.336285043,
                    0.347467345,0.356656635,0.364883088,0.373827813,0.382839555,0.3902882,0.395495771,0.400343653,0.401560403,
                    0.396238242,0.390316468,0.384591232,0.375317514,0.365819506,0.358254968,0.346811362,0.335599315,0.326263057,
                    0.314742636,0.300694748,0.29059875,0.283296713,0.270049269,0.257841507,0.247144881,0.237727757,0.22854291,
                    0.217013978,0.206721701,0.200096265,0.191250653,0.181575856,0.168947005,0.159534377,0.149674853,0.139503115,
                    0.129670093,0.120230653,0.108280609,0.091831406,0.098424138,0.083937488,0.073056832,0.060399447,0.047887957,
                    0.034501313}}, // S14161
    
    //Optical Surface
    fRfSurface{this, {0.985, 0.985}},
    fCouplerSurface{this, {1,1}},
    fAirPaintSurface{this, {0,0}},
    fCathodeSurface{this, {0.,0.}}{}

auto TTC::CalculateWidth() -> std::vector<double> {
    std::deque<double> dequefWidth;
    std::vector<double> fWidth;
    double omega{2 * pi * cos(atan(fRadius / fWidthDown))};
    double temporaryWidth;
    auto nMax{static_cast<int>(std::floor(2 * pi / omega))};
    for (gsl::index nSameSolidAngle{1}; nSameSolidAngle <= nMax; nSameSolidAngle++) {
        temporaryWidth = {fRadius * (1 / std::tan(std::acos(nSameSolidAngle * omega / (2 * pi))) - 1 / std::tan(std::acos((nSameSolidAngle - 1) * omega / (2 * pi))))};
        if (temporaryWidth >= fWidthUp||fRadius * (1 / std::tan(std::acos(nSameSolidAngle * omega / (2 * pi))))<=fBarrelLength/2) {
            break;
        }
        dequefWidth.push_front(temporaryWidth);
        dequefWidth.push_back(temporaryWidth);
    }
    auto nFinalSameSolidAngle{dequefWidth.size() / 2};
    for (gsl::index nWidthUp = nFinalSameSolidAngle + 1; fRadius / std::tan(std::acos(nFinalSameSolidAngle * omega / (2 * pi))) + (nWidthUp - nFinalSameSolidAngle - 0.5) * fWidthUp <= fBarrelLength / 2; nWidthUp++) { // 第n块（上限宽度条件）
        dequefWidth.push_front(fWidthUp);
        dequefWidth.push_back(fWidthUp);
    }
    std::ranges::copy(dequefWidth, std::back_inserter(fWidth));
    return fWidth;
}

auto TTC::CalculatePosition() -> std::vector<muc::array3d> {
    std::deque<muc::array3d> dequefPosition;
    std::vector<muc::array3d> fPosition;
    double omega{2 * pi * cos(atan(fRadius / fWidthDown))};
    double temporaryWidth;
    auto nMax{static_cast<int>(std::floor(2 * pi / omega))};
    for (gsl::index nSameSolidAngle{1}; nSameSolidAngle <= nMax; nSameSolidAngle++) {
        temporaryWidth = {fRadius * (1 / std::tan(std::acos(nSameSolidAngle * omega / (2 * pi))) - 1 / std::tan(std::acos((nSameSolidAngle - 1) * omega / (2 * pi))))};
        if (temporaryWidth >= fWidthUp||fRadius * (1 / std::tan(std::acos(nSameSolidAngle * omega / (2 * pi))))<=fBarrelLength/2) {
            break;
        }
        dequefPosition.push_front(muc::array3d{fRadius, 0, -1 * (fRadius / 2 * (1 / std::tan(std::acos(nSameSolidAngle * omega / (2 * pi))) + 1 / std::tan(std::acos((nSameSolidAngle - 1) * omega / (2 * pi)))))});
        dequefPosition.push_back(muc::array3d{fRadius, 0, fRadius / 2 * (1 / std::tan(std::acos(nSameSolidAngle * omega / (2 * pi))) + 1 / std::tan(std::acos((nSameSolidAngle - 1) * omega / (2 * pi))))});
    }
    auto nFinalSameSolidAngle{dequefPosition.size() / 2};
    for (gsl::index nWidthUp = nFinalSameSolidAngle + 1; fRadius / std::tan(std::acos(nFinalSameSolidAngle * omega / (2 * pi))) + (nWidthUp - nFinalSameSolidAngle - 0.5) * fWidthUp <= fBarrelLength / 2; nWidthUp++) { // 第n块（上限宽度条件）
        dequefPosition.push_front(muc::array3d{fRadius, 0, -1 * (fRadius / std::tan(std::acos(nFinalSameSolidAngle * omega / (2 * pi))) + (nWidthUp - nFinalSameSolidAngle - 0.5) * fWidthUp)});
        dequefPosition.push_back(muc::array3d{fRadius, 0, fRadius / std::tan(std::acos(nFinalSameSolidAngle * omega / (2 * pi))) + (nWidthUp - nFinalSameSolidAngle - 0.5) * fWidthUp});
    }
    std::ranges::copy(dequefPosition, std::back_inserter(fPosition));
    return fPosition;
}

auto TTC::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fLength, "Length");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fRadius, "DistanceToCDC");
    ImportValue(node, fSlantAngle, "SlantAngle");
    ImportValue(node, fNAlongPhi, "NAlongPhi");
    ImportValue(node, fBarrelLength, "BarrelLength");
    ImportValue(node, fPCBLength, "PCBLength");
    ImportValue(node, fPCBWidth, "PCBWidth");
    ImportValue(node, fPCBThickness, "PCBThickness");
    ImportValue(node, fWindowLength, "WindowLength");
    ImportValue(node, fWindowWidth, "WindowWidth");
    ImportValue(node, fWindowThickness, "WindowThickness");
    ImportValue(node, fLightCouplerLength, "LightCouplerLength");
    ImportValue(node, fLightCouplerWidth, "LightCouplerWidth");
    ImportValue(node, fLightCouplerThickness, "LightCouplerThickness");
    ImportValue(node, fSiliconeLength, "SiliconeLength");
    ImportValue(node, fSiliconeWidth, "SiliconeWidth");
    ImportValue(node, fSiliconeThickness, "SiliconeThickness");
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
    ImportValue(node, fLightCouplerDensity, "LightCouplerDensity");
    ImportValue(node, fLightCouplerCarbonElement, "LightCouplerCarbonElement");
    ImportValue(node, fLightCouplerHydrogenElement, "LightCouplerHydrogenElement");
    ImportValue(node, fLightCouplerOxygenElement, "LightCouplerOxygenElement");
    ImportValue(node, fLightCouplerSiliconElement, "LightCouplerSiliconElement");
    ImportValue(node, fLightCouplerRIndex, "LightCouplerRIndex");
    ImportValue(node, fLightCouplerAbsLength, "LightCouplerAbsLength");
    ImportValue(node, fWindowDensity, "WindowDensity");
    ImportValue(node, fWindowCarbonElement, "WindowCarbonElement");
    ImportValue(node, fWindowHydrogenElement, "WindowHydrogenElement");
    ImportValue(node, fWindowOxygenElement, "WindowOxygenElement");
    ImportValue(node, fWindowRIndex, "WindowRIndex");
    ImportValue(node, fSiPMEnergyBin, "SiPMEnergyBin");
    ImportValue(node, fSiPMEfficiency, "SiPMEfficiency");
    ImportValue(node, fRfSurface, "RfSurface");
    ImportValue(node, fCouplerSurface, "CouplerSurface");
    ImportValue(node, fAirPaintSurface, "AirPaintSurface");
    ImportValue(node, fCathodeSurface, "CathodeSurface");
}

auto TTC::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fLength, "Length");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fRadius, "DistanceToCDC");
    ExportValue(node, fSlantAngle, "SlantAngle");
    ExportValue(node, fNAlongPhi, "NAlongPhi");
    ExportValue(node, fBarrelLength, "BarrelLength");
    ExportValue(node, fPCBLength, "PCBLength");
    ExportValue(node, fPCBWidth, "PCBWidth");
    ExportValue(node, fPCBThickness, "PCBThickness");
    ExportValue(node, fWindowLength, "WindowLength");
    ExportValue(node, fWindowWidth, "WindowWidth");
    ExportValue(node, fWindowThickness, "WindowThickness");
    ExportValue(node, fLightCouplerLength, "LightCouplerLength");
    ExportValue(node, fLightCouplerWidth, "LightCouplerWidth");
    ExportValue(node, fLightCouplerThickness, "LightCouplerThickness");
    ExportValue(node, fSiliconeLength, "SiliconeLength");
    ExportValue(node, fSiliconeWidth, "SiliconeWidth");
    ExportValue(node, fSiliconeThickness, "SiliconeThickness");
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
    ExportValue(node,fLightCouplerDensity, "LightCouplerDensity");
    ExportValue(node, fLightCouplerCarbonElement, "LightCouplerCarbonElement");
    ExportValue(node, fLightCouplerHydrogenElement, "LightCouplerHydrogenElement");
    ExportValue(node, fLightCouplerOxygenElement, "LightCouplerOxygenElement");
    ExportValue(node, fLightCouplerSiliconElement, "LightCouplerSiliconElement");
    ExportValue(node, fLightCouplerRIndex, "LightCouplerRIndex");
    ExportValue(node, fLightCouplerAbsLength, "LightCouplerAbsLength");
    ExportValue(node,fWindowDensity, "WindowDensity");
    ExportValue(node, fWindowCarbonElement, "WindowCarbonElement");
    ExportValue(node, fWindowHydrogenElement, "WindowHydrogenElement");
    ExportValue(node, fWindowOxygenElement, "WindowOxygenElement");
    ExportValue(node, fWindowRIndex, "WindowRIndex");
    ExportValue(node,fSiPMEnergyBin, "SiPMEnergyBin");
    ExportValue(node,fSiPMEfficiency, "SiPMEfficiency");
    ExportValue(node, fRfSurface, "RfSurface");
    ExportValue(node, fCouplerSurface, "CouplerSurface");
    ExportValue(node, fAirPaintSurface, "AirPaintSurface");
    ExportValue(node, fCathodeSurface, "CathodeSurface");
}

} // namespace MACE::Detector::Description
