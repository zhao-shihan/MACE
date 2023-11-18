namespace MACE::Env::Memory::internal {

template<Singletonified ASingleton>
[[nodiscard]] auto SingletonPool::Find() -> std::optional<std::reference_wrapper<SingletonPool::Node>> {
    if (const auto existed = fInstanceMap.find(typeid(ASingleton));
        existed == fInstanceMap.end()) {
        return std::nullopt;
    } else {
        return existed->second.first;
    }
}

template<Singletonified ASingleton>
[[nodiscard]] auto SingletonPool::Insert(gsl::not_null<ASingleton*> instance) -> Node& {
    if (const auto [iter, inserted] = fInstanceMap.try_emplace(
            typeid(ASingleton), instance,
            std::make_pair(fInstanceMap.size(), static_cast<SingletonBase*>(instance)));
        inserted) {
        return iter->second.first;
    } else {
        throw std::logic_error{fmt::format("MACE::Env::Memory::internal::SingletonPool::Insert: "
                                           "Instance of type {} already exists",
                                           typeid(ASingleton).name())};
    }
}

} // namespace MACE::Env::Memory::internal
