namespace MACE::Detector::Field {

inline SolenoidFieldB2::SolenoidFieldB2() :
    MagneticFieldBase<SolenoidFieldB2>{},
    fSolenoid{Description::Solenoid::Instance()} {}

template<Concept::NumericVector3D T>
inline auto SolenoidFieldB2::BFieldAt(T x) const -> T {
    const auto deltaX{x - fSolenoid.B2Center()};
    const auto alpha{fSolenoid.MagneticFluxDensity() * fSolenoid.B2Radius() / Math::Norm2(deltaX)};
    return {-alpha * deltaX[2], 0, alpha * deltaX[0]};
}

} // namespace MACE::Detector::Field
