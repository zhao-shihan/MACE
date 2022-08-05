namespace MACE::Environment::Memory {

template<class ADerived>
ObserverPtr<Detail::MuteSingletonPool::Node> MuteSingleton<ADerived>::fgInstanceNode = nullptr;

template<class ADerived>
MuteSingleton<ADerived>::MuteSingleton() :
    MuteSingletonBase() {
    static_assert(Concept::MuteSingletonized<ADerived>);
    if (auto& muteSingletonPool = Detail::MuteSingletonPool::Instance();
        not muteSingletonPool.Contains<ADerived>()) {
        fgInstanceNode = std::addressof(muteSingletonPool.Insert(static_cast<ADerived*>(this)));
    } else {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::MuteSingleton::MuteSingleton(): "
                        "Trying to construct ")
                .append(typeid(ADerived).name())
                .append(" (mute singleton in environment) twice"));
    }
}

template<class ADerived>
MuteSingleton<ADerived>::~MuteSingleton() {
    if (fgInstanceNode != nullptr) {
        *fgInstanceNode = nullptr;
        fgInstanceNode = nullptr;
    }
}

} // namespace MACE::Environment::Memory
