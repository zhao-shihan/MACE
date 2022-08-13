namespace MACE::Environment::Memory {

template<class ADerived>
FreeSingleton<ADerived>::FreeSingleton() :
    FreeSingletonBase(),
    MuteSingleton<ADerived>() {
    static_assert(Concept::FreeSingletonized<ADerived>);
}

template<class ADerived>
ADerived& FreeSingleton<ADerived>::Instance() {
    if (MuteSingleton<ADerived>::fgInstanceNode == nullptr) [[unlikely]] {
        FindInstance();
    }
    return *static_cast<ObserverPtr<ADerived>>(*MuteSingleton<ADerived>::fgInstanceNode);
}

template<class ADerived>
void FreeSingleton<ADerived>::FindInstance() {
    if (const auto optionalNode = Internal::MuteSingletonPool::Instance().Find<ADerived>();
        optionalNode.has_value()) {
        if (optionalNode.value() != nullptr) {
            MuteSingleton<ADerived>::fgInstanceNode = std::addressof(optionalNode.value().get());
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
