namespace MACE::Data::inline Model::inline Field {

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
constexpr BasicField<T>::Named<AFieldSet, I>::Named(const T& object) :
    fObject(object) {}

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
constexpr BasicField<T>::Named<AFieldSet, I>::Named(T&& object) :
    fObject(std::move(object)) {}

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
constexpr auto BasicField<T>::Named<AFieldSet, I>::operator=(detail::VeryDifferentFrom<Named> auto&& o) & -> auto& {
    if constexpr (std::assignable_from<T&, decltype(o)>) {
        fObject = std::forward<decltype(o)>(o);
    } else if constexpr (requires { VectorAssign(fObject, std::forward<decltype(o)>(o)); }) {
        VectorAssign(fObject, std::forward<decltype(o)>(o));
    } else {
        struct {
        } failed;
        fObject = failed;
    }
    return *this;
}

template<GoodFieldValueType T>
template<typename AFieldSet, gsl::index I>
template<typename U>
constexpr auto BasicField<T>::Named<AFieldSet, I>::As() const -> std::conditional_t<std::same_as<T, U>, const T&, U> {
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
// MACE_ALWAYS_INLINE auto BasicField<T>::Named<AFieldSet, I>::CreateBranchFor(TTree& tree) -> TBranch* {
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
// MACE_ALWAYS_INLINE auto BasicField<T>::Named<AFieldSet, I>::SetAddressTo(TBranch& branch) -> std::conditional_t<std::is_class_v<T>, T*, void> {
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

} // namespace MACE::Data::inline Model::inline Field
