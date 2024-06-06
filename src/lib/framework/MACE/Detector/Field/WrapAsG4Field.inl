namespace MACE::Detector::Field {

template<ElectromagneticField AField>
auto WrapAsG4Field<AField>::GetFieldValue(const G4double* x, G4double* f) const -> void {
    std::ranges::copy(std::bit_cast<std::array<G4double, 6>>(
                          this->BEFieldAt(
                              VectorCast<muc::array3d>(x))),
                      f);
}

} // namespace MACE::Detector::Field
