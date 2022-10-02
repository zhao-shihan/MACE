namespace MACE::Env::Memory::internal {

template<Singletonized ASingleton>
[[nodiscard]] std::optional<std::reference_wrapper<SingletonPool::Node>> SingletonPool::Find() {
    if (const auto existed = fInstanceMap.find(typeid(ASingleton));
        existed == fInstanceMap.end()) {
        return std::nullopt;
    } else {
        return existed->second.first;
    }
}

template<Singletonized ASingleton>
[[nodiscard]] SingletonPool::Node& SingletonPool::Insert(gsl::not_null<ASingleton*> instance) {
    if (const auto [iter, inserted] = fInstanceMap.try_emplace(
            typeid(decltype(*instance)), instance,
            std::make_pair(fInstanceMap.size(), static_cast<ISingletonBase*>(instance)));
        inserted) {
        return iter->second.first;
    } else {
        throw std::logic_error(
            std::string("MACE::Env::Memory::internal::SingletonPool::Insert: "
                        "Instance of type ")
                .append(typeid(decltype(*instance)).name())
                .append(" already exists"));
    }
}

} // namespace MACE::Env::Memory::internal
