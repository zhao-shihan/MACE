#include "DataModel/PersistencyReader.hh"

using namespace MACE::DataModel;

PersistencyReader::PersistencyReader() :
    PersistencyHandler() {}

PersistencyReader::PersistencyReader(const char* fileName) :
    PersistencyHandler() {
    PersistencyReader::Open(fileName);
}