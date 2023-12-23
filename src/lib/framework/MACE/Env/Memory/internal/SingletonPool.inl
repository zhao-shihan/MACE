namespace MACE::Env::Memory::internal {

template<Singletonified ASingleton>
[[nodiscard]] auto SingletonPool::Find() -> std::optional<std::reference_wrapper<void*>> {
    if (const auto existed{fInstanceMap.find(typeid(ASingleton))};
        existed == fInstanceMap.end()) {
        return std::nullopt;
    } else {
        return get<0>(existed->second);
    }
}

template<Singletonified ASingleton>
[[nodiscard]] auto SingletonPool::Insert(gsl::not_null<ASingleton*> instance) -> void*& {
    if (const auto [iter, inserted]{fInstanceMap.try_emplace(
            typeid(ASingleton), std::tuple{instance,
                                           fInstanceMap.size(),
                                           static_cast<SingletonBase*>(instance)})};
        inserted) {
        return get<0>(iter->second);
    } else {
        throw std::logic_error{fmt::format("MACE::Env::Memory::internal::SingletonPool::Insert: "
                                           "Instance of type {} already exists",
                                           typeid(ASingleton).name())};
    }
}

} // namespace MACE::Env::Memory::internal
