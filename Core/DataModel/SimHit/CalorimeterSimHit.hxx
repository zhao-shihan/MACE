#pragma once

#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "Core/DataModel/Hit/CalorimeterHit.hxx"

namespace MACE::Core::DataModel::SimHit {

using BranchSocket::IntBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using Utility::ShortString;

class CalorimeterSimHit : public Hit::CalorimeterHit {
    friend DataHub;

public:
    CalorimeterSimHit() noexcept;
    CalorimeterSimHit(const CalorimeterSimHit& hit) noexcept = default;
    CalorimeterSimHit(CalorimeterSimHit&& hit) noexcept = default;
    virtual ~CalorimeterSimHit() noexcept = default;
    CalorimeterSimHit& operator=(const CalorimeterSimHit& hit) noexcept = default;
    CalorimeterSimHit& operator=(CalorimeterSimHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetParticle() const { return fParticle; }
    [[nodiscard]] const auto& GetG4EventID() const { return fG4EventID; }
    [[nodiscard]] const auto& GetG4TrackID() const { return fG4TrackID; }

    template<typename String_t>
    void SetParticle(String_t&& particleName) { fParticle = std::forward<String_t>(particleName); }
    void SetG4EventID(Int_t val) { fG4EventID = val; }
    void SetG4TrackID(Int_t val) { fG4TrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "CalSimHit"; }

private:
    ShortString fParticle;
    Int_t fG4EventID;
    Int_t fG4TrackID;

    static ShortStringBranchSocket fgParticle;
    static IntBranchSocket fgG4EventID;
    static IntBranchSocket fgG4TrackID;
};

} // namespace MACE::Core::DataModel::SimHit
