namespace MACE::Environment::Memory {

template<class ADerived>
ObserverPtr<ADerived> FreeSingleton<ADerived>::fgInstance = nullptr;

template<class ADerived>
FreeSingleton<ADerived>::FreeSingleton() :
    FreeSingletonBase(),
    MuteSingleton<ADerived>() {
    static_assert(FreeSingletonized<ADerived>);
    fgInstance = static_cast<ObserverPtr<ADerived>>(this);
}

template<class ADerived>
FreeSingleton<ADerived>::~FreeSingleton() {
    assert((fgInstance == nullptr and MuteSingleton<ADerived>::fgInstanceNode == nullptr) or
           fgInstance == *MuteSingleton<ADerived>::fgInstanceNode);
    fgInstance = nullptr;
}

template<class ADerived>
ADerived& FreeSingleton<ADerived>::Instance() {
    if (fgInstance == nullptr) [[unlikely]] {
        assert(MuteSingleton<ADerived>::fgInstanceNode == nullptr);
        FindInstance();
    }
    assert(fgInstance == *MuteSingleton<ADerived>::fgInstanceNode);
    return *fgInstance;
}

template<class ADerived>
void FreeSingleton<ADerived>::FindInstance() {
    if (const auto optionalNode = internal::MuteSingletonPool::Instance().Find<ADerived>();
        optionalNode.has_value()) {
        if (auto& node = optionalNode->get();
            node != nullptr) {
            MuteSingleton<ADerived>::fgInstanceNode = std::addressof(node);
            fgInstance = static_cast<ObserverPtr<ADerived>>(node);
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
