namespace MACE::Detector::Field {

template<std::floating_point AFloat>
constexpr SolenoidB2Field<AFloat>::SolenoidB2Field() :
    MagneticFieldBase<SolenoidB2Field<AFloat>, AFloat>(),
    fSolenoid(&Description::Solenoid::Instance()),
    fX0(fSolenoid->B2Transform().dx()),
    fZ0(fSolenoid->B2Transform().dz()),
    fR0(fSolenoid->B2Radius()) {}

template<std::floating_point AFloat>
template<Concept::NumericVector3<AFloat> T>
constexpr T SolenoidB2Field<AFloat>::BFieldAt(const T& x) const {
    const auto deltaX = x[0] - fX0;
    const auto deltaZ = x[2] - fZ0;
    const auto alpha = fSolenoid->MagneticFluxDensity() * fR0 / Math::Hypot2(deltaX, deltaZ);
    return {-alpha * deltaZ,
            0,
            alpha * deltaX};
}

} // namespace MACE::Detector::Field
