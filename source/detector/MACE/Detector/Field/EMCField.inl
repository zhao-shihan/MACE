namespace MACE::Detector::Field {

template<std::floating_point AFloat>
constexpr EMCField<AFloat>::EMCField() :
    fEMCField(&Description::EMCField::Instance()) {}

} // namespace MACE::Detector::Field
