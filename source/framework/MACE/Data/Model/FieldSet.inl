namespace MACE::Data::inline Model {

template<typename AFieldSet, Concept::InstantiatedFrom<BasicField>... AFields>
constexpr FieldSet<AFieldSet, AFields...>::Entry::~Entry() = default;

} // namespace MACE::DataModel
