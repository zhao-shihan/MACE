namespace MACE::Detector::Field {

inline SolenoidB2Field::SolenoidB2Field() :
    MagneticFieldBase<SolenoidB2Field>{},
    fSolenoid{Description::Solenoid::Instance()} {}

template<Concept::NumericVector3D T>
inline auto SolenoidB2Field::BFieldAt(T x) const -> T {
    const auto deltaX{x - fSolenoid.B2Center()};
    const auto alpha{fSolenoid.MagneticFluxDensity() * fSolenoid.B2Radius() / Math::Norm2(deltaX)};
    return {-alpha * deltaX[2], 0, alpha * deltaX[0]};
}

} // namespace MACE::Detector::Field
