namespace MACE::DataModel {

namespace internal {

template<class E,
         class AData, gsl::index BranchIndex,
         typename T, class ABranchSocket,
         typename U>
concept EntryConcept =
    requires(E& e, const E& ce, const U v, TTree& tree) {
        requires BranchSocketable2<ABranchSocket, T>;
        typename E::Base;
        typename E::BranchSocket;
        { ce.Value() } -> std::same_as<const U&>;
        { e.Value(v) } -> std::same_as<void>;
        { E::Name() } -> std::same_as<const std::string&>;
        { ce.FillBranchSocket() } -> std::same_as<void>;
        { E::CreateBranch(tree) } -> std::same_as<void>;
        { E::ConnectToBranch(tree) } -> std::same_as<void>;
        requires std::semiregular<E>;
        requires std::is_trivially_copyable_v<E>;
        requires std::derived_from<E, EntryBase<E, AData, BranchIndex, T, ABranchSocket, U>>;
        requires std::is_final_v<E>;
        requires not std::is_polymorphic_v<E>;
    };

} // namespace internal

template<class ADerived,
         class AData, gsl::index BranchIndex,
         typename T, BranchSocketable2<T> ABranchSocket,
         typename U>
EntryBase<ADerived, AData, BranchIndex, T, ABranchSocket, U>::EntryBase(U value) :
    fValue(std::move(value)) {
    static_assert(internal::EntryConcept<ADerived, AData, BranchIndex, T, ABranchSocket, U>);
}

} // namespace MACE::DataModel
