namespace MACE::Environment::Memory {

template<class ADerived>
ObserverPtr<Detail::FreeSingletonPool::Node> FreeSingleton<ADerived>::fgInstanceNode = nullptr;

template<class ADerived>
FreeSingleton<ADerived>::FreeSingleton() :
    NonCopyableBase() {
    static_assert(Concept::FreeSingletonized<ADerived>);
    if (not Detail::FreeSingletonPool::Instance().Contains<ADerived>()) {
        fgInstanceNode = std::addressof(Detail::FreeSingletonPool::Instance().Insert(static_cast<ADerived*>(this)));
    } else {
        throw std::logic_error(std::string("MACE::Environment::Memory::FreeSingleton::FreeSingleton(): Trying to construct ")
                                   .append(typeid(ADerived).name())
                                   .append(" (free singleton in environment) twice"));
    }
}

template<class ADerived>
FreeSingleton<ADerived>::~FreeSingleton() {
    if (fgInstanceNode != nullptr) {
        *fgInstanceNode = nullptr;
        fgInstanceNode = nullptr;
    }
}

template<class ADerived>
ADerived& FreeSingleton<ADerived>::Instance() {
    if (fgInstanceNode == nullptr) [[unlikely]] {
        FindInstance();
    }
    return *static_cast<ObserverPtr<ADerived>>(*fgInstanceNode);
}

template<class ADerived>
void FreeSingleton<ADerived>::FindInstance() {
    if (const auto optionalNode = Detail::FreeSingletonPool::Instance().Find<ADerived>();
        optionalNode.has_value()) {
        if (optionalNode.value() != nullptr) {
            fgInstanceNode = std::addressof(optionalNode.value().get());
        } else {
            throw std::logic_error(
                std::string("MACE::Environment::Memory::FreeSingleton::Instance(): The instance of ")
                    .append(typeid(ADerived).name())
                    .append(" (free singleton in environment) has been deleted"));
        }
    } else {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::FreeSingleton::Instance(): ")
                .append(typeid(ADerived).name())
                .append(" (free singleton in environment) has not been instantiated"));
    }
}

} // namespace MACE::Environment::Memory
