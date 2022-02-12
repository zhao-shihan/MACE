#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::CalorimeterHit :
    private MACE::DataModel::Interface::Data {
public:
    CalorimeterHit() noexcept;
    CalorimeterHit(const CalorimeterHit& hit) noexcept;
    CalorimeterHit(CalorimeterHit&& hit) noexcept;
    virtual ~CalorimeterHit() noexcept {}
    CalorimeterHit& operator=(const CalorimeterHit& hit) noexcept;
    CalorimeterHit& operator=(CalorimeterHit&& hit) noexcept;

    static constexpr const char* Name() { return "CalHit"; }
    static void CreateBranches(TTree* tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    const auto& GetHitTime() const { return fHitTime; }
    const auto& GetEnergy() const { return fEnergy; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetEnergy(Double_t val) { fEnergy = val; }

private:
    Double_t fHitTime;
    Double_t fEnergy;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgEnergy;
};

inline void MACE::DataModel::CalorimeterHit::FillBranches() noexcept {
    Interface::Data::FillBranches();
    fgHitTime.value = fHitTime;
    fgEnergy.value = fEnergy;
}
