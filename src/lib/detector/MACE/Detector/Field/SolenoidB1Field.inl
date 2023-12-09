namespace MACE::Detector::Field {

inline SolenoidB1Field::SolenoidB1Field() :
    MagneticFieldBase<SolenoidB1Field>{},
    fSolenoid{Description::Solenoid::Instance()} {}

template<Concept::NumericVector3D T>
inline auto SolenoidB1Field::BFieldAt(T x) const -> T {
    const auto deltaX{x - fSolenoid.B1Center()};
    const auto alpha{fSolenoid.MagneticFluxDensity() * fSolenoid.B1Radius() / Math::Norm2(deltaX)};
    return {alpha * deltaX[2], 0, -alpha * deltaX[0]};
}

} // namespace MACE::Detector::Field
