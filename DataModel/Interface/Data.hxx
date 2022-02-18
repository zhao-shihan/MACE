#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Column.hxx"

class MACE::DataModel::Interface::Data {
protected:
    Data() = default;
    Data(const Data& data) noexcept = default;
    Data(Data&& data) noexcept = default;
    virtual ~Data() noexcept = 0;
    Data& operator=(const Data& data) noexcept = default;
    Data& operator=(Data&& data) noexcept = default;

    // Override this in derived classes at least once!
    static constexpr const char* Name() { return "MACE_DataModel_Base_Data"; }
    // Extend (override & invoke) this in derived classes!
    static void CreateBranches(TTree& tree) { tree.ResetBranchAddresses(); }
    // Extend (override & invoke) this in derived classes!
    inline void FillBranchVariables() const noexcept {}
    // Extend (override & invoke) this in derived classes!
    static void ReadBranches(TTree& tree) { tree.ResetBranchAddresses(); }
};
