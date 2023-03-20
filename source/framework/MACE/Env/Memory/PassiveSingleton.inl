namespace MACE::Env::Memory {

template<class ADerived>
ADerived* PassiveSingleton<ADerived>::fgInstance = nullptr;

template<class ADerived>
PassiveSingleton<ADerived>::PassiveSingleton() :
    PassiveSingletonBase(),
    MuteSingleton<ADerived>() {
    static_assert(PassiveSingletonized<ADerived>);
    fgInstance = static_cast<ADerived*>(this);
}

template<class ADerived>
PassiveSingleton<ADerived>::~PassiveSingleton() {
    assert((fgInstance == nullptr and MuteSingleton<ADerived>::fgInstanceNode == nullptr) or
           fgInstance == *MuteSingleton<ADerived>::fgInstanceNode);
    fgInstance = nullptr;
}

template<class ADerived>
ADerived& PassiveSingleton<ADerived>::Instance() {
    if (fgInstance == nullptr) [[unlikely]] {
        assert(MuteSingleton<ADerived>::fgInstanceNode == nullptr);
        FindInstance();
    }
    assert(fgInstance == *MuteSingleton<ADerived>::fgInstanceNode);
    return *fgInstance;
}

template<class ADerived>
void PassiveSingleton<ADerived>::FindInstance() {
    if (const auto optionalNode = internal::MuteSingletonPool::Instance().Find<ADerived>();
        optionalNode.has_value()) {
        if (auto& node = optionalNode->get();
            node != nullptr) {
            MuteSingleton<ADerived>::fgInstanceNode = std::addressof(node);
            fgInstance = static_cast<ADerived*>(node);
        } else {
            throw std::logic_error(
                std::string("MACE::Env::Memory::PassiveSingleton::Instance(): The instance of ")
                    .append(typeid(ADerived).name())
                    .append(" (free singleton in environment) has been deleted"));
        }
    } else {
        throw std::logic_error(
            std::string("MACE::Env::Memory::PassiveSingleton::Instance(): ")
                .append(typeid(ADerived).name())
                .append(" (free singleton in environment) has not been instantiated"));
    }
}

} // namespace MACE::Env::Memory
