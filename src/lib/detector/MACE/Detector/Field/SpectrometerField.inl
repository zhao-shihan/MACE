namespace MACE::Detector::Field {

template<std::floating_point AFloat>
constexpr SpectrometerField<AFloat>::SpectrometerField() :
    fSpectrometerField(&Description::SpectrometerField::Instance()) {}

} // namespace MACE::Detector::Field
