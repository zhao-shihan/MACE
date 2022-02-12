#include <iostream>

#include "DataModel/Interface/PersistencyHandler.hxx"

using namespace MACE::DataModel::Interface;

PersistencyHandler::PersistencyHandler() :
    fFile(nullptr),
    fTreeNamePrefix(std::make_pair<TString, TString>("Eve", "_")),
    fTreeNameSuffix(std::make_pair<TString, TString>("", "")) {}

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

static Bool_t Split(const TString& format, Char_t indexer, std::pair<TString, TString>& result) {
    auto index = format.First(indexer);
    if (index == kNPOS) {
        result = std::make_pair<TString, TString>(TString(format), TString(""));
        return false;
    } else {
        result = std::make_pair<TString, TString>(format(0, index), format(index + 1, format.Length() - index - 1));
        return true;
    }
}

void PersistencyHandler::SetTreeNameIndexer(Char_t indexer) {
    fTreeNameIndexer = indexer;
    fPrefixHasIndexer = Split(fTreeNamePrefixFormat, fTreeNameIndexer, fTreeNamePrefix);
    fSuffixHasIndexer = Split(fTreeNameSuffixFormat, fTreeNameIndexer, fTreeNameSuffix);
}

void PersistencyHandler::SetTreeNamePrefixFormat(const TString& prefix) {
    fTreeNamePrefixFormat = prefix;
    fPrefixHasIndexer = Split(fTreeNamePrefixFormat, fTreeNameIndexer, fTreeNamePrefix);
}

void PersistencyHandler::SetTreeNameSuffixFormat(const TString& suffix) {
    fTreeNameSuffixFormat = suffix;
    fSuffixHasIndexer = Split(fTreeNameSuffixFormat, fTreeNameIndexer, fTreeNameSuffix);
}