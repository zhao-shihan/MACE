namespace MACE::Detector::Field {

template<std::floating_point AFloat>
constexpr AcceleratorField<AFloat>::AcceleratorField() :
    fSpectrometerField(&Description::SpectrometerField::Instance()),
    fAcceleratorField(&Description::AcceleratorField::Instance()) {}

} // namespace MACE::Detector::Field
