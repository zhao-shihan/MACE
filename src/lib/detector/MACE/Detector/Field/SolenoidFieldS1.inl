namespace MACE::Detector::Field {

inline SolenoidFieldS1::SolenoidFieldS1() :
    MagneticFieldBase<SolenoidFieldS1>{},
    fSolenoid{Description::Solenoid::Instance()} {}

} // namespace MACE::Detector::Field
