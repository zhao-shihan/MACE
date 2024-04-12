namespace MACE::Detector::Field {

inline AcceleratorField::AcceleratorField() :
    ElectromagneticFieldBase<AcceleratorField>{},
    fMMSField{Description::MMSField::Instance()},
    fAccelerator{Description::Accelerator::Instance()} {}

} // namespace MACE::Detector::Field
