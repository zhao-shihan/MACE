#pragma once

#include "MACE/Core/DataModel/SimHit/EMCalSimHit.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::Hit {

using Utility::ObserverPtr;

class EMCalHit final : public G4VHit,
                       public Core::DataModel::SimHit::EMCalSimHit {
public:
    EMCalHit() noexcept = default;
    EMCalHit(const EMCalHit& hit) noexcept = default;
    EMCalHit(EMCalHit&& hit) noexcept = default;
    ~EMCalHit() noexcept = default;
    EMCalHit& operator=(const EMCalHit& hit) noexcept = default;
    EMCalHit& operator=(EMCalHit&& hit) noexcept = default;

    inline void* operator new(size_t);
    inline void operator delete(void*);

private:
    static ObserverPtr<G4Allocator<EMCalHit>> fgEMCalHitAllocator;
};

using EMCalHitCollection = G4THitsCollection<EMCalHit>;

} // namespace MACE::SimMACE::Hit

#include "MACE/SimMACE/Hit/EMCalHit.inl"
