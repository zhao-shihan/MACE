namespace MACE::inline Extension::CLHEPX::Vector {

namespace internal {

template class ForbiddenLore<&CLHEP::Hep2Vector::dx>;

constexpr double& ForbiddenGet(CLHEP::Hep2Vector&);
constexpr const double& ForbiddenGet(const CLHEP::Hep2Vector&);

} // namespace internal

namespace Hep2VectorData {

static_assert(std::is_standard_layout_v<CLHEP::Hep2Vector>);
static_assert(sizeof(CLHEP::Hep2Vector) == 2 * sizeof(double));
static_assert(alignof(CLHEP::Hep2Vector) == alignof(double));

#ifdef __cpp_lib_is_layout_compatible

namespace internal {

class Hep2VectorImitator {
    double dx;
    double dy;
};

static_assert(std::is_standard_layout_v<Hep2VectorImitator>);
static_assert(sizeof(Hep2VectorImitator) == 2 * sizeof(double));
static_assert(alignof(Hep2VectorImitator) == alignof(double));
static_assert(std::is_layout_compatible_v<CLHEP::Hep2Vector, Hep2VectorImitator>);

} // namespace internal

#endif

constexpr double* operator&(CLHEP::Hep2Vector& vector) noexcept {
    return std::launder(&Vector::internal::ForbiddenGet(vector));
}

constexpr const double* operator&(const CLHEP::Hep2Vector& vector) noexcept {
    return std::launder(&Vector::internal::ForbiddenGet(vector));
}

} // namespace Hep2VectorData

} // namespace MACE::inline Extension::CLHEPX::Vector
