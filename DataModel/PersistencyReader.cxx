#include "DataModel/PersistencyReader.hxx"

using namespace MACE::DataModel;

PersistencyReader::PersistencyReader() :
    PersistencyHandler() {}

PersistencyReader::PersistencyReader(const char* fileName) :
    PersistencyHandler() {
    PersistencyReader::Open(fileName);
}