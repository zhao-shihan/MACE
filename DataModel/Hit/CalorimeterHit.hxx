#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::CalorimeterHit :
    public MACE::DataModel::Interface::Data {
    friend MACE::DataModel::DataHub;

public:
    CalorimeterHit() noexcept;
    CalorimeterHit(const CalorimeterHit& hit) noexcept;
    CalorimeterHit(CalorimeterHit&& hit) noexcept;
    virtual ~CalorimeterHit() noexcept = default;
    CalorimeterHit& operator=(const CalorimeterHit& hit) noexcept;
    CalorimeterHit& operator=(CalorimeterHit&& hit) noexcept;

    [[nodiscard]] const auto& GetHitTime() const { return fHitTime; }
    [[nodiscard]] const auto& GetEnergy() const { return fEnergy; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetEnergy(Double_t val) { fEnergy = val; }

protected:
    static constexpr const char* Name() { return "CalHit"; }
    static void CreateBranches(TTree& tree);
    inline void FillBranchVariables() const noexcept;
    static void ReadBranches(TTree& tree);

private:
    Double_t fHitTime;
    Double_t fEnergy;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgEnergy;
};

inline void MACE::DataModel::CalorimeterHit::FillBranchVariables() const noexcept {
    Interface::Data::FillBranchVariables();
    fgHitTime.value = fHitTime;
    fgEnergy.value = fEnergy;
}
