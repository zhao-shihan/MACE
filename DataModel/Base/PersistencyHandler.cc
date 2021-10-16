#include <iostream>

#include "DataModel/Base/PersistencyHandler.hh"

using namespace MACE::DataModel::Base;

PersistencyHandler::PersistencyHandler() :
    fFile(nullptr) {}

PersistencyHandler::~PersistencyHandler() {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            std::cerr << "Warning from MACE::DataModel::PersistencyHandler::~PersistencyHandler : "
                "We think you forgot to close the file! Although we will close it for you, "
                "it is recommended for you to explicitly call the Close(...) function somewhere "
                "to close the file, in order to control the behaviour fully." << std::endl;
            fFile->Close();
        } else {
            std::cerr << "Warning from MACE::DataModel::PersistencyHandler::~PersistencyHandler : "
                "... How could you close the file without deleting it and setting it to nullptr "
                "(this is the behavior of the Close(...) function)? If you did not intend to do this, "
                "please contact the developer. " << std::endl;
        }
        delete fFile;
    }
}

void PersistencyHandler::Open(const char* fileName, Option_t* option) {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            std::cerr << "Warning from MACE::DataModel::PersistencyHandler::Open : "
                "Current file is not closed. Nothing was done." << std::endl;
            return;
        } else {
            std::cerr << "Warning from MACE::DataModel::PersistencyHandler::Open : "
                "... How could you close the file without deleting it and setting it to nullptr "
                "(this is the behavior of the Close(...) function)? If you did not intend to do this, "
                "please contact the developer. " << std::endl;
        }
        delete fFile;
    }
    fFile = new TFile(fileName, option);
}

void PersistencyHandler::Close(Option_t* option) {
    if (fFile == nullptr) {
        std::cerr << "Warning from MACE::DataModel::PersistencyHandler::Close : "
            "Current file does not exist. Nothing was done." << std::endl;
        return;
    }
    if (fFile->IsOpen()) {
        fFile->Close(option);
    } else {
        std::cerr << "Warning from MACE::DataModel::PersistencyHandler::Close : "
            "... How could you close the file without deleting it and setting it to nullptr "
            "(this is the behavior of the Close(...) function)? If you did not intend to do this, "
            "please contact the developer. " << std::endl;
    }
    delete fFile;
    fFile = nullptr;
}
