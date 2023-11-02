namespace MACE::Data {

template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
constexpr Field<T, AName, ATitle>::Field(const T& object) :
    fObject{object} {}

template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
constexpr Field<T, AName, ATitle>::Field(T&& object) :
    fObject{std::move(object)} {}

// template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
// template<typename SF>
//     requires std::same_as<SF, typename Field<typename SF::Type>::template Item<SF::AModel>> and
//              std::constructible_from<T, const typename SF::Type&>
// constexpr Field<T, AName, ATitle>::Field(const SF& that) :
//     fObject{that} {}

// template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
// template<typename SF>
//     requires std::same_as<SF, typename Field<typename SF::Type>::template Item<SF::AModel>> and
//              std::constructible_from<T, const typename SF::Type&>
// constexpr Field<T, AName, ATitle>::Field(SF&& that) :
//     fObject{std::move(that)} {}

// template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
// constexpr Field<T, AName, ATitle>::Field(auto&& v) // clang-format off
//     requires requires { VectorCast<T>(std::forward<decltype(v)>(v)); } : // clang-format on
//     fObject{VectorCast<T>(std::forward<decltype(v)>(v))} {}

template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
template<typename U>
    requires(std::constructible_from<T, U> and not std::same_as<std::remove_cvref_t<U>, T>)
constexpr Field<T, AName, ATitle>::Field(U&& object) :
    fObject{std::forward<U>(object)} {}

template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
template<typename U>
    requires(internal::IsStdArray<T>::value and not std::constructible_from<T, U> and not std::same_as<std::remove_cvref_t<U>, T> and
             requires(U&& object) { VectorCast<T>(std::forward<U>(object)); })
constexpr Field<T, AName, ATitle>::Field(U&& object) :
    fObject{VectorCast<T>(std::forward<U>(object))} {}

template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
template<typename U>
    requires(internal::IsStdArray<T>::value and not std::constructible_from<T, U> and not std::same_as<std::remove_cvref_t<U>, T> and
             requires(T fObject, U&& object) { VectorAssign(fObject, std::forward<U>(object)); })
constexpr auto Field<T, AName, ATitle>::operator=(U&& object) -> auto& {
    VectorAssign(fObject, std::forward<U>(object));
    return *this;
}

template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
template<typename U>
constexpr auto Field<T, AName, ATitle>::As() const& -> std::conditional_t<std::same_as<T, U>, const T&, U> {
    if constexpr (std::same_as<T, U> or std::convertible_to<const T&, U>) {
        return fObject;
    } else if constexpr (requires { static_cast<U>(fObject); }) {
        return static_cast<U>(fObject);
    } else if constexpr (requires { VectorCast<U>(fObject); }) {
        return VectorCast<U>(fObject);
    } else {
        struct {
        } failed;
        return failed;
    }
}

template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
template<typename U>
constexpr auto Field<T, AName, ATitle>::As() && -> U {
    if constexpr (std::convertible_to<T, U>) {
        return std::move(fObject);
    } else if constexpr (requires { static_cast<U>(std::move(fObject)); }) {
        return static_cast<U>(std::move(fObject));
    } else if constexpr (requires { VectorCast<U>(std::move(fObject)); }) {
        return VectorCast<U>(std::move(fObject));
    } else {
        struct {
        } failed;
        return failed;
    }
}

} // namespace MACE::Data
