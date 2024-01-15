namespace MACE::Detector::Field {

inline SolenoidS2Field::SolenoidS2Field() :
    MagneticFieldBase<SolenoidS2Field>{},
    fSolenoid{Description::Solenoid::Instance()} {}

} // namespace MACE::Detector::Field
