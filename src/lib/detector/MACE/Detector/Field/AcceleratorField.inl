namespace MACE::Detector::Field {

inline AcceleratorField::AcceleratorField() :
    ElectromagneticFieldBase<AcceleratorField>{},
    fSpectrometerField{Description::SpectrometerField::Instance()},
    fAcceleratorField{Description::AcceleratorField::Instance()} {}

} // namespace MACE::Detector::Field
