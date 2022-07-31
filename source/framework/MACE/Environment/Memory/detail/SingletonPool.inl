namespace MACE::Environment::Memory::Detail {

template<Concept::Singletonized ASingleton>
[[nodiscard]] std::optional<std::reference_wrapper<SingletonPool::Node>> SingletonPool::Find() {
    if (const auto existed = fInstanceMap.find(typeid(ASingleton));
        existed == fInstanceMap.end()) {
        return std::nullopt;
    } else {
        return existed->second.first;
    }
}

template<Concept::Singletonized ASingleton>
[[nodiscard]] SingletonPool::Node& SingletonPool::Insert(ASingleton* instance) {
    const auto [iter, inserted] = fInstanceMap.try_emplace(
        typeid(ASingleton), instance, std::make_pair(fInstanceMap.size(), static_cast<ISingletonBase*>(instance)));
    if (inserted) {
        return iter->second.first;
    } else {
        throw std::logic_error(std::string("MACE::Environment::Memory::Detail::SingletonPool::Insert: Instance of type ")
                                   .append(typeid(ASingleton).name())
                                   .append(" already exists"));
    }
}

} // namespace MACE::Environment::Memory::Detail
