namespace MACE::Data::inline Model {

template<typename ADerived, Concept::InstantiatedFrom<Field>... AFields>
constexpr FieldSet<ADerived, AFields...>::Entry::~Entry() = default;

} // namespace MACE::Data::inline Model
