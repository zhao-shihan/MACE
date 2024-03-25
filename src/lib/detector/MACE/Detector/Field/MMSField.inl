namespace MACE::Detector::Field {

inline MMSField::MMSField() :
    MagneticFieldBase<MMSField>{},
    fMMSField{Description::MMSField::Instance()} {}

} // namespace MACE::Detector::Field
