namespace MACE::Detector::Field {

template<std::floating_point AFloat>
constexpr SolenoidS3Field<AFloat>::SolenoidS3Field() :
    fSolenoid(&Description::Solenoid::Instance()) {}

} // namespace MACE::Detector::Field
