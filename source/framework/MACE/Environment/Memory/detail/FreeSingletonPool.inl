namespace MACE::Environment::Memory::Detail {

template<Concept::FreeSingletonized AFreeSingleton>
[[nodiscard]] std::optional<std::reference_wrapper<FreeSingletonPool::Node>> FreeSingletonPool::Find() {
    if (const auto existed = fInstanceMap.find(typeid(AFreeSingleton));
        existed == fInstanceMap.cend()) {
        return std::nullopt;
    } else {
        return existed->second;
    }
}

template<Concept::FreeSingletonized AFreeSingleton>
[[nodiscard]] FreeSingletonPool::Node& FreeSingletonPool::Insert(AFreeSingleton* instance) {
    const auto [iter, inserted] = fInstanceMap.try_emplace(typeid(AFreeSingleton), instance);
    if (inserted) {
        return iter->second;
    } else {
        throw std::logic_error(std::string("MACE::Environment::Memory::Detail::FreeSingletonPool::Insert: Instance of type ")
                                   .append(typeid(AFreeSingleton).name())
                                   .append(" already exists"));
    }
}

} // namespace MACE::Environment::Memory::Detail
