#pragma once

#include "DataModel/Global.hh"
#include "DataModel/Base/Data.hh"

class MACE::DataModel::Hit::CalorimeterHit :
    protected MACE::DataModel::Base::Data {
public:
    CalorimeterHit() noexcept;
    CalorimeterHit(const CalorimeterHit& hit) noexcept;
    CalorimeterHit(CalorimeterHit&& hit) noexcept;
    virtual ~CalorimeterHit() noexcept {}
    CalorimeterHit& operator=(const CalorimeterHit& hit) noexcept;
    CalorimeterHit& operator=(CalorimeterHit&& hit) noexcept;

    static constexpr const char* Name() { return "CalHit"; }
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() noexcept override;

    auto GetHitTime() const { return fHitTime; }
    auto GetEnergy() const { return fEnergy; }

    void SetHitTime(double_t val) { fHitTime = val; }
    void SetEnergy(double_t val) { fEnergy = val; }

private:
    double_t fHitTime;
    double_t fEnergy;

    static Float_t persistHitTime;
    static Float_t persistEnergy;
};