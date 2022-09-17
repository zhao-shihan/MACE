namespace MACE::Environment::Memory {

template<class ADerived>
ObserverPtr<ADerived> Singleton<ADerived>::fgInstance = nullptr;
template<class ADerived>
ObserverPtr<internal::SingletonPool::Node> Singleton<ADerived>::fgInstanceNode = nullptr;

template<class ADerived>
Singleton<ADerived>::Singleton() {
    static_assert(Singletonized<ADerived>);
    if (internal::SingletonPool::Instance().Contains<ADerived>()) {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::Singleton: Trying to construct ")
                .append(typeid(ADerived).name())
                .append(" (environmental singleton) twice"));
    }
}

template<class ADerived>
Singleton<ADerived>::~Singleton() {
    assert((fgInstance == nullptr and fgInstanceNode == nullptr) or
           fgInstance == *fgInstanceNode);
    if (fgInstance != nullptr) {
        fgInstance = nullptr;
        *fgInstanceNode = nullptr;
        fgInstanceNode = nullptr;
    }
}

template<class ADerived>
ADerived& Singleton<ADerived>::Instance() {
    if (fgInstance == nullptr) [[unlikely]] {
        assert(fgInstanceNode == nullptr);
        InstantiateOrFindInstance();
    }
    assert(fgInstance == *fgInstanceNode);
    return *fgInstance;
}

template<class ADerived>
void Singleton<ADerived>::InstantiateOrFindInstance() {
    if (auto& node = internal::SingletonFactory::Instance().InstantiateOrFind<ADerived>();
        node != nullptr) {
        fgInstance = static_cast<ObserverPtr<ADerived>>(node);
        fgInstanceNode = std::addressof(node);
    } else {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::Singleton::Instance(): The instance of ")
                .append(typeid(ADerived).name())
                .append(" has been deleted"));
    }
}

} // namespace MACE::Environment::Memory
