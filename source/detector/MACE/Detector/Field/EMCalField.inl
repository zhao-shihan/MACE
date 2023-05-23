namespace MACE::Detector::Field {

template<std::floating_point AFloat>
constexpr EMCalField<AFloat>::EMCalField() :
    fEMCalField(&Description::EMCalField::Instance()) {}

} // namespace MACE::Detector::Field
