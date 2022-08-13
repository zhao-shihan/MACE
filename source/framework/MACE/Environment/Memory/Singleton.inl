namespace MACE::Environment::Memory {

template<class ADerived>
ObserverPtr<Internal::SingletonPool::Node> Singleton<ADerived>::fgInstanceNode = nullptr;

template<class ADerived>
Singleton<ADerived>::Singleton() {
    static_assert(Concept::Singletonized<ADerived>);
    if (Internal::SingletonPool::Instance().Contains<ADerived>()) {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::Singleton: Trying to construct ")
                .append(typeid(ADerived).name())
                .append(" (environmental singleton) twice"));
    }
}

template<class ADerived>
Singleton<ADerived>::~Singleton() {
    if (fgInstanceNode != nullptr) {
        *fgInstanceNode = nullptr;
        fgInstanceNode = nullptr;
    }
}

template<class ADerived>
ADerived& Singleton<ADerived>::Instance() {
    if (fgInstanceNode == nullptr) [[unlikely]] {
        InstantiateOrFindInstance();
    }
    return *static_cast<ObserverPtr<ADerived>>(*fgInstanceNode);
}

template<class ADerived>
void Singleton<ADerived>::InstantiateOrFindInstance() {
    if (auto& node = Internal::SingletonFactory::Instance().InstantiateOrFind<ADerived>();
        node != nullptr) {
        fgInstanceNode = std::addressof(node);
    } else {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::Singleton::Instance(): The instance of ")
                .append(typeid(ADerived).name())
                .append(" has been deleted"));
    }
}

} // namespace MACE::Environment::Memory
