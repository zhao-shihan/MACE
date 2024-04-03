namespace MACE::Detector::Field {

inline AcceleratorField::AcceleratorField() :
    ElectromagneticFieldBase<AcceleratorField>{},
    fMMSField{Description::MMSField::Instance()},
    fAcceleratorField{Description::AcceleratorField::Instance()} {}

} // namespace MACE::Detector::Field
