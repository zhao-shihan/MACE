#pragma once

#include "DataModel/Interface/BranchSocket.hxx"

template<typename Arith_t>
class MACE::DataModel::BasicBranchSocket final :
    public MACE::DataModel::Interface::BranchSocket<Arith_t, Arith_t*> {
    static_assert(std::is_arithmetic_v<Arith_t>,
        "Arith_t should be an arithmetic type!");
public:
    BasicBranchSocket(const char* branchName, Arith_t defaultValue);
    ~BasicBranchSocket() noexcept = default;
    BasicBranchSocket(const BasicBranchSocket&) = delete;
    BasicBranchSocket& operator=(const BasicBranchSocket&) = delete;

    [[nodiscard]] Arith_t& Value() override { return fValue; }
    [[nodiscard]] Arith_t* Address() override { return std::addressof(fValue); }

private:
    Arith_t fValue;
};

#include "DataModel/BranchSocket/BasicBranchSocket.ixx"

namespace MACE::DataModel {
    inline namespace BranchSocket {
        using IntBranchSocket = BasicBranchSocket<Int_t>;
        using FloatBranchSocket = BasicBranchSocket<Float_t>;
    }
}
