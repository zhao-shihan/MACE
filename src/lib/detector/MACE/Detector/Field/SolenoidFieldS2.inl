namespace MACE::Detector::Field {

inline SolenoidFieldS2::SolenoidFieldS2() :
    MagneticFieldBase<SolenoidFieldS2>{},
    fSolenoid{Description::Solenoid::Instance()} {}

} // namespace MACE::Detector::Field
