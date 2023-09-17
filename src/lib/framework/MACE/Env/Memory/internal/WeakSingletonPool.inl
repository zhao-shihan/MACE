namespace MACE::Env::Memory::internal {

template<WeakSingletonified AWeakSingleton>
[[nodiscard]] std::optional<std::reference_wrapper<WeakSingletonPool::Node>> WeakSingletonPool::Find() {
    if (const auto existed = fInstanceMap.find(typeid(AWeakSingleton));
        existed == fInstanceMap.cend()) {
        return std::nullopt;
    } else {
        return existed->second;
    }
}

template<WeakSingletonified AWeakSingleton>
[[nodiscard]] WeakSingletonPool::Node& WeakSingletonPool::Insert(gsl::not_null<AWeakSingleton*> instance) {
    if (const auto [iter, inserted] = fInstanceMap.try_emplace(typeid(decltype(*instance)), instance);
        inserted) {
        return iter->second;
    } else {
        throw std::logic_error(
            std::string("MACE::Env::Memory::internal::WeakSingletonPool::Insert: "
                        "Instance of type ")
                .append(typeid(decltype(*instance)).name())
                .append(" already exists"));
    }
}

} // namespace MACE::Env::Memory::internal
