namespace MACE::DataModel::inline Column {

namespace internal {

template<class C,
         class AData, gsl::index AUniqueID,
         typename T, class ABranchSocket,
         typename U>
concept ColumnConcept =
    requires(C& c, const C& cc, const U v, TTree& tree) {
        requires BranchSocket2<ABranchSocket, T>;
        typename C::Base;
        typename C::BranchSocket;
        { cc.Value() } -> std::same_as<const U&>;
        { c.Value(v) } -> std::same_as<void>;
        { C::Name() } -> std::same_as<const std::string&>;
        { cc.FillBranchSocket() } -> std::same_as<void>;
        { C::CreateBranch(tree) } -> std::same_as<void>;
        { C::ConnectToBranch(tree) } -> std::same_as<void>;
        requires std::semiregular<C>;
        requires(std::is_trivially_copyable_v<C> == std::is_trivially_copyable_v<U>);
        requires std::derived_from<C, ColumnBase<C, AData, AUniqueID, T, ABranchSocket, U>>;
        requires std::is_final_v<C>;
        requires not std::is_polymorphic_v<C>;
    };

} // namespace internal

template<class ADerived,
         class AData, gsl::index AUniqueID,
         typename T, BranchSocket2<T> ABranchSocket,
         typename U>
    requires(AUniqueID >= 0)
constexpr ColumnBase<ADerived, AData, AUniqueID, T, ABranchSocket, U>::ColumnBase() {
    static_assert(internal::ColumnConcept<ADerived, AData, AUniqueID, T, ABranchSocket, U>);
}

} // namespace MACE::DataModel::inline Column
