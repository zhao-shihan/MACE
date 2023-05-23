namespace MACE::Env::Memory {

template<class ADerived>
ADerived* PassiveSingleton<ADerived>::fgInstance = nullptr;

template<class ADerived>
PassiveSingleton<ADerived>::PassiveSingleton() :
    PassiveSingletonBase(),
    WeakSingleton<ADerived>() {
    static_assert(PassiveSingletonified<ADerived>);
    fgInstance = static_cast<ADerived*>(this);
}

template<class ADerived>
PassiveSingleton<ADerived>::~PassiveSingleton() {
    fgInstance = nullptr;
}

template<class ADerived>
ADerived& PassiveSingleton<ADerived>::Instance() {
    if (fgInstance == nullptr) [[unlikely]] {
        assert(WeakSingleton<ADerived>::fgInstanceNode == nullptr);
        FindInstance();
    }
    assert(fgInstance == *WeakSingleton<ADerived>::fgInstanceNode);
    return *fgInstance;
}

template<class ADerived>
void PassiveSingleton<ADerived>::FindInstance() {
    if (const auto optionalNode = internal::WeakSingletonPool::Instance().Find<ADerived>();
        optionalNode.has_value()) {
        if (auto& node = optionalNode->get();
            node != nullptr) {
            WeakSingleton<ADerived>::fgInstanceNode = std::addressof(node);
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
