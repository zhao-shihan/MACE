#ifndef PSIMACEAnalysisManager_h
#define PSIMACEAnalysisManager_h 1

#include <fstream>
#include <array>
#include <list>

#include "globals.hh"

class PSIMACEAnalysisManager {
private:
    static PSIMACEAnalysisManager* instance;
public:
    static PSIMACEAnalysisManager* Instance();
private:
    PSIMACEAnalysisManager();
    PSIMACEAnalysisManager(const PSIMACEAnalysisManager&) = delete;
    const PSIMACEAnalysisManager& operator=(const PSIMACEAnalysisManager&) = delete;

private:
    G4String fFileName;
    std::ofstream* fout[3];
    enum { fMCP, fCsI, fMWPC };

public:
    ~PSIMACEAnalysisManager();

    void Open();

    void WriteMCPHitList(std::vector<std::array<G4double, 3>>& list);
    void WriteCsIHitList(std::vector<std::array<G4double, 2>>& list);
    void WriteMWPCHitList(std::vector<std::pair<std::array<G4double, 4>, G4int>>& list);

    void Close();

    void SetFileName(const G4String& csvFileName) { fFileName = csvFileName; }
    const G4String& GetFileName() { return fFileName; }
};

#endif
