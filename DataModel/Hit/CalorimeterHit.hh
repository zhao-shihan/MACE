#pragma once

#include "DataModel/Global.hh"
#include "DataModel/Base/Data.hh"

class MACE::DataModel::Hit::CalorimeterHit :
    protected MACE::DataModel::Base::Data {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(CalorimeterHit);
public:
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