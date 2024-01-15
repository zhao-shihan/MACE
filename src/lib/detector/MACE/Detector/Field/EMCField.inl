namespace MACE::Detector::Field {

inline EMCField::EMCField() :
    MagneticFieldBase<EMCField>{},
    fEMCField{Description::EMCField::Instance()} {}

} // namespace MACE::Detector::Field
