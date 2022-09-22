#pragma once

#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/Hit/EMCalHit.hxx"

#include <utility>
#include <string_view>

namespace MACE::Core::DataModel::SimHit {

using namespace std::string_view_literals;

class EMCalSimHit : public Hit::EMCalHit {
public:
    EMCalSimHit() noexcept;
    virtual ~EMCalSimHit() = default;

    EMCalSimHit(const EMCalSimHit& hit) noexcept = default;
    EMCalSimHit(EMCalSimHit&& hit) noexcept = default;
    EMCalSimHit& operator=(const EMCalSimHit& hit) noexcept = default;
    EMCalSimHit& operator=(EMCalSimHit&& hit) noexcept = default;

    const auto& GetParticle() const { return fParticle; }
    const auto& GetG4EventID() const { return fG4EventID; }
    const auto& GetG4TrackID() const { return fG4TrackID; }

    void SetParticle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }
    void SetG4EventID(int val) { fG4EventID = val; }
    void SetG4TrackID(int val) { fG4TrackID = val; }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "CalSimHit"sv; }

private:
    Utility::ShortString fParticle;
    int fG4EventID;
    int fG4TrackID;

    static BranchSocket::ShortStringBranchSocket fgParticle;
    static BranchSocket::IntBranchSocket fgG4EventID;
    static BranchSocket::IntBranchSocket fgG4TrackID;
};
static_assert(TransientData<EMCalSimHit>);

} // namespace MACE::Core::DataModel::SimHit
