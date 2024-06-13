namespace MACE::Detector::Field {

constexpr UniformMagneticField::UniformMagneticField(double bx, double by, double bz) :
    MagneticFieldBase<UniformMagneticField>{},
    fBx{bx},
    fBy{by},
    fBz{bz} {}

} // namespace MACE::Detector::Field
