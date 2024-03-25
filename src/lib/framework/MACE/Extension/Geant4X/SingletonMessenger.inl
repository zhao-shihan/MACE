namespace MACE::inline Extension::Geant4X {

template<typename ADerived, typename... ARecipients>
SingletonMessenger<ADerived, ARecipients...>::SingletonMessenger() :
    fDelivering{},
    fRecipientSetTuple{} {
    static_assert(std::derived_from<ADerived, SingletonMessenger<ADerived, ARecipients...>>);
    static_assert((... and stdx::tuple_contains_unique_v<std::tuple<ARecipients...>, ARecipients>));
}

template<typename ADerived, typename... ARecipients>
template<typename ARecipient>
SingletonMessenger<ADerived, ARecipients...>::Register<ARecipient>::Register(gsl::not_null<ARecipient*> recipient) :
    fRecipient{recipient} {
    static_assert(stdx::tuple_contains_unique_v<std::tuple<ARecipients...>, ARecipient>);
    get<std::unordered_set<ARecipient*>>(SingletonMessenger::Instance().fRecipientSetTuple).emplace(fRecipient);
}

template<typename ADerived, typename... ARecipients>
template<typename ARecipient>
SingletonMessenger<ADerived, ARecipients...>::Register<ARecipient>::~Register() {
    if (SingletonMessenger::Expired()) { return; }
    auto& messenger{SingletonMessenger::Instance()};
    if (messenger.fDelivering) {
        Env::PrintLnError("Fatal: de-register from SingletonMessenger during delivering");
        std::terminate();
    }
    get<std::unordered_set<ARecipient*>>(messenger.fRecipientSetTuple).erase(fRecipient);
}

template<typename ADerived, typename... ARecipients>
template<typename ARecipient>
    requires stdx::tuple_contains_unique_v<std::tuple<ARecipients...>, ARecipient>
auto SingletonMessenger<ADerived, ARecipients...>::Deliver(std::invocable<ARecipient&> auto&& Action) const -> void {
    const auto& recipientSet{get<std::unordered_set<ARecipient*>>(fRecipientSetTuple)};
    if (recipientSet.empty()) {
        Env::PrintLnError("{} not registered", typeid(ARecipient).name());
        return;
    }
    fDelivering = true;
    for (auto&& recipient : recipientSet) {
        Action(*recipient);
    }
    fDelivering = false;
}

} // namespace MACE::inline Extension::Geant4X
