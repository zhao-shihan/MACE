namespace MACE::Env::Memory {

template<typename ADerived>
typename Singleton<ADerived>::InstanceKeeper Singleton<ADerived>::fgInstance = {nullptr, nullptr};

template<typename ADerived>
Singleton<ADerived>::Singleton() :
    SingletonBase{} {
    static_assert(Singletonified<ADerived>);
    if (internal::SingletonPool::Instance().Contains<ADerived>()) {
        throw std::logic_error{fmt::format("MACE::Env::Memory::Singleton: "
                                           "Trying to construct {} (environmental singleton) twice",
                                           typeid(ADerived).name())};
    }
}

template<typename ADerived>
Singleton<ADerived>::~Singleton() {
    assert((fgInstance.object == nullptr and fgInstance.node == nullptr) or
           fgInstance.object == *fgInstance.node);
    if (fgInstance.object != nullptr) {
        fgInstance.object = nullptr;
        *fgInstance.node = nullptr;
        fgInstance.node = nullptr;
    }
}

template<typename ADerived>
auto Singleton<ADerived>::Instance() -> ADerived& {
    if (fgInstance.object == nullptr) [[unlikely]] {
        assert(fgInstance.node == nullptr);
        InstantiateOrFindInstance();
    }
    assert(fgInstance.object == *fgInstance.node);
    return *fgInstance.object;
}

template<typename ADerived>
auto Singleton<ADerived>::InstantiateOrFindInstance() -> void {
    if (auto& node = internal::SingletonFactory::Instance().InstantiateOrFind<ADerived>();
        node != nullptr) {
        fgInstance.object = static_cast<ADerived*>(node);
        fgInstance.node = std::addressof(node);
    } else {
        throw std::logic_error{fmt::format("MACE::Env::Memory::Singleton::Instance(): "
                                           "The instance of {} has been deleted",
                                           typeid(ADerived).name())};
    }
}

} // namespace MACE::Env::Memory
