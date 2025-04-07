#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/PDSVeto.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PhysicalConstant.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::LiteralUnit::Time;
using namespace Mustard::MathConstant;

PDSVeto::PDSVeto() :
    DescriptionWithCacheBase{"PDSVeto"},
    // Geometry
    /*  SiPM: microft-30035-smt
        plastic scintillator: EJ-200
        coupler: EJ-550*/
    fNModuleOfACategory{this, 1, 2, 4, 4},
    fNLayerPerModuleOfACategory{this, 3, 2, 2, 2},
    fNStripPerLayerOfACategory{this, 12, 16, 5, 8},
    fStripLengthOfACategory{this, 145_cm, 140_cm, 180_cm, 35_cm},
    fPSWidth{this, 10_cm},
    fPSThickness{this, 2_cm},
    fPSFiberRadius{this, 0.7_mm},
    fPSHoleRadius{this, 0.75_mm},
    fInterPSGap{this, 1_mm},
    fPerpendicularModuleGap{this, 0.5_cm},
    fParallelModuleGap{this, 1_cm},
    fModuleOffset{this, 1_cm},
    fAlAbsorberThickness{this, 0.6_cm},
    fReflectiveFilmThickness{this, 0.4_mm},
    fSiPMThickness{this, 0.41_mm},
    fSiPMCathodeThickness{this, 0.2_mm},
    fSiPMCouplerThickness{this, 0.1_mm},
    fSiPMSize{this, 4_mm},
    fSolenoidWindowRadius{this, 14_cm},
    fFiberNum{this, 4},
    fSelectedCategory{this, -1},

    // plastic scintillator
    fPSScintillationEnergyBin{this,
                              2.482953109_eV, 2.489659196_eV, 2.496003695_eV, 2.502381059_eV, 2.508791544_eV, 2.515235634_eV, 2.521712914_eV, 2.528223186_eV, 2.53476796_eV, 2.541347168_eV, 2.548161747_eV,
                              2.554661489_eV, 2.561202446_eV, 2.567815247_eV, 2.574829427_eV, 2.579956087_eV, 2.585046827_eV, 2.590273296_eV, 2.596648064_eV, 2.602100665_eV, 2.608203377_eV, 2.613926041_eV,
                              2.61797784_eV, 2.622401485_eV, 2.628222987_eV, 2.632330767_eV, 2.637208697_eV, 2.643026898_eV, 2.647008211_eV, 2.651842137_eV, 2.658691238_eV, 2.665141972_eV, 2.671429914_eV,
                              2.677283888_eV, 2.685400294_eV, 2.69325325_eV, 2.699300679_eV, 2.706719316_eV, 2.713494146_eV, 2.719892644_eV, 2.726076443_eV, 2.73102463_eV, 2.737402211_eV, 2.742231678_eV,
                              2.748404443_eV, 2.754115306_eV, 2.759358856_eV, 2.764781943_eV, 2.76890398_eV, 2.776072945_eV, 2.782386965_eV, 2.789212011_eV, 2.795753365_eV, 2.802196767_eV, 2.806414568_eV,
                              2.811221166_eV, 2.814980328_eV, 2.819868451_eV, 2.825619424_eV, 2.831284734_eV, 2.836501956_eV, 2.84333131_eV, 2.849700132_eV, 2.854645037_eV, 2.859428074_eV, 2.864396308_eV,
                              2.869215654_eV, 2.876671121_eV, 2.883946516_eV, 2.890948342_eV, 2.897377698_eV, 2.904990895_eV, 2.914133981_eV, 2.923149418_eV, 2.93084661_eV, 2.93754637_eV, 2.942295531_eV,
                              2.948393432_eV, 2.950505154_eV, 2.953888442_eV, 2.956461509_eV, 2.959992269_eV, 2.962296518_eV, 2.963894507_eV, 2.966508035_eV, 2.969782779_eV, 2.972055663_eV, 2.97447451_eV,
                              2.976897154_eV, 2.979993842_eV, 2.982571392_eV, 2.984057776_eV, 2.986510592_eV, 2.989977852_eV, 2.992336239_eV, 2.994789689_eV, 2.997247019_eV, 2.999594545_eV, 3.002766198_eV,
                              3.006660177_eV, 3.009685411_eV, 3.012724858_eV, 3.017190476_eV, 3.021169347_eV, 3.024479237_eV, 3.02868571_eV, 3.033628622_eV, 3.037260887_eV, 3.039760862_eV, 3.0437672_eV,
                              3.049236157_eV, 3.054563595_eV, 3.059786635_eV, 3.065879764_eV, 3.072860517_eV, 3.083715748_eV, 3.098728373_eV, 3.111650017_eV},
    fPSScintillationComponent1{this,
                               0.077888009, 0.082150664, 0.088739682, 0.095756293, 0.103193138, 0.111289285, 0.119298292, 0.126732782, 0.134934949, 0.143529913, 0.152476488, 0.16297777, 0.173540989, 0.186993338,
                               0.200955848, 0.211164882, 0.222622367, 0.232494545, 0.244232765, 0.255609754, 0.2722475, 0.289500739, 0.300091751, 0.314133944, 0.331890226, 0.347596397, 0.365647018, 0.380866094,
                               0.399555549, 0.412500396, 0.429919533, 0.45401665, 0.462738638, 0.476929472, 0.490301698, 0.497266344, 0.504161567, 0.515877668, 0.523951135, 0.535893102, 0.543232708, 0.557756994,
                               0.566009808, 0.583304467, 0.594966465, 0.606232199, 0.620023278, 0.635371167, 0.647351693, 0.660163631, 0.679587504, 0.700735441, 0.721714308, 0.742391928, 0.760771645, 0.777741956,
                               0.788358215, 0.804450384, 0.826447798, 0.843659688, 0.86502977, 0.884261775, 0.899289116, 0.916822104, 0.928268553, 0.938936237, 0.948338711, 0.961042779, 0.969245089, 0.982328519,
                               0.995048127, 0.998512266, 1, 0.99249575, 0.981785089, 0.960954079, 0.931809338, 0.898882312, 0.87618235, 0.850207553, 0.821478459, 0.794677086, 0.772790048, 0.750823072, 0.725797968,
                               0.6979187, 0.674004238, 0.65037776, 0.626744929, 0.595646008, 0.571557652, 0.552377475, 0.530034237, 0.504213142, 0.480734358, 0.458517559, 0.436292167, 0.413344652, 0.385161025,
                               0.356410043, 0.337410262, 0.313685191, 0.286478918, 0.263165205, 0.240645736, 0.218947384, 0.198340354, 0.180335346, 0.165189116, 0.14669725, 0.121817485, 0.101515975, 0.079466925,
                               0.056909146, 0.0343247, 0.016377592, 0.007494536, 0.00300246},
    fPSScintillationTimeConstant1{this, 2.1_ns},
    fPSScintillationYield{this, 10000 * 0.64},
    fPSResolutionScale{this, 1},

    // SiPM
    fSiPMEnergyBin{this,
                   1.305431375_eV, 1.318930645_eV, 1.346784438_eV, 1.37140206_eV, 1.410843362_eV, 1.43950485_eV, 1.465977332_eV, 1.500469355_eV,
                   1.542197517_eV, 1.562985965_eV, 1.590268701_eV, 1.628855701_eV, 1.656354489_eV, 1.693747036_eV, 1.721174714_eV, 1.747108857_eV,
                   1.766466373_eV, 1.796320525_eV, 1.835087888_eV, 1.883876227_eV, 1.923654111_eV, 1.960616839_eV, 1.992781276_eV, 2.013226883_eV,
                   2.034096376_eV, 2.08054917_eV, 2.122088259_eV, 2.147094414_eV, 2.172696928_eV, 2.214186634_eV, 2.251315222_eV, 2.283561026_eV,
                   2.316743972_eV, 2.368366892_eV, 2.399556673_eV, 2.429263293_eV, 2.459714673_eV, 2.495813443_eV, 2.540555674_eV, 2.581695073_eV,
                   2.616114959_eV, 2.648711918_eV, 2.67931431_eV, 2.713515524_eV, 2.748601178_eV, 2.784606031_eV, 2.818449194_eV, 2.853125116_eV,
                   2.878884731_eV, 2.918408274_eV, 2.955603674_eV, 2.990250065_eV, 3.022133712_eV, 3.051050991_eV, 3.110578109_eV, 3.164602846_eV,
                   3.212425963_eV, 3.249252716_eV, 3.282703744_eV, 3.30396266_eV, 3.329839664_eV, 3.360546536_eV, 3.446821871_eV, 3.532744564_eV,
                   3.587394333_eV, 3.648973726_eV, 3.664700323_eV, 3.691214739_eV, 3.712704122_eV, 3.745411477_eV, 3.761982214_eV, 3.77870023_eV,
                   3.789928368_eV, 3.795567497_eV, 3.829757849_eV, 3.841291928_eV, 3.852895692_eV, 3.876314812_eV, 3.911982213_eV, 3.966731246_eV,
                   3.997814734_eV, 4.133866021_eV},
    fSiPMEfficiency{this,
                    0.109781735, 0.107546001, 0.137524711, 0.149210659, 0.182757886, 0.205647423, 0.22730502, 0.253906669, 0.297162903, 0.31483807,
                    0.341116517, 0.383907441, 0.412938712, 0.445629255, 0.473641265, 0.49713988, 0.519612426, 0.54757919, 0.58024284, 0.612078653,
                    0.648819193, 0.662439631, 0.683104141, 0.694943549, 0.710900897, 0.737136788, 0.759337226, 0.77782606, 0.790427109, 0.816202571,
                    0.834617473, 0.859048541, 0.88109146, 0.906100928, 0.922411175, 0.938736516, 0.953430845, 0.966095375, 0.987117201, 0.993333813,
                    0.997740037, 1, 0.997556662, 0.995153729, 0.991921918, 0.982521663, 0.97215177, 0.956325779, 0.946812706, 0.923781929, 0.900677187,
                    0.872952471, 0.84780232, 0.820642654, 0.763753225, 0.7129909, 0.671777197, 0.638915456, 0.604741592, 0.581750316, 0.555870629,
                    0.532873858, 0.485535492, 0.452210909, 0.427231352, 0.399663205, 0.381536125, 0.354715371, 0.335540548, 0.308960287, 0.288618891,
                    0.256954072, 0.238067205, 0.220045292, 0.176450298, 0.155669426, 0.140730177, 0.119666806, 0.097119843, 0.064072528, 0.050073861,
                    0.046832098},

    // fiber
    fWLSRIndexEnergy{this,
                     2.00_eV, 2.03_eV, 2.06_eV, 2.09_eV, 2.12_eV, 2.15_eV, 2.18_eV, 2.21_eV, 2.24_eV, 2.27_eV,
                     2.30_eV, 2.33_eV, 2.36_eV, 2.39_eV, 2.42_eV, 2.45_eV, 2.48_eV, 2.51_eV, 2.54_eV, 2.57_eV,
                     2.60_eV, 2.63_eV, 2.66_eV, 2.69_eV, 2.72_eV, 2.75_eV, 2.78_eV, 2.81_eV, 2.84_eV, 2.87_eV,
                     2.90_eV, 2.93_eV, 2.96_eV, 2.99_eV, 3.02_eV, 3.05_eV, 3.08_eV, 3.11_eV, 3.14_eV, 3.17_eV,
                     3.20_eV, 3.23_eV, 3.26_eV, 3.29_eV, 3.32_eV, 3.35_eV, 3.38_eV, 3.41_eV, 3.44_eV, 3.47_eV},
    fWLSRIndex{this,
               1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
               1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
               1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
               1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
               1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60},
    fWLSVAbsEnergy{this,
                   1.910850344_eV, 1.940785336_eV, 1.970888993_eV, 2.001132814_eV, 2.040688494_eV, 2.071396918_eV, 2.111107026_eV,
                   2.141209229_eV, 2.180785635_eV, 2.220856839_eV, 2.261395753_eV, 2.301302736_eV, 2.34043068_eV, 2.380912184_eV},
    fWLSVAbsLength{this,
                   14.49489342_m, 16.81308915_m, 20.64029605_m, 15.52541632_m, 7.587889914_m, 12.70061337_m, 18.20429215_m, 19.09754214_m,
                   17.39172749_m, 16.99931524_m, 16.29954689_m, 12.80542565_m, 10.12174192_m, 8.388157991_m},
    fWLSAbsEnergy{this,
                  1.997981846_eV, 2.027062605_eV, 2.057002412_eV, 2.085755333_eV, 2.114253037_eV, 2.142441084_eV, 2.171390915_eV,
                  2.201133835_eV, 2.229321308_eV, 2.258240077_eV, 2.286666787_eV, 2.315818293_eV, 2.343091665_eV, 2.372361386_eV,
                  2.400991064_eV, 2.43032019_eV, 2.457480388_eV, 2.486733706_eV, 2.513663605_eV, 2.542729703_eV, 2.570892934_eV,
                  2.599687023_eV, 2.627480008_eV, 2.655873678_eV, 2.684887721_eV, 2.71278016_eV, 2.741258214_eV, 2.768504811_eV,
                  2.796298478_eV, 2.824655859_eV, 2.851646616_eV, 2.881143603_eV, 2.909230049_eV, 2.937869479_eV, 2.96497279_eV,
                  2.99258084_eV, 3.020707862_eV, 3.049368628_eV, 3.076311711_eV, 3.10604253_eV, 3.134001011_eV, 3.157687135_eV,
                  3.189019663_eV, 3.213547981_eV, 3.240968652_eV, 3.271420824_eV, 3.299842395_eV, 3.326112141_eV, 3.355496222_eV,
                  3.382663197_eV},
    fWLSAbsLength{this,
                  4918.459907_mm, 5000_mm, 4918.459907_mm, 5000_mm, 5000_mm, 5000_mm, 4918.459907_mm, 4918.459907_mm, 4918.459907_mm,
                  4918.459907_mm, 4918.459907_mm, 5000_mm, 5000_mm, 4918.459907_mm, 4918.459907_mm, 5000_mm, 5000_mm, 3971.895759_mm,
                  3003.330134_mm, 1991.046281_mm, 981.8021971_mm, 1.837435671_mm, 0.80754867_mm, 0.493108677_mm, 0.40481092_mm,
                  0.411522029_mm, 0.439497656_mm, 0.425279869_mm, 0.372861786_mm, 0.337833462_mm, 0.360799676_mm, 0.411522029_mm,
                  0.454190766_mm, 0.518042333_mm, 0.571755648_mm, 0.620747254_mm, 0.696467552_mm, 0.756145256_mm, 0.921076403_mm,
                  1.121982495_mm, 1.412401738_mm, 1.930344175_mm, 2.390375027_mm, 3.161264333_mm, 3.914642483_mm, 4.690743236_mm,
                  981.8021971_mm, 1991.046281_mm, 3003.330134_mm, 3971.895759_mm},
    fWLSEmissionEnergy{this,
                       2.00_eV, 2.03_eV, 2.06_eV, 2.09_eV, 2.12_eV, 2.15_eV, 2.18_eV, 2.21_eV, 2.24_eV, 2.27_eV, 2.30_eV,
                       2.33_eV, 2.36_eV, 2.39_eV, 2.42_eV, 2.45_eV, 2.48_eV, 2.51_eV, 2.54_eV, 2.57_eV, 2.60_eV, 2.63_eV,
                       2.66_eV, 2.69_eV, 2.72_eV, 2.75_eV, 2.78_eV, 2.81_eV, 2.84_eV, 2.87_eV, 2.90_eV, 2.93_eV, 2.96_eV,
                       2.99_eV, 3.02_eV, 3.05_eV, 3.08_eV, 3.11_eV, 3.14_eV, 3.17_eV, 3.20_eV, 3.23_eV, 3.26_eV, 3.29_eV,
                       3.32_eV, 3.35_eV, 3.38_eV, 3.41_eV, 3.44_eV, 3.47_eV},
    fWLSEmissionAmplitude{this,
                          0.05, 0.10, 0.30, 0.50, 0.75, 1.00, 1.50, 1.85, 2.30, 2.75,
                          3.25, 3.80, 4.50, 5.20, 6.00, 7.00, 8.50, 9.50, 11.1, 12.4,
                          12.9, 13.0, 12.8, 12.3, 11.1, 11.0, 12.0, 11.0, 17.0, 16.9,
                          15.0, 9.00, 2.50, 1.00, 0.05, 0.00, 0.00, 0.00, 0.00, 0.00,
                          0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
    fCategoryConfiguration{this, [this] { return CalculateCategoryConfiguration(); }},
    fStripInformation{this, [this] { return CalculateStripInformation(); }},
    fStartingStripIDOfAModule{this, [this] { return CalculateStartingStripIDOfAModule(); }} {}

auto PDSVeto::CalculateCategoryConfiguration() const -> std::vector<CategoryConfigurationType> {
    std::vector<double> moduleLengths;
    std::vector<double> moduleThicknesses;
    std::vector<double> moduleWidths;
    for (int categoryID{}; categoryID < (*fNModuleOfACategory).size(); ++categoryID) {
        moduleLengths.emplace_back((*fStripLengthOfACategory)[categoryID] + (*fSiPMThickness + *fSiPMCouplerThickness) * 2);
        moduleWidths.emplace_back(((*fPSWidth + *fReflectiveFilmThickness * 2) + *fInterPSGap) * (*fNStripPerLayerOfACategory)[categoryID] - *fInterPSGap + *fModuleOffset * ((*fNLayerPerModuleOfACategory)[categoryID] - 1));
        moduleThicknesses.emplace_back(((*fPSThickness + *fReflectiveFilmThickness * 2) + *fAlAbsorberThickness) * (*fNLayerPerModuleOfACategory)[categoryID] - *fAlAbsorberThickness);
    }
    const auto sideModuleXShift{fSolenoidWindowRadius + moduleWidths[2] + moduleThicknesses[1] / 2 + *fPerpendicularModuleGap};
    const G4ThreeVector side0ModuleCenter{sideModuleXShift, 0, 0};
    const G4ThreeVector side1ModuleCenter{-sideModuleXShift, 0, 0};

    const auto cap2ModuleYShift{fSolenoidWindowRadius + moduleWidths[3] / 2};
    const auto cap2ModuleZShift{moduleWidths[0] / 2 + *fPerpendicularModuleGap + moduleThicknesses[2] + *fParallelModuleGap + moduleThicknesses[3] / 2};
    const G4ThreeVector cap2Module0Center{0, cap2ModuleYShift, cap2ModuleZShift};
    const G4ThreeVector cap2Module1Center{0, -cap2ModuleYShift, cap2ModuleZShift};
    const auto cap2Module2Center{-cap2Module0Center};
    const auto cap2Module3Center{-cap2Module1Center};

    const auto cap1ModuleXShift{fSolenoidWindowRadius + moduleWidths[2] / 2};
    const auto cap1ModuleZShift(moduleWidths[0] / 2 + *fPerpendicularModuleGap + moduleThicknesses[2] / 2);
    const G4ThreeVector cap1Module0Center{cap1ModuleXShift, 0, cap1ModuleZShift};
    const G4ThreeVector cap1Module1Center{-cap1ModuleXShift, 0, cap1ModuleZShift};
    const auto cap1Module2Center{-cap1Module0Center};
    const auto cap1Module3Center{-cap1Module1Center};

    const auto topModuleYShift{moduleWidths[1] / 2 + *fPerpendicularModuleGap + moduleThicknesses[0] / 2};
    const G4ThreeVector topModuleCenter{0, topModuleYShift, 0};

    const auto topModuleRotation{G4RotateY3D{pi / 2}.getRotation()};

    const auto side0ModuleRotation{G4RotateZ3D{pi / 2}.getRotation()};
    const auto side1ModuleRotation{G4RotateZ3D{-pi / 2}.getRotation()};

    const auto cap1ModuleRotation{G4RotateX3D{pi / 2}.getRotation()};
    const auto cap2ModuleRotation{(G4RotateZ3D{pi / 2} * G4RotateX3D{pi / 2}).getRotation()};
    const auto& ecalField{Description::ECALField::Instance()};
    const auto x0{Mustard::VectorCast<G4ThreeVector>(ecalField.Center())};

    const G4Transform3D topModuleTransform{topModuleRotation, topModuleCenter + x0};

    const G4Transform3D side0ModuleTransform{side0ModuleRotation, side0ModuleCenter + x0};
    const G4Transform3D side1ModuleTransform{side1ModuleRotation, side1ModuleCenter + x0};

    const G4Transform3D cap1Module0Transform{cap1ModuleRotation, cap1Module0Center + x0};
    const G4Transform3D cap1Module1Transform{cap1ModuleRotation, cap1Module1Center + x0};
    const G4Transform3D cap1Module2Transform{cap1ModuleRotation, cap1Module2Center + x0};
    const G4Transform3D cap1Module3Transform{cap1ModuleRotation, cap1Module3Center + x0};

    const G4Transform3D cap2Module0Transform{cap2ModuleRotation, cap2Module0Center + x0};
    const G4Transform3D cap2Module1Transform{cap2ModuleRotation, cap2Module1Center + x0};
    const G4Transform3D cap2Module2Transform{cap2ModuleRotation, cap2Module2Center + x0};
    const G4Transform3D cap2Module3Transform{cap2ModuleRotation, cap2Module3Center + x0};

    std::vector<CategoryConfigurationType> categoryConfigurationS{};
    const std::vector<G4Transform3D> moduleTransformS{topModuleTransform, side0ModuleTransform, side1ModuleTransform, cap1Module0Transform, cap1Module1Transform, cap1Module2Transform, cap1Module3Transform, cap2Module0Transform, cap2Module1Transform, cap2Module2Transform, cap2Module3Transform};
    int categoryID{};
    int moduleID{};
    int layerID{};
    int stripID{};
    for (auto nModule : *fNModuleOfACategory) {
        struct CategoryConfigurationType aCategoryConfig;
        CategoryConfigurationType::ModuleConfiguration aModuleConfig;
        CategoryConfigurationType::ModuleConfiguration::AlLayerConfiguration aLayerConfig;
        CategoryConfigurationType::ModuleConfiguration::StripConfiguration aStripConfig;
        aCategoryConfig.categoryID = categoryID;
        aCategoryConfig.moduleLength = moduleLengths[categoryID];
        aCategoryConfig.moduleWidth = moduleWidths[categoryID];
        aCategoryConfig.moduleThickness = moduleThicknesses[categoryID];
        for (int moduleLocalID{}; moduleLocalID < nModule; ++moduleLocalID) {
            aModuleConfig.moduleID = moduleID;
            aModuleConfig.moduleLocalID = moduleLocalID;
            aModuleConfig.moduleTransform = moduleTransformS[moduleID];
            for (int layerLocalID{}; layerLocalID < (*fNLayerPerModuleOfACategory)[categoryID]; ++layerLocalID) {
                // clang-format off
                auto layerYShift{
                                -(moduleThicknesses[categoryID]/2-(*fPSThickness+2*(*fReflectiveFilmThickness))/2)
                                +layerLocalID*((*fPSThickness+2*(*fReflectiveFilmThickness))+*fAlAbsorberThickness)
                                    };
                auto alAbsorberYShift{
                                layerYShift - (fPSThickness + 2 * fReflectiveFilmThickness) / 2 - fAlAbsorberThickness / 2};
                // clang-format on
                // auto layerLocalTransform{
                //     G4Transform3D{G4RotationMatrix::IDENTITY, G4ThreeVector{0, layerYShift, 0}}
                // };
                auto alAbsorberLocalTransform{
                    G4Transform3D{G4RotationMatrix::IDENTITY, G4ThreeVector{0, alAbsorberYShift, 0}}
                }; // relative to modulebox

                aLayerConfig.layerID = layerID;
                aLayerConfig.layerLocalID = layerLocalID;
                // aLayerConfig.layerLocalTransform = layerLocalTransform;
                aLayerConfig.alAbsorberLocalTransform = alAbsorberLocalTransform; // first Transform not used, only absorber between layers

                aModuleConfig.alLayers.emplace_back(aLayerConfig);
                ++layerID;
                for (int stripCountInLayer{}; stripCountInLayer < (*fNStripPerLayerOfACategory)[categoryID]; ++stripCountInLayer) {
                    // clang-format off
                    auto stripXShift{
                                    -(moduleWidths[categoryID]/2-(*fPSWidth+2*(*fReflectiveFilmThickness))/2)
                                    +stripCountInLayer*(*fPSWidth+2*(*fReflectiveFilmThickness)+*fInterPSGap)
                                    +layerLocalID*(*fModuleOffset)
                    };
                    // clang-format on
                    auto stripLocalTransform{
                        G4Transform3D{G4RotationMatrix::IDENTITY, G4ThreeVector{stripXShift, layerYShift, 0}}
                    };

                    aStripConfig.stripID = stripID;
                    aStripConfig.stripLocalID = stripCountInLayer + layerLocalID * (*fNStripPerLayerOfACategory)[categoryID];
                    aStripConfig.stripLocalTransform = stripLocalTransform;
                    aModuleConfig.strips.emplace_back(aStripConfig);
                    ++stripID;
                }
            };
            aCategoryConfig.modules.emplace_back(aModuleConfig);
            ++moduleID;
        }
        categoryConfigurationS.emplace_back(aCategoryConfig);
        ++categoryID;
    }
    return categoryConfigurationS;
}

auto PDSVeto::CalculateStripInformation() const -> std::vector<StripInformationType> {
    std::vector<StripInformationType> stripInformationS{};
    int moduleID{};
    int layerID{};
    int stripID{};
    for (auto nModule : *fNModuleOfACategory) {
        int categoryID{};
        for (int moduleLocalID{}; moduleLocalID < nModule; ++moduleLocalID) {
            for (int layerLocalID{}; layerLocalID < (*fNLayerPerModuleOfACategory)[categoryID]; ++layerLocalID) {
                for (int stripLocalID; stripLocalID < (*fNStripPerLayerOfACategory)[categoryID]; ++stripLocalID) {
                    double x{((categoryID == 1) && (categoryID == 4)) ? 1. : 0.},
                        y{(categoryID == 3) ? 1. : 0.},
                        z{(categoryID == 2) ? 1. : 0.};
                    muc::array3d readDirection{x, y, z};
                    stripInformationS.emplace_back(StripInformationType{stripID, stripLocalID, layerID, layerLocalID, moduleID, moduleLocalID, categoryID, (*fStripLengthOfACategory)[categoryID], readDirection});
                    ++stripLocalID;
                }
                ++layerID;
            }
            ++moduleID;
        }
        ++categoryID;
    }
    return stripInformationS;
}

auto PDSVeto::CalculateStartingStripIDOfAModule() const -> std::vector<short> {
    const auto totalNModules{std::accumulate(fNModuleOfACategory->begin(), fNModuleOfACategory->end(), 0)};
    auto nStripOfAModule{[this](short& aModuleID) {
        auto categoryIDOfAModule{[](short& aModuleID) {
            if (aModuleID == 0) return 0;
            if (aModuleID == 1 or aModuleID == 2) return 1;
            if (aModuleID == 3 or aModuleID == 4 or aModuleID == 5 or aModuleID == 6) return 2;
            if (aModuleID == 7 or aModuleID == 8 or aModuleID == 9 or aModuleID == 10) return 3;
        }};
        return (*fNLayerPerModuleOfACategory)[categoryIDOfAModule(aModuleID)] * (*fNStripPerLayerOfACategory)[categoryIDOfAModule(aModuleID)];
    }};

    std::vector<short> startingStripIDS{};
    short stripIDAccumulation{};
    for (short thisModuleID{}; thisModuleID < totalNModules; ++thisModuleID) {
        startingStripIDS.emplace_back(stripIDAccumulation);
        stripIDAccumulation += nStripOfAModule(thisModuleID);
    }
    return startingStripIDS;
}

auto PDSVeto::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fNModuleOfACategory, "NModuleOfACategory");
    ImportValue(node, fNLayerPerModuleOfACategory, "NLayerPerModuleOfACategory");
    ImportValue(node, fNStripPerLayerOfACategory, "NStripPerLayerOfACategory");
    ImportValue(node, fStripLengthOfACategory, "StripLengthOfACategory");
    ImportValue(node, fPSWidth, "PSWidth");
    ImportValue(node, fPSThickness, "PSThickness");
    ImportValue(node, fPSFiberRadius, "PSFiberRadius");
    ImportValue(node, fPSHoleRadius, "PSHoleRadius");
    ImportValue(node, fInterPSGap, "InterPSGap");
    ImportValue(node, fPerpendicularModuleGap, "PerpendicularModuleGap");
    ImportValue(node, fModuleOffset, "ModuleOffset");
    ImportValue(node, fParallelModuleGap, "ParallelModuleGap");
    ImportValue(node, fAlAbsorberThickness, "AlAbsorberThickness");
    ImportValue(node, fReflectiveFilmThickness, "ReflectiveFilmThickness");
    ImportValue(node, fSiPMThickness, "SiPMThickness");
    ImportValue(node, fSiPMCathodeThickness, "SiPMCathodeThickness");
    ImportValue(node, fSiPMCouplerThickness, "SiPMCouplerThickness");
    ImportValue(node, fSiPMSize, "SiPMSize");
    ImportValue(node, fSolenoidWindowRadius, "SolenoidWindowRadius");
    ImportValue(node, fFiberNum, "FiberNum");
    ImportValue(node, fSelectedCategory, "SelectedCategory");
}
auto PDSVeto::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry

    ExportValue(node, fNModuleOfACategory, "NModuleOfACategory");
    ExportValue(node, fNLayerPerModuleOfACategory, "NLayerPerModuleOfACategory");
    ExportValue(node, fNStripPerLayerOfACategory, "NStripPerLayerOfACategory");
    ExportValue(node, fStripLengthOfACategory, "StripLengthOfACategory");
    ExportValue(node, fPSWidth, "PSWidth");
    ExportValue(node, fPSThickness, "PSThickness");
    ExportValue(node, fPSFiberRadius, "PSFiberRadius");
    ExportValue(node, fPSHoleRadius, "PSHoleRadius");
    ExportValue(node, fInterPSGap, "InterPSGap");
    ExportValue(node, fPerpendicularModuleGap, "PerpendicularModuleGap");
    ExportValue(node, fReflectiveFilmThickness, "ReflectiveFilmThickness");
    ExportValue(node, fModuleOffset, "ModuleOffset");
    ExportValue(node, fAlAbsorberThickness, "AlAbsorberThickness");
    ExportValue(node, fSiPMThickness, "SiPMThickness");
    ExportValue(node, fSiPMCathodeThickness, "SiPMCathodeThickness");
    ExportValue(node, fSiPMCouplerThickness, "SiPMCouplerThickness");
    ExportValue(node, fSiPMSize, "SiPMSize");
    ExportValue(node, fSolenoidWindowRadius, "SolenoidWindowRadius");
    ExportValue(node, fFiberNum, "FiberNum");
    ExportValue(node, fSelectedCategory, "SelectedCategory");
}
} // namespace MACE::Detector::Description
