namespace MACE::Detector::Field {

template<std::floating_point AFloat>
constexpr SolenoidS2Field<AFloat>::SolenoidS2Field() :
    fSolenoid(&Description::Solenoid::Instance()) {}

} // namespace MACE::Detector::Field
