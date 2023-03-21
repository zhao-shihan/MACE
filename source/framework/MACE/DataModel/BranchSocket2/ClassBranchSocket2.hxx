#pragma once

#include "MACE/DataModel/BranchSocketBase2.hxx"

#include "TTree.h"

#include "gsl/gsl"

#include <string>
#include <tuple>
#include <utility>

namespace MACE::DataModel::inline BranchSocket {

template<class AClass>
class ClassBranchSocket2 final : public BranchSocketBase2<ClassBranchSocket2<AClass>, AClass> {
public:
    template<typename... Args>
    ClassBranchSocket2(std::string name, std::tuple<Args&&...> argTuple);
    ~ClassBranchSocket2();

    const auto& Value() const { return *fObject; }
    void Value(auto&& v) { *fObject = std::forward<decltype(v)>(v); }

    void CreateBranch(TTree& tree) { tree.Branch(this->fName.c_str(), &fObject); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fName.c_str(), &fObject); }

private:
    const gsl::owner<AClass*> fObject;
};

} // namespace MACE::DataModel::inline BranchSocket

#include "MACE/DataModel/BranchSocket2/ClassBranchSocket2.inl"
