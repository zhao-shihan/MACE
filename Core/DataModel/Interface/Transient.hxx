#pragma once

#include "DataModel/Global.hxx"

class MACE::DataModel::Interface::Transient {
protected:
    Transient() noexcept = default;
    Transient(const Transient& data) noexcept = default;
    Transient(Transient&& data) noexcept = default;
    virtual ~Transient() noexcept = 0;
    Transient& operator=(const Transient& data) noexcept = default;
    Transient& operator=(Transient&& data) noexcept = default;

    // Extend (override & invoke) this in derived classes!
    static void CreateBranches(TTree&) {}
    // Extend (override & invoke) this in derived classes!
    static void ConnectToBranches(TTree&) {}
    // Extend (override & invoke) this in derived classes!
    inline void FillBranchSockets() const noexcept {}

private:
    // Override this in derived classes at least once!
    static constexpr const char* BasicName() { return "MACE_DataModel_Base_Data"; }
};
