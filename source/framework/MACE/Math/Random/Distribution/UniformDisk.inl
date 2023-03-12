namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
constexpr BasicUniformDiskParameter<T, AUniformDisk>::BasicUniformDiskParameter() :
    BasicUniformDiskParameter(1) {}

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
constexpr BasicUniformDiskParameter<T, AUniformDisk>::BasicUniformDiskParameter(VOfT r, VOfT x0, VOfT y0) :
    Base(),
    fRadius(r),
    fCenterX(x0),
    fCenterY(y0) {}

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
constexpr BasicUniformDiskParameter<T, AUniformDisk>::BasicUniformDiskParameter(VOfT radius, const T& center) :
    Base(),
    fRadius(radius),
    fCenterX(center[0]),
    fCenterY(center[1]) {}

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
constexpr BasicUniformDiskParameter<T, AUniformDisk>::BasicUniformDiskParameter(VOfT radius) :
    Base(),
    fRadius(radius),
    fCenterX(0),
    fCenterY(0) {}

template<std::floating_point T, template<typename> class AUniformDisk, Concept::Character AChar>
auto operator<<(std::basic_ostream<AChar>& os, const BasicUniformDiskParameter<T, AUniformDisk>& self) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
    return os << self.fRadius << ' ' << self.fCenter[0] << ' ' << self.fCenter[1] << std::setprecision(oldPrecision);
}

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
constexpr UniformDiskBase<T, AUniformDisk>::UniformDiskBase(VOfT r, VOfT x0, VOfT y0) :
    Base(),
    fParameter(r, x0, y0) {}

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
constexpr UniformDiskBase<T, AUniformDisk>::UniformDiskBase(VOfT radius, const T& center) :
    Base(),
    fParameter(radius, center) {}

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
constexpr UniformDiskBase<T, AUniformDisk>::UniformDiskBase(VOfT radius) :
    Base(),
    fParameter(radius) {}

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
constexpr UniformDiskBase<T, AUniformDisk>::UniformDiskBase(const typename Base::ParameterType& p) :
    Base(),
    fParameter(p) {}

} // namespace internal

#define MACE_MATH_RANDOM_DISTRIBUTION_UNIFORM_DISK_GENERATOR(rejection) \
    T r;                                                                \
    ValueTypeOf<T> r2;                                                  \
    do {                                                                \
        r = UniformCompactRectangle<T>({-0.5, 0.5}, {-0.5, 0.5})(g);    \
        r2 = Math::Hypot2(r[0], r[1]);                                  \
        std2b::assume(0 <= r2 and r2 <= 0.5);                           \
    } while (rejection);                                                \
    if constexpr (Concept::MathVector2Any<T>) {                         \
        r *= 2 * p.Radius();                                            \
        r += p.Center();                                                \
    } else {                                                            \
        r[0] = 2 * p.Radius() * r[0] + p.Center()[0];                   \
        r[1] = 2 * p.Radius() * r[1] + p.Center()[1];                   \
    }                                                                   \
    return r;

template<Concept::NumericVector2Any T>
constexpr T UniformCompactDisk<T>::operator()(UniformRandomBitGenerator auto& g, const UniformCompactDiskParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_UNIFORM_DISK_GENERATOR(r2 > 0.25)
}

template<Concept::NumericVector2Any T>
constexpr T UniformDisk<T>::operator()(UniformRandomBitGenerator auto& g, const UniformDiskParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_UNIFORM_DISK_GENERATOR(r2 >= 0.25)
}

#undef MACE_MATH_RANDOM_DISTRIBUTION_UNIFORM_DISK_GENERATOR

} // namespace MACE::Math::Random::Distribution
