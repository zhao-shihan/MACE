namespace MACE::Env::Memory {

template<class ADerived>
ObserverPtr<internal::MuteSingletonPool::Node> MuteSingleton<ADerived>::fgInstanceNode = nullptr;

template<class ADerived>
MuteSingleton<ADerived>::MuteSingleton() :
    MuteSingletonBase() {
    static_assert(MuteSingletonized<ADerived>);
    if (auto& muteSingletonPool = internal::MuteSingletonPool::Instance();
        not muteSingletonPool.Contains<ADerived>()) {
        fgInstanceNode = std::addressof(muteSingletonPool.Insert(static_cast<ObserverPtr<ADerived>>(this)));
    } else {
        throw std::logic_error(
            std::string("MACE::Env::Memory::MuteSingleton::MuteSingleton(): "
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

} // namespace MACE::Env::Memory
