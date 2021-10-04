#pragma once

#include "DataModelGlobal.hh"

#include "base/Manager.hh"
#include "hit/transient/Calorimeter.hh"
#include "hit/transient/OrbitalDetector.hh"
#include "hit/transient/Spectrometer.hh"
#include "hit/persistency/Calorimeter.hh"
#include "hit/persistency/OrbitalDetector.hh"
#include "hit/persistency/Spectrometer.hh"

class MACE::DataModel::Hit::Manager : public MACE::DataModel::Base::Manager {
    MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(Manager);
private:
    using Base::Manager::Manager;
public:
    static Manager* Instance();
};