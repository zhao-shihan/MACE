namespace MACE::Detector::Field {

inline SpectrometerField::SpectrometerField() :
    MagneticFieldBase<SpectrometerField>{},
    fSpectrometerField{Description::SpectrometerField::Instance()} {}

} // namespace MACE::Detector::Field
