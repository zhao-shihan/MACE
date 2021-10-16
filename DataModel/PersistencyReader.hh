#pragma once

#include "ROOT/RDataFrame.hxx"

#include "DataModel/Global.hh"
#include "DataModel/Base/PersistencyHandler.hh"
#include "DataModel/TreeNameHandler.hh"

class MACE::DataModel::PersistencyReader :
    public MACE::DataModel::Base::PersistencyHandler {
    PersistencyReader(const PersistencyReader&) = delete;
    PersistencyReader& operator=(const PersistencyReader&) = delete;
public:
    PersistencyReader();
    virtual ~PersistencyReader();

    virtual void Open(const char* fileName, Option_t* = nullptr) override { PersistencyHandler::Open(fileName, "READ"); }
    using PersistencyHandler::Close;

    // template<class DataType>
    // ROOT::RDataFrame ReadTree() { return ROOT::RDataFrame(TreeNameHandler::GetName(), fFile); }
};