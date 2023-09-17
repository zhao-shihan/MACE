namespace MACE::Detector::Field {

template<ElectromagneticField<G4double> AField>
void WrapAsG4Field<AField>::GetFieldValue(const G4double* x, G4double* f) const {
    std::ranges::copy(std::bit_cast<std::array<G4double, 6>>(this->BEFieldAt(VectorCast<stdx::array3d>(x))), f);
}

} // namespace MACE::Detector::Field
