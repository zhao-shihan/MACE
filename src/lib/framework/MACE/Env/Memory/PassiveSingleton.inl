namespace MACE::Env::Memory {

template<typename ADerived>
ADerived* PassiveSingleton<ADerived>::fgInstance = nullptr;

template<typename ADerived>
PassiveSingleton<ADerived>::PassiveSingleton() :
    PassiveSingletonBase{},
    WeakSingleton<ADerived>{} {
    static_assert(PassiveSingletonified<ADerived>);
    fgInstance = static_cast<ADerived*>(this);
}

template<typename ADerived>
PassiveSingleton<ADerived>::~PassiveSingleton() {
    fgInstance = nullptr;
}

template<typename ADerived>
MACE_ALWAYS_INLINE auto PassiveSingleton<ADerived>::Instance() -> ADerived& {
    if (fgInstance == nullptr) [[unlikely]] {
        assert(WeakSingleton<ADerived>::fgInstanceNode == nullptr);
        FindInstance();
    }
    assert(fgInstance == *WeakSingleton<ADerived>::fgInstanceNode);
    return *fgInstance;
}

template<typename ADerived>
auto PassiveSingleton<ADerived>::FindInstance() -> void {
    if (const auto optionalNode = internal::WeakSingletonPool::Instance().Find<ADerived>();
        optionalNode.has_value()) {
        if (auto& node = optionalNode->get();
            node != nullptr) {
            WeakSingleton<ADerived>::fgInstanceNode = std::addressof(node);
            fgInstance = static_cast<ADerived*>(node);
        } else {
            throw std::logic_error{fmt::format("MACE::Env::Memory::PassiveSingleton::Instance(): "
                                               "The instance of {} (passive singleton in environment) has been deleted",
                                               typeid(ADerived).name())};
        }
    } else {
        throw std::logic_error{fmt::format("MACE::Env::Memory::PassiveSingleton::Instance(): "
                                           "{} (passive singleton in environment) has not been instantiated",
                                           typeid(ADerived).name())};
    }
}

} // namespace MACE::Env::Memory
