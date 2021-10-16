#pragma once

#include "TFile.h"

#include "DataModel/Global.hh"

class MACE::DataModel::Base::PersistencyHandler {
    PersistencyHandler(const PersistencyHandler&) = delete;
    PersistencyHandler& operator=(const PersistencyHandler&) = delete;
public:
    PersistencyHandler();
    virtual ~PersistencyHandler() = 0;

protected:
    virtual void Open(const char* fileName, Option_t* option);
    virtual void Close(Option_t* option = nullptr);

protected:
    TFile* fFile;
};