namespace MACE::Detector::Field {

template<std::floating_point AFloat>
constexpr SolenoidS1Field<AFloat>::SolenoidS1Field() :
    fSolenoid(&Description::Solenoid::Instance()) {}

} // namespace MACE::Detector::Field
