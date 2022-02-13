#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Column.hxx"

class MACE::DataModel::Interface::Data {
public:
    virtual ~Data() noexcept = 0;

    // Override this in derived classes at least once!
    static constexpr const char* Name() { return "MACE_DataModel_Base_Data"; }
    // Extend (override & invoke) this in derived classes!
    static void CreateBranches(TTree* tree) {}
    // Extend (override & invoke) this in derived classes!
    inline void FillBranches() noexcept {}
    // Extend (override & invoke) this in derived classes!
    static void ReadBranches(TTree* tree) {}
};
