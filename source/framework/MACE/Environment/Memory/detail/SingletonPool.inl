namespace MACE::Environment::Memory::Detail {

template<class ASingleton> // clang-format off
    requires std::is_base_of_v<Singleton<ASingleton>, ASingleton>
std::optional<std::reference_wrapper<SingletonPool::Node>> SingletonPool::Find() const { // clang-format on
    if (const auto existed = fTypeMap.find(typeid(ASingleton));
        existed == fTypeMap.cend()) {
        return std::nullopt;
    } else {
        return *(existed->second);
    }
}

template<class ASingleton> // clang-format off
    requires std::is_base_of_v<Singleton<ASingleton>, ASingleton>
SingletonPool::Node& SingletonPool::Push(ASingleton* instance) { // clang-format on
    auto& pushed = fInstanceList.emplace_front(instance, static_cast<ISingletonBase*>(instance));
    if (not fTypeMap.emplace(typeid(ASingleton), fInstanceList.begin()).second) {
        fInstanceList.pop_front();
        throw std::logic_error(std::string("MACE::Environment::Memory::Detail::SingletonPool::Push: Instance of type ")
                                   .append(typeid(ASingleton).name())
                                   .append(" already exists"));
    }
    return pushed;
}

} // namespace MACE::Environment::Memory::Detail
