namespace MACE::Data::inline Model {

template<typename AConcreteFieldSet, Concept::InstantiatedFrom<Field>... AFields>
constexpr FieldSet<AConcreteFieldSet, AFields...>::Entry::~Entry() = default;

} // namespace MACE::Data::inline Model
