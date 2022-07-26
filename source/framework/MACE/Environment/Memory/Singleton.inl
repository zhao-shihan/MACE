namespace MACE::Environment::Memory {

template<class ADerived>
ObserverPtr<Detail::SingletonPool::Node> Singleton<ADerived>::fgInstanceNode = nullptr;

template<class ADerived>
Singleton<ADerived>::Singleton() {
    static_assert(Concept::Singletonized<ADerived>);
    if (Detail::SingletonFactory::Instance().Instantiated<ADerived>()) {
        throw std::logic_error(std::string("MACE::Environment::Memory::Singleton: Trying to construct ")
                                   .append(typeid(ADerived).name())
                                   .append(" (environmental singleton) twice"));
    }
}

template<class ADerived>
Singleton<ADerived>::~Singleton() {
    if (fgInstanceNode != nullptr) {
        *fgInstanceNode = {nullptr, nullptr};
        fgInstanceNode = nullptr;
    }
}

template<class ADerived>
ADerived& Singleton<ADerived>::Instance() {
    if (fgInstanceNode == nullptr) [[unlikely]] {
        InstantiateOrFindInstance();
    }
    return *static_cast<ObserverPtr<ADerived>>(fgInstanceNode->first);
}

template<class ADerived>
void Singleton<ADerived>::InstantiateOrFindInstance() {
    fgInstanceNode = std::addressof(Detail::SingletonFactory::Instance().InstantiateOrFind<ADerived>());
    if (fgInstanceNode->first == nullptr and fgInstanceNode->second == nullptr) {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::Singleton::Instance(): The instance of ")
                .append(typeid(ADerived).name())
                .append(" has been deleted"));
    } else if (fgInstanceNode->first == nullptr or fgInstanceNode->second == nullptr) {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::Singleton::Instance(): The instance node of ")
                .append(typeid(ADerived).name())
                .append(" is corrupted (partially null)"));
    }
}

} // namespace MACE::Environment::Memory
