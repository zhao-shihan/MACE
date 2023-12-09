namespace MACE::Detector::Field {

inline SolenoidS3Field::SolenoidS3Field() :
    MagneticFieldBase<SolenoidS3Field>{},
    fSolenoid{Description::Solenoid::Instance()} {}

} // namespace MACE::Detector::Field
