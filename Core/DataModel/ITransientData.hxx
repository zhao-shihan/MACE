#pragma once

#include "TTree.h"

#include <concepts>

namespace MACE::Core::DataModel {

class ITransientData {
protected:
    ITransientData() noexcept = default;
    ITransientData(const ITransientData& data) noexcept = default;
    ITransientData(ITransientData&& data) noexcept = default;
    virtual ~ITransientData() noexcept = 0;
    ITransientData& operator=(const ITransientData& data) noexcept = default;
    ITransientData& operator=(ITransientData&& data) noexcept = default;

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

template<class Data_t>
concept IsTransientData = std::derived_from<Data_t, ITransientData>;

} // namespace MACE::Core::DataModel
