namespace MACE::Environment::Memory::Detail {

template<Concept::Singletonized ASingleton>
[[nodiscard]] std::optional<std::reference_wrapper<SingletonPool::Node>> SingletonPool::Find() {
    if (const auto existed = std::as_const(fTypeMap).find(typeid(ASingleton));
        existed == fTypeMap.cend()) {
        return std::nullopt;
    } else {
        return *(existed->second);
    }
}

template<Concept::Singletonized ASingleton>
[[nodiscard]] SingletonPool::Node& SingletonPool::Insert(ASingleton* instance) {
    auto& node = fInstanceList.emplace_front(instance, static_cast<ISingletonBase*>(instance));
    if (fTypeMap.try_emplace(typeid(ASingleton), fInstanceList.begin()).second) {
        return node;
    } else {
        fInstanceList.pop_front();
        throw std::logic_error(std::string("MACE::Environment::Memory::Detail::SingletonPool::Insert: Instance of type ")
                                   .append(typeid(ASingleton).name())
                                   .append(" already exists"));
    }
}

} // namespace MACE::Environment::Memory::Detail
