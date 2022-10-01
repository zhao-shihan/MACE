namespace MACE::Env::Memory::internal {

template<MuteSingletonized AMuteSingleton>
[[nodiscard]] std::optional<std::reference_wrapper<MuteSingletonPool::Node>> MuteSingletonPool::Find() {
    if (const auto existed = fInstanceMap.find(typeid(AMuteSingleton));
        existed == fInstanceMap.cend()) {
        return std::nullopt;
    } else {
        return existed->second;
    }
}

[[nodiscard]] MuteSingletonPool::Node& MuteSingletonPool::Insert(MuteSingletonized auto* instance) {
    if (const auto [iter, inserted] = fInstanceMap.try_emplace(typeid(decltype(*instance)), instance);
        inserted) {
        return iter->second;
    } else {
        throw std::logic_error(
            std::string("MACE::Env::Memory::internal::MuteSingletonPool::Insert: "
                        "Instance of type ")
                .append(typeid(decltype(*instance)).name())
                .append(" already exists"));
    }
}

} // namespace MACE::Env::Memory::internal
