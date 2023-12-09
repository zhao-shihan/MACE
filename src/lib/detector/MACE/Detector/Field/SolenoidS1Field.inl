namespace MACE::Detector::Field {

inline SolenoidS1Field::SolenoidS1Field() :
    MagneticFieldBase<SolenoidS1Field>{},
    fSolenoid{Description::Solenoid::Instance()} {}

} // namespace MACE::Detector::Field
