#pragma once

#include "DataModelGlobal.hh"

class MACE::DataModel::Base::Data {
public:
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() = 0;
};