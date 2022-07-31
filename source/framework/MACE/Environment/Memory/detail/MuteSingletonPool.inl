namespace MACE::Environment::Memory::Detail {

template<Concept::MuteSingletonized AMuteSingleton>
[[nodiscard]] std::optional<std::reference_wrapper<MuteSingletonPool::Node>> MuteSingletonPool::Find() {
    if (const auto existed = fInstanceMap.find(typeid(AMuteSingleton));
        existed == fInstanceMap.cend()) {
        return std::nullopt;
    } else {
        return existed->second;
    }
}

template<Concept::MuteSingletonized AMuteSingleton>
[[nodiscard]] MuteSingletonPool::Node& MuteSingletonPool::Insert(AMuteSingleton* instance) {
    const auto [iter, inserted] = fInstanceMap.try_emplace(typeid(AMuteSingleton), instance);
    if (inserted) {
        return iter->second;
    } else {
        throw std::logic_error(std::string("MACE::Environment::Memory::Detail::MuteSingletonPool::Insert: Instance of type ")
                                   .append(typeid(AMuteSingleton).name())
                                   .append(" already exists"));
    }
}

} // namespace MACE::Environment::Memory::Detail
