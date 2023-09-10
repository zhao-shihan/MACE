#define MACE_DATA_MODEL_FIELD_DEFINE_FIELD_NAME_TITLE(TheField) \
    namespace MACE::Data::inline Model {                        \
    template<>                                                  \
    template<>                                                  \
    std::string TheField::fgName{TheField::DefaultName()};      \
    template<>                                                  \
    template<>                                                  \
    std::string TheField::fgTitle{TheField::DefaultTitle()};    \
    }

namespace MACE::Data::inline Model {

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
constexpr Field<T>::Named<AFieldSet, I>::Named(const T& object) :
    fObject{object} {}

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
constexpr Field<T>::Named<AFieldSet, I>::Named(T&& object) :
    fObject{std::move(object)} {}

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
constexpr Field<T>::Named<AFieldSet, I>::Named(auto&& v) // clang-format off
    requires requires { VectorCast<T>(std::forward<decltype(v)>(v)); } : // clang-format on
    fObject{VectorCast<T>(std::forward<decltype(v)>(v))} {}

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
constexpr auto Field<T>::Named<AFieldSet, I>::operator=(auto&& v) -> Named& // clang-format off
    requires requires(T fObject) { VectorAssign(fObject, std::forward<decltype(v)>(v)); } { // clang-format on
    VectorAssign(fObject, std::forward<decltype(v)>(v));
    return *this;
}

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
template<typename U>
constexpr auto Field<T>::Named<AFieldSet, I>::As() const -> std::conditional_t<std::same_as<T, U>, const T&, U> {
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

// template<GoodFieldValueType T>
// template<typename AFieldSet, gsl::index I>
// MACE_ALWAYS_INLINE auto Field<T>::Named<AFieldSet, I>::CreateBranchFor(TTree& tree) -> TBranch* {
//     const auto branch = [this, &tree] {
//         if constexpr (Concept::ROOTFundamental<T>) {
//             return tree.Branch(fgName.c_str(),
//                                &fObject,
//                                fmt::format("{}/{}", fgName, ROOTUtil::LeafTypeCode<T>()).c_str());
//         }
//         if constexpr (detail::IsStdArray<T>::value) {
//             return tree.Branch(fgName.c_str(),
//                                fObject.data(),
//                                fmt::format("{}[{}]/{}", fgName, fObject.size(), ROOTUtil::LeafTypeCode<typename T::value_type>()).c_str());
//         }
//         if constexpr (detail::IsFixedString<T>::value) {
//             return tree.Branch(fgName.c_str(),
//                                fObject.CString(),
//                                (fgName + "/C").c_str());
//         }
//         if constexpr (std::is_class_v<T>) {
//             return tree.Branch(fgName.c_str(), std::addressof(fObject));
//         }
//     }();
//     branch->SetTitle(fgTitle.c_str());
//     return branch;
// }

// template<GoodFieldValueType T>
// template<typename AFieldSet, gsl::index I>
// MACE_ALWAYS_INLINE auto Field<T>::Named<AFieldSet, I>::SetAddressTo(TBranch& branch) -> std::conditional_t<std::is_class_v<T>, T*, void> {
//     if constexpr (Concept::ROOTFundamental<T>) {
//         branch.SetAddress(&fObject);
//         return;
//     }
//     if constexpr (detail::IsStdArray<T>::value) {
//         branch.SetAddress(fObject.data());
//         return;
//     }
//     if constexpr (detail::IsFixedString<T>::value) {
//         branch.SetAddress(fObject.CString());
//         return;
//     }
//     if constexpr (std::is_class_v<T>) {
//         auto pObject = std::addressof(fObject);
//         branch.SetAddress(&pObject);
//         return pObject;
//     }
// }

} // namespace MACE::Data::inline Model
