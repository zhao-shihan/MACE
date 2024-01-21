namespace MACE::Env::Memory::internal {

template<Singletonified ASingleton>
[[nodiscard]] auto SingletonPool::Find() -> std::shared_ptr<void*> {
    if (const auto existed{fInstanceMap.find(typeid(ASingleton))};
        existed == fInstanceMap.end()) {
        return {};
    } else {
        return get<0>(existed->second);
    }
}

template<Singletonified ASingleton>
[[nodiscard]] auto SingletonPool::Insert(gsl::not_null<ASingleton*> instance) -> std::shared_ptr<void*> {
    if (const auto [iter, inserted]{fInstanceMap.try_emplace(
            typeid(ASingleton), std::tuple{std::make_shared<void*>(instance),
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
