namespace MACE::Detector::Field {

inline SolenoidFieldS3::SolenoidFieldS3() :
    MagneticFieldBase<SolenoidFieldS3>{},
    fSolenoid{Description::Solenoid::Instance()} {}

} // namespace MACE::Detector::Field
