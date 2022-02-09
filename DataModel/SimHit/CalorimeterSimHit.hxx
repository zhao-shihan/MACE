#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Hit/CalorimeterHit.hxx"

class MACE::DataModel::CalorimeterSimHit :
    public MACE::DataModel::CalorimeterHit {
public:
    CalorimeterSimHit() noexcept;
    CalorimeterSimHit(const CalorimeterSimHit& hit) noexcept;
    CalorimeterSimHit(CalorimeterSimHit&& hit) noexcept;
    virtual ~CalorimeterSimHit() noexcept {}
    CalorimeterSimHit& operator=(const CalorimeterSimHit& hit) noexcept;
    CalorimeterSimHit& operator=(CalorimeterSimHit&& hit) noexcept;

    static void CreateBranches(TTree* tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    const auto& GetParticlePDGCode() const { return fPDGCode; }
    auto GetTrackID() const { return fTrackID; }

    void SetPDGCode(Int_t pdgCode) { fPDGCode = pdgCode; }
    void SetTrackID(Int_t val) { fTrackID = val; }

private:
    Int_t fPDGCode;
    Int_t fTrackID;

    static DataModel::Column<Int_t> fgPDGCode;
    static DataModel::Column<Int_t> fgTrackID;
};

inline void MACE::DataModel::CalorimeterSimHit::FillBranches() noexcept {
    DataModel::CalorimeterHit::FillBranches();
    fgPDGCode.value = fPDGCode;
    fgTrackID.value = fTrackID;
}
