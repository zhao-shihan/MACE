namespace MACE::Env::Memory::internal {

template<WeakSingletonified AWeakSingleton>
[[nodiscard]] auto WeakSingletonPool::Find() -> std::shared_ptr<void*> {
    if (const auto existed = fInstanceMap.find(typeid(AWeakSingleton));
        existed == fInstanceMap.cend()) {
        return {};
    } else {
        return existed->second;
    }
}

template<WeakSingletonified AWeakSingleton>
[[nodiscard]] auto WeakSingletonPool::Insert(gsl::not_null<AWeakSingleton*> instance) -> std::shared_ptr<void*> {
    if (const auto [iter, inserted]{fInstanceMap.try_emplace(typeid(AWeakSingleton), std::make_shared<void*>(instance))};
        inserted) {
        return iter->second;
    } else {
        throw std::logic_error{fmt::format("MACE::Env::Memory::internal::WeakSingletonPool::Insert: "
                                           "Instance of type {} already exists",
                                           typeid(AWeakSingleton).name())};
    }
}

} // namespace MACE::Env::Memory::internal
