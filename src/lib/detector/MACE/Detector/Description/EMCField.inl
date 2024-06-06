namespace MACE::Detector::Description {

MACE_ALWAYS_INLINE auto EMCField::Center() const -> muc::array3d {
    const auto& solenoid{Solenoid::Instance()};
    return solenoid.S3Center() + muc::array3d{0, 0, (solenoid.S3Length() + fLength) / 2};
}

} // namespace MACE::Detector::Description
