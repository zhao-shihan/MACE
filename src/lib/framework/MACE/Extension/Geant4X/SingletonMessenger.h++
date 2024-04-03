#pragma once

#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/Memory/Singleton.h++"
#include "MACE/Env/Print.h++"
#include "MACE/Extension/stdx/tuple_contains.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <concepts>
#include <exception>
#include <tuple>
#include <typeinfo>
#include <unordered_set>

namespace MACE::inline Extension::Geant4X {

template<typename ADerived, typename... ARecipients>
class SingletonMessenger : public Env::Memory::Singleton<ADerived>,
                           public G4UImessenger {
protected:
    SingletonMessenger();
    ~SingletonMessenger() = default;

public:
    template<typename ARecipient>
    friend class Register;
    template<typename ARecipient>
    class Register final {
    public:
        Register(gsl::not_null<ARecipient*> recipient);
        ~Register();

    private:
        ARecipient* fRecipient;
    };

protected:
    template<typename ARecipient>
        requires stdx::tuple_contains_unique_v<std::tuple<ARecipients...>, ARecipient>
    auto Deliver(std::invocable<ARecipient&> auto&& Action) const -> void;

private:
    mutable bool fDelivering;
    std::tuple<std::unordered_set<ARecipients*>...> fRecipientSetTuple;
};

} // namespace MACE::inline Extension::Geant4X

#include "MACE/Extension/Geant4X/SingletonMessenger.inl"
