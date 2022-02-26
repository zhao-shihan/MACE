#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Hit/CalorimeterHit.hxx"
#include "DataModel/BranchSocket/BasicBranchSocket.hxx"

class MACE::DataModel::CalorimeterSimHit :
    public MACE::DataModel::CalorimeterHit {
    using Base = MACE::DataModel::CalorimeterHit;
    friend MACE::DataModel::DataHub;

public:
    CalorimeterSimHit() noexcept;
    CalorimeterSimHit(const CalorimeterSimHit& hit) noexcept = default;
    CalorimeterSimHit(CalorimeterSimHit&& hit) noexcept = default;
    virtual ~CalorimeterSimHit() noexcept = default;
    CalorimeterSimHit& operator=(const CalorimeterSimHit& hit) noexcept = default;
    CalorimeterSimHit& operator=(CalorimeterSimHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetParticlePDGCode() const { return fPDGCode; }
    [[nodiscard]] const auto& GetTrackID() const { return fTrackID; }

    void SetPDGCode(Int_t pdgCode) { fPDGCode = pdgCode; }
    void SetTrackID(Int_t val) { fTrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "CalSimHit"; }

private:
    Int_t fPDGCode;
    Int_t fTrackID;

    static IntBranchSocket fgPDGCode;
    static IntBranchSocket fgTrackID;
};

inline void MACE::DataModel::CalorimeterSimHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgPDGCode.Value() = fPDGCode;
    fgTrackID.Value() = fTrackID;
}
