#pragma once

#include "DataModel/Global.hh"

class MACE::DataModel::Base::Data {
public:
    virtual ~Data() noexcept {}

    static constexpr const char* Name();
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() noexcept = 0;
};