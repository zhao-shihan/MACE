#pragma once

#include "DataModel/Interface/BranchSocket.hxx"

template<MACE::DataModel::ClassType Class_t>
class MACE::DataModel::ClassBranchSocket final :
    public MACE::DataModel::Interface::BranchSocket<Class_t> {
public:
    template<typename... Args>
    ClassBranchSocket(const char* branchName, Args&&... args);
    ~ClassBranchSocket() noexcept;
    ClassBranchSocket(const ClassBranchSocket&) = delete;
    ClassBranchSocket& operator=(const ClassBranchSocket&) = delete;

    [[nodiscard]] const Class_t& GetValue() const override { return *fObject; }
    void SetValue(const Class_t& object) override { *fObject = object; }

    void CreateBranch(TTree& tree) override { tree.Branch(fBranchName, std::addressof(fObject), 256000, 0); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(fBranchName, std::addressof(fObject)); }

private:
    const TString fBranchName;
    Class_t* fObject;
};

#include "DataModel/BranchSocket/ClassBranchSocket.ixx"
