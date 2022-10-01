namespace MACE::Env::Memory {

template<class ADerived>
typename Singleton<ADerived>::InstanceKeeper Singleton<ADerived>::fgInstance = {nullptr, nullptr};

template<class ADerived>
Singleton<ADerived>::Singleton() {
    static_assert(Singletonized<ADerived>);
    if (internal::SingletonPool::Instance().Contains<ADerived>()) {
        throw std::logic_error(
            std::string("MACE::Env::Memory::Singleton: Trying to construct ")
                .append(typeid(ADerived).name())
                .append(" (environmental singleton) twice"));
    }
}

template<class ADerived>
Singleton<ADerived>::~Singleton() {
    assert((fgInstance.object == nullptr and fgInstance.node == nullptr) or
           fgInstance.object == *fgInstance.node);
    if (fgInstance.object != nullptr) {
        fgInstance.object = nullptr;
        *fgInstance.node = nullptr;
        fgInstance.node = nullptr;
    }
}

template<class ADerived>
ADerived& Singleton<ADerived>::Instance() {
    if (fgInstance.object == nullptr) [[unlikely]] {
        assert(fgInstance.node == nullptr);
        InstantiateOrFindInstance();
    }
    assert(fgInstance.object == *fgInstance.node);
    return *fgInstance.object;
}

template<class ADerived>
void Singleton<ADerived>::InstantiateOrFindInstance() {
    if (auto& node = internal::SingletonFactory::Instance().InstantiateOrFind<ADerived>();
        node != nullptr) {
        fgInstance.object = static_cast<ObserverPtr<ADerived>>(node);
        fgInstance.node = std::addressof(node);
    } else {
        throw std::logic_error(
            std::string("MACE::Env::Memory::Singleton::Instance(): The instance of ")
                .append(typeid(ADerived).name())
                .append(" has been deleted"));
    }
}

} // namespace MACE::Env::Memory
