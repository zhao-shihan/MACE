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

#include "muc/utility"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::LiteralUnit::Time;
using namespace Mustard::MathConstant;

PDSVeto::PDSVeto() :
    DescriptionWithCacheBase{"PDSVeto"},

    /*  SiPM: microfc-30035-smt
        plastic scintillator: EJ-200
        coupler: EJ-550
        wls fiber: KURARAY Y-11
                    (may be BICRON BCF-92 later)*/
    // ECAL solenoid
    fSolenoidWindowRadius{this, 14_cm},

    fNModuleOfACategory{this, 1, 2, 4, 4},
    fNLayerPerModuleOfACategory{this, 3, 2, 2, 2},
    fNStripPerLayerOfACategory{this, 12, 16, 5, 8},
    fStripLengthOfACategory{this, 145_cm, 140_cm, 180_cm, 35_cm},

    // plastic scintillator
    fPSWidth{this, 10_cm},
    fPSThickness{this, 2_cm},
    fPSScintillationEnergyBin{this, {}},
    fPSScintillationComponent1{this, {}},
    fPSScintillationYield{this, 10000.},
    fPSScintillationTimeConstant1{this, 2.1_ns},
    fPSResolutionScale{this, 1.},

    // SiPM
    fSiPMThickness{this, 0.41_mm},
    fSiPMCathodeThickness{this, 0.2_mm},
    fSiPMCouplerThickness{this, 0.1_mm},
    fSiPMSize{this, 4_mm},
    fSiPMEnergyBin{this, {}},
    fSiPMEfficiency{this, {}},

    // Fiber
    fFiberHoleRadius{this, 0.75_mm},
    fFiberRadius{this, 0.7_mm},
    fFiberInnerRadiusRatio{this, 0.98},
    fFiberCoreRadiusRatio{this, 0.96},
    // fiber outer - FP (Fluorinated Polymer)
    fFPRIndexEnergy{this, 2.00_eV, 3.47_eV},
    fFPRIndex{this, 1.42, 1.42},
    fFPAbsEnergy{this, 2.00_eV, 3.47_eV},
    fFPAbsLength{this, 20.0_m, 20.0_m},
    // fiber inner - PMMA
    fPMMARIndexEnergy{this, 2.00_eV, 3.47_eV},
    fPMMARIndex{this, 1.49, 1.49},
    fPMMAAbsEnergy{this, 2.00_eV, 3.47_eV},
    fPMMAAbsLength{this, 20.0_m, 20.0_m},
    // fiber core - WLS PS
    fWLSRIndexEnergy{this, 2.00_eV, 3.47_eV},
    fWLSRIndex{this, 1.60, 1.60},
    fWLSVAbsEnergy{this, {}},
    fWLSVAbsLength{this, {}},
    fWLSAbsEnergy{this, {}},
    fWLSAbsLength{this, {}},
    fWLSEmissionEnergy{this, {}},
    fWLSEmissionAmplitude{this, {}},
    // fiber material [BICRON BCF-92]
    // fiber clad - PMMA defined before
    // fiber core - WLS PS BCF92

    fInterPSGap{this, 1_mm},
    fPerpendicularModuleGap{this, 0.5_cm},
    fParallelModuleGap{this, 1_cm},
    fModuleOffset{this, 1_cm},

    fAlAbsorberThickness{this, 0.6_cm},
    fReflectiveFilmThickness{this, 0.4_mm},

    fFiberNum{this, 4},
    fSelectedCategory{this, -1},

    fCategoryConfiguration{this, [this] { return CalculateCategoryConfiguration(); }},
    fStripInformation{this, [this] { return CalculateStripInformation(); }},
    fStartingStripIDOfAModule{this, [this] { return CalculateStartingStripIDOfAModule(); }} {
    fPSScintillationEnergyBin = {2.482953109_eV, 2.489659196_eV, 2.496003695_eV, 2.502381059_eV, 2.508791544_eV, 2.515235634_eV, 2.521712914_eV, 2.528223186_eV, 2.53476796_eV, 2.541347168_eV, 2.548161747_eV,
                                 2.554661489_eV, 2.561202446_eV, 2.567815247_eV, 2.574829427_eV, 2.579956087_eV, 2.585046827_eV, 2.590273296_eV, 2.596648064_eV, 2.602100665_eV, 2.608203377_eV, 2.613926041_eV,
                                 2.61797784_eV, 2.622401485_eV, 2.628222987_eV, 2.632330767_eV, 2.637208697_eV, 2.643026898_eV, 2.647008211_eV, 2.651842137_eV, 2.658691238_eV, 2.665141972_eV, 2.671429914_eV,
                                 2.677283888_eV, 2.685400294_eV, 2.69325325_eV, 2.699300679_eV, 2.706719316_eV, 2.713494146_eV, 2.719892644_eV, 2.726076443_eV, 2.73102463_eV, 2.737402211_eV, 2.742231678_eV,
                                 2.748404443_eV, 2.754115306_eV, 2.759358856_eV, 2.764781943_eV, 2.76890398_eV, 2.776072945_eV, 2.782386965_eV, 2.789212011_eV, 2.795753365_eV, 2.802196767_eV, 2.806414568_eV,
                                 2.811221166_eV, 2.814980328_eV, 2.819868451_eV, 2.825619424_eV, 2.831284734_eV, 2.836501956_eV, 2.84333131_eV, 2.849700132_eV, 2.854645037_eV, 2.859428074_eV, 2.864396308_eV,
                                 2.869215654_eV, 2.876671121_eV, 2.883946516_eV, 2.890948342_eV, 2.897377698_eV, 2.904990895_eV, 2.914133981_eV, 2.923149418_eV, 2.93084661_eV, 2.93754637_eV, 2.942295531_eV,
                                 2.948393432_eV, 2.950505154_eV, 2.953888442_eV, 2.956461509_eV, 2.959992269_eV, 2.962296518_eV, 2.963894507_eV, 2.966508035_eV, 2.969782779_eV, 2.972055663_eV, 2.97447451_eV,
                                 2.976897154_eV, 2.979993842_eV, 2.982571392_eV, 2.984057776_eV, 2.986510592_eV, 2.989977852_eV, 2.992336239_eV, 2.994789689_eV, 2.997247019_eV, 2.999594545_eV, 3.002766198_eV,
                                 3.006660177_eV, 3.009685411_eV, 3.012724858_eV, 3.017190476_eV, 3.021169347_eV, 3.024479237_eV, 3.02868571_eV, 3.033628622_eV, 3.037260887_eV, 3.039760862_eV, 3.0437672_eV,
                                 3.049236157_eV, 3.054563595_eV, 3.059786635_eV, 3.065879764_eV, 3.072860517_eV, 3.083715748_eV, 3.098728373_eV, 3.111650017_eV};
    fPSScintillationComponent1 = {0.077888009, 0.082150664, 0.088739682, 0.095756293, 0.103193138, 0.111289285, 0.119298292, 0.126732782, 0.134934949, 0.143529913, 0.152476488, 0.16297777, 0.173540989, 0.186993338,
                                  0.200955848, 0.211164882, 0.222622367, 0.232494545, 0.244232765, 0.255609754, 0.2722475, 0.289500739, 0.300091751, 0.314133944, 0.331890226, 0.347596397, 0.365647018, 0.380866094,
                                  0.399555549, 0.412500396, 0.429919533, 0.45401665, 0.462738638, 0.476929472, 0.490301698, 0.497266344, 0.504161567, 0.515877668, 0.523951135, 0.535893102, 0.543232708, 0.557756994,
                                  0.566009808, 0.583304467, 0.594966465, 0.606232199, 0.620023278, 0.635371167, 0.647351693, 0.660163631, 0.679587504, 0.700735441, 0.721714308, 0.742391928, 0.760771645, 0.777741956,
                                  0.788358215, 0.804450384, 0.826447798, 0.843659688, 0.86502977, 0.884261775, 0.899289116, 0.916822104, 0.928268553, 0.938936237, 0.948338711, 0.961042779, 0.969245089, 0.982328519,
                                  0.995048127, 0.998512266, 1.0, 0.99249575, 0.981785089, 0.960954079, 0.931809338, 0.898882312, 0.87618235, 0.850207553, 0.821478459, 0.794677086, 0.772790048, 0.750823072, 0.725797968,
                                  0.6979187, 0.674004238, 0.65037776, 0.626744929, 0.595646008, 0.571557652, 0.552377475, 0.530034237, 0.504213142, 0.480734358, 0.458517559, 0.436292167, 0.413344652, 0.385161025,
                                  0.356410043, 0.337410262, 0.313685191, 0.286478918, 0.263165205, 0.240645736, 0.218947384, 0.198340354, 0.180335346, 0.165189116, 0.14669725, 0.121817485, 0.101515975, 0.079466925,
                                  0.056909146, 0.0343247, 0.016377592, 0.007494536, 0.00300246};
    fSiPMEnergyBin = {1.308590_eV, 1.316035_eV, 1.323565_eV, 1.331182_eV, 1.338883_eV, 1.346619_eV, 1.354558_eV, 1.364726_eV, 1.375046_eV,
                      1.384019_eV, 1.393109_eV, 1.401241_eV, 1.408531_eV, 1.417155_eV, 1.425888_eV, 1.434728_eV, 1.443679_eV, 1.452741_eV,
                      1.461918_eV, 1.471211_eV, 1.480623_eV, 1.490158_eV, 1.499815_eV, 1.509596_eV, 1.519507_eV, 1.529548_eV, 1.539721_eV,
                      1.550031_eV, 1.560481_eV, 1.571073_eV, 1.581807_eV, 1.592690_eV, 1.603723_eV, 1.614908_eV, 1.626250_eV, 1.637752_eV,
                      1.649418_eV, 1.661251_eV, 1.673256_eV, 1.685436_eV, 1.697794_eV, 1.710332_eV, 1.723057_eV, 1.735972_eV, 1.749081_eV,
                      1.762386_eV, 1.775897_eV, 1.789617_eV, 1.803551_eV, 1.817703_eV, 1.832078_eV, 1.846685_eV, 1.861524_eV, 1.876604_eV,
                      1.891927_eV, 1.907501_eV, 1.923336_eV, 1.939436_eV, 1.955806_eV, 1.972454_eV, 1.989387_eV, 2.006610_eV, 2.024133_eV,
                      2.041965_eV, 2.060114_eV, 2.077735_eV, 2.095660_eV, 2.114775_eV, 2.134243_eV, 2.152247_eV, 2.169634_eV, 2.189179_eV,
                      2.207167_eV, 2.223515_eV, 2.242073_eV, 2.260938_eV, 2.279093_eV, 2.296512_eV, 2.314204_eV, 2.333237_eV, 2.351498_eV,
                      2.367848_eV, 2.383314_eV, 2.398979_eV, 2.414851_eV, 2.430933_eV, 2.447233_eV, 2.463751_eV, 2.480495_eV, 2.497468_eV,
                      2.514672_eV, 2.532116_eV, 2.549803_eV, 2.567740_eV, 2.585937_eV, 2.605721_eV, 2.628519_eV, 2.653105_eV, 2.676751_eV,
                      2.700822_eV, 2.726786_eV, 2.754744_eV, 2.786349_eV, 2.820250_eV, 2.855002_eV, 2.890648_eV, 2.927214_eV, 2.964762_eV,
                      3.003313_eV, 3.037467_eV, 3.068708_eV, 3.098714_eV, 3.125469_eV, 3.152692_eV, 3.180394_eV, 3.204544_eV, 3.224947_eV,
                      3.247711_eV, 3.270837_eV, 3.287878_eV, 3.302918_eV, 3.318113_eV, 3.335613_eV, 3.366626_eV, 3.405046_eV, 3.449010_eV,
                      3.501305_eV, 3.547788_eV, 3.590485_eV, 3.632242_eV, 3.653483_eV, 3.673341_eV, 3.691081_eV, 3.711334_eV, 3.729458_eV,
                      3.750148_eV, 3.757523_eV, 3.768152_eV, 3.778839_eV, 3.790695_eV, 3.794278_eV, 3.811046_eV, 3.821643_eV, 3.833164_eV,
                      3.841295_eV, 3.853475_eV, 3.859237_eV, 3.871024_eV, 3.892416_eV, 3.917577_eV, 3.938098_eV, 3.955904_eV, 3.979456_eV,
                      4.022527_eV, 4.093734_eV};
    fSiPMEfficiency = {0.009042, 0.009068, 0.009449, 0.009494, 0.010709, 0.011916, 0.012568, 0.013465, 0.015059, 0.015754, 0.016921, 0.016781,
                       0.017465, 0.018791, 0.019735, 0.020851, 0.021918, 0.023034, 0.024225, 0.025685, 0.026999, 0.027943, 0.029280, 0.030889,
                       0.032498, 0.033983, 0.036060, 0.037865, 0.039523, 0.041082, 0.043060, 0.045088, 0.047139, 0.049536, 0.052080, 0.054673,
                       0.057143, 0.059737, 0.062182, 0.064653, 0.067246, 0.070159, 0.073097, 0.076158, 0.079367, 0.083192, 0.086770, 0.090225,
                       0.093729, 0.097208, 0.100786, 0.104044, 0.107721, 0.111348, 0.115419, 0.119588, 0.123560, 0.127531, 0.131602, 0.135919,
                       0.140284, 0.145143, 0.150124, 0.155080, 0.160062, 0.165525, 0.171156, 0.176703, 0.182152, 0.188052, 0.193728, 0.200245,
                       0.206275, 0.211641, 0.217723, 0.224533, 0.232273, 0.239177, 0.245705, 0.252512, 0.259338, 0.265635, 0.271443, 0.277715,
                       0.284065, 0.290492, 0.296648, 0.303114, 0.309309, 0.315582, 0.322164, 0.328591, 0.335018, 0.341406, 0.347330, 0.353690,
                       0.360414, 0.366890, 0.373005, 0.379179, 0.385625, 0.392117, 0.397159, 0.402263, 0.406186, 0.408361, 0.409354, 0.407492,
                       0.403980, 0.398276, 0.392174, 0.385909, 0.379570, 0.373154, 0.366660, 0.360289, 0.355202, 0.348671, 0.340100, 0.333153,
                       0.327920, 0.321875, 0.316878, 0.311022, 0.304988, 0.299512, 0.295507, 0.290862, 0.284640, 0.276884, 0.267938, 0.256915,
                       0.247440, 0.237114, 0.227097, 0.216229, 0.206211, 0.194671, 0.183234, 0.171318, 0.162100, 0.149589, 0.138679, 0.128470,
                       0.117973, 0.105446, 0.099453, 0.092758, 0.082126, 0.072436, 0.063332, 0.055295, 0.044820, 0.041966, 0.041404};
    fWLSVAbsEnergy = {1.910850344_eV, 1.940785336_eV, 1.970888993_eV, 2.001132814_eV, 2.040688494_eV, 2.071396918_eV, 2.111107026_eV,
                      2.141209229_eV, 2.180785635_eV, 2.220856839_eV, 2.261395753_eV, 2.301302736_eV, 2.34043068_eV, 2.380912184_eV};
    fWLSVAbsLength = {14.49489342_m, 16.81308915_m, 20.64029605_m, 15.52541632_m, 7.587889914_m, 12.70061337_m, 18.20429215_m, 19.09754214_m,
                      17.39172749_m, 16.99931524_m, 16.29954689_m, 12.80542565_m, 10.12174192_m, 8.388157991_m};
    fWLSAbsEnergy = {1.997981846_eV, 2.027062605_eV, 2.057002412_eV, 2.085755333_eV, 2.114253037_eV, 2.142441084_eV, 2.171390915_eV,
                     2.201133835_eV, 2.229321308_eV, 2.258240077_eV, 2.286666787_eV, 2.315818293_eV, 2.343091665_eV, 2.372361386_eV,
                     2.400991064_eV, 2.43032019_eV, 2.457480388_eV, 2.486733706_eV, 2.513663605_eV, 2.542729703_eV, 2.570892934_eV,
                     2.599687023_eV, 2.627480008_eV, 2.655873678_eV, 2.684887721_eV, 2.71278016_eV, 2.741258214_eV, 2.768504811_eV,
                     2.796298478_eV, 2.824655859_eV, 2.851646616_eV, 2.881143603_eV, 2.909230049_eV, 2.937869479_eV, 2.96497279_eV,
                     2.99258084_eV, 3.020707862_eV, 3.049368628_eV, 3.076311711_eV, 3.10604253_eV, 3.134001011_eV, 3.157687135_eV,
                     3.189019663_eV, 3.213547981_eV, 3.240968652_eV, 3.271420824_eV, 3.299842395_eV, 3.326112141_eV, 3.355496222_eV,
                     3.382663197_eV};
    fWLSAbsLength = {4918.459907_mm, 5000_mm, 4918.459907_mm, 5000_mm, 5000_mm, 5000_mm, 4918.459907_mm, 4918.459907_mm, 4918.459907_mm,
                     4918.459907_mm, 4918.459907_mm, 5000_mm, 5000_mm, 4918.459907_mm, 4918.459907_mm, 5000_mm, 5000_mm, 3971.895759_mm,
                     3003.330134_mm, 1991.046281_mm, 981.8021971_mm, 1.837435671_mm, 0.80754867_mm, 0.493108677_mm, 0.40481092_mm,
                     0.411522029_mm, 0.439497656_mm, 0.425279869_mm, 0.372861786_mm, 0.337833462_mm, 0.360799676_mm, 0.411522029_mm,
                     0.454190766_mm, 0.518042333_mm, 0.571755648_mm, 0.620747254_mm, 0.696467552_mm, 0.756145256_mm, 0.921076403_mm,
                     1.121982495_mm, 1.412401738_mm, 1.930344175_mm, 2.390375027_mm, 3.161264333_mm, 3.914642483_mm, 4.690743236_mm,
                     981.8021971_mm, 1991.046281_mm, 3003.330134_mm, 3971.895759_mm};
    fWLSEmissionEnergy = {2.00_eV, 2.03_eV, 2.06_eV, 2.09_eV, 2.12_eV, 2.15_eV, 2.18_eV, 2.21_eV, 2.24_eV, 2.27_eV, 2.30_eV,
                          2.33_eV, 2.36_eV, 2.39_eV, 2.42_eV, 2.45_eV, 2.48_eV, 2.51_eV, 2.54_eV, 2.57_eV, 2.60_eV, 2.63_eV,
                          2.66_eV, 2.69_eV, 2.72_eV, 2.75_eV, 2.78_eV, 2.81_eV, 2.84_eV, 2.87_eV, 2.90_eV, 2.93_eV, 2.96_eV,
                          2.99_eV, 3.02_eV, 3.05_eV, 3.08_eV, 3.11_eV, 3.14_eV, 3.17_eV, 3.20_eV, 3.23_eV, 3.26_eV, 3.29_eV,
                          3.32_eV, 3.35_eV, 3.38_eV, 3.41_eV, 3.44_eV, 3.47_eV};
    fWLSEmissionAmplitude = {0.05, 0.10, 0.30, 0.50, 0.75, 1.00, 1.50, 1.85, 2.30, 2.75,
                             3.25, 3.80, 4.50, 5.20, 6.00, 7.00, 8.50, 9.50, 11.1, 12.4,
                             12.9, 13.0, 12.8, 12.3, 11.1, 11.0, 12.0, 11.0, 17.0, 16.9,
                             15.0, 9.00, 2.50, 1.00, 0.05, 0.00, 0.00, 0.00, 0.00, 0.00,
                             0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
}

auto PDSVeto::CalculateCategoryConfiguration() const -> std::vector<CategoryConfigurationType> {
    std::vector<double> moduleLengths;
    std::vector<double> moduleThicknesses;
    std::vector<double> moduleWidths;
    for (int categoryID{}; categoryID < ssize(*fNModuleOfACategory); ++categoryID) {
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
    auto nStripOfAModule{[this](short aModuleID) {
        auto categoryIDOfAModule{[](short aModuleID) {
            if (aModuleID == 0) { return 0; }
            if (aModuleID == 1 or aModuleID == 2) { return 1; }
            if (aModuleID == 3 or aModuleID == 4 or aModuleID == 5 or aModuleID == 6) { return 2; }
            if (aModuleID == 7 or aModuleID == 8 or aModuleID == 9 or aModuleID == 10) { return 3; }
            muc::unreachable();
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
    ImportValue(node, fFiberHoleRadius, "FiberHoleRadius");
    ImportValue(node, fFiberRadius, "FiberRadius");
    ImportValue(node, fFiberInnerRadiusRatio, "FiberInnerRadiusRatio");
    ImportValue(node, fFiberCoreRadiusRatio, "FiberCoreRadiusRatio");
    ImportValue(node, fFPRIndexEnergy, "FPRIndexEnergy");
    ImportValue(node, fFPRIndex, "FPRIndex");
    ImportValue(node, fFPAbsEnergy, "FPAbsEnergy");
    ImportValue(node, fFPAbsLength, "FPAbsLength");
    ImportValue(node, fPMMARIndexEnergy, "PMMARIndexEnergy");
    ImportValue(node, fPMMARIndex, "PMMARIndex");
    ImportValue(node, fPMMAAbsEnergy, "PMMAAbsEnergy");
    ImportValue(node, fPMMAAbsLength, "PMMAAbsLength");
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
    ExportValue(node, fFiberHoleRadius, "FiberHoleRadius");
    ExportValue(node, fFiberRadius, "FiberRadius");
    ExportValue(node, fFiberInnerRadiusRatio, "FiberInnerRadiusRatio");
    ExportValue(node, fFiberCoreRadiusRatio, "FiberCoreRadiusRatio");
    ExportValue(node, fFPRIndexEnergy, "FPRIndexEnergy");
    ExportValue(node, fFPRIndex, "FPRIndex");
    ExportValue(node, fFPAbsEnergy, "FPAbsEnergy");
    ExportValue(node, fFPAbsLength, "FPAbsLength");
    ExportValue(node, fPMMARIndexEnergy, "PMMARIndexEnergy");
    ExportValue(node, fPMMARIndex, "PMMARIndex");
    ExportValue(node, fPMMAAbsEnergy, "PMMAAbsEnergy");
    ExportValue(node, fPMMAAbsLength, "PMMAAbsLength");

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
