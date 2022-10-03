namespace MACE::CLHEPX::Vector {

namespace internal {

template class ForbiddenLore<&CLHEP::Hep3Vector::data>;

constexpr double (&ForbiddenGet(CLHEP::Hep3Vector&))[3];
constexpr const double (&ForbiddenGet(const CLHEP::Hep3Vector&))[3];

} // namespace internal

namespace Hep3VectorData {

static_assert(std::is_standard_layout_v<CLHEP::Hep3Vector>);
static_assert(sizeof(CLHEP::Hep3Vector) == 3 * sizeof(double));
static_assert(alignof(CLHEP::Hep3Vector) == alignof(double));

#ifdef __cpp_lib_is_layout_compatible

namespace internal {

class Hep3VectorImitator {
    double data[3];
};

static_assert(std::is_standard_layout_v<internal::Hep3VectorImitator>);
static_assert(sizeof(internal::Hep3VectorImitator) == 3 * sizeof(double));
static_assert(alignof(internal::Hep3VectorImitator) == alignof(double));
static_assert(std::is_layout_compatible_v<CLHEP::Hep3Vector, internal::Hep3VectorImitator>);

} // namespace internal

#endif

constexpr double* operator&(CLHEP::Hep3Vector& vector) noexcept {
    return Vector::internal::ForbiddenGet(vector);
}

constexpr const double* operator&(const CLHEP::Hep3Vector& vector) noexcept {
    return Vector::internal::ForbiddenGet(vector);
}

} // namespace Hep3VectorData

} // namespace MACE::CLHEPX::Vector
