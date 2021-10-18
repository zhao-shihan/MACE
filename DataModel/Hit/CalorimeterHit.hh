#pragma once

#include "DataModel/Global.hh"
#include "DataModel/Core/Data.hh"

class MACE::DataModel::Hit::CalorimeterHit :
    protected MACE::DataModel::Core::Data {
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

    auto GetHitTime() const { return fHitTime; }
    auto GetEnergy() const { return fEnergy; }

    void SetHitTime(double_t val) { fHitTime = val; }
    void SetEnergy(double_t val) { fEnergy = val; }

private:
    double_t fHitTime;
    double_t fEnergy;

    static Core::Column<Float_t> fgHitTime;
    static Core::Column<Float_t> fgEnergy;
};

void MACE::DataModel::Hit::CalorimeterHit::FillBranches() noexcept {
    MACE::DataModel::Core::Data::FillBranches();
    fgHitTime.value = fHitTime;
    fgEnergy.value = fEnergy;
}