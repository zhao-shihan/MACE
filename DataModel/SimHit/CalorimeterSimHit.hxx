#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Hit/CalorimeterHit.hxx"

class MACE::DataModel::CalorimeterSimHit :
    public MACE::DataModel::CalorimeterHit {
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
    inline void FillBranchVariables() const noexcept;
    static void ReadBranches(TTree& tree);

private:
    static constexpr const char* BasicName() { return "CalSimHit"; }

private:
    Int_t fPDGCode;
    Int_t fTrackID;

    static Column<Int_t> fgPDGCode;
    static Column<Int_t> fgTrackID;
};

inline void MACE::DataModel::CalorimeterSimHit::FillBranchVariables() const noexcept {
    CalorimeterHit::FillBranchVariables();
    fgPDGCode.value = fPDGCode;
    fgTrackID.value = fTrackID;
}
