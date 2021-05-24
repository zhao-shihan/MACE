#ifndef PSIMACEAnalysisManager_h
#define PSIMACEAnalysisManager_h 1

#include <list>
#include <fstream>
#include "hit/PSIMACECsIHit.hh"
#include "hit/PSIMACEMCPHit.hh"
#include "hit/PSIMACEMWPCHit.hh"

#include "globals.hh"

class PSIMACEAnalysisManager {
private:
    G4ThreadLocal static PSIMACEAnalysisManager fInstance;
public:
    static PSIMACEAnalysisManager& ThreadLocalInstance() { return fInstance; }
private:
    PSIMACEAnalysisManager();
    ~PSIMACEAnalysisManager();
    PSIMACEAnalysisManager(const PSIMACEAnalysisManager&) = delete;
    const PSIMACEAnalysisManager& operator=(const PSIMACEAnalysisManager&) = delete;

private:
    static G4String fFileName;
    static std::ofstream* fout[3];
    enum { fMCP, fCsI, fMWPC };
public:
    static void Open();
    static void Close();
    static void SetFileName(const G4String& csvFileName) { fFileName = csvFileName; }
    static const G4String& GetFileName() { return fFileName; }

private:
    std::vector<PSIMACEMCPHit>* fpMCPHitList;
    std::vector<PSIMACECsIHit>* fpCsIHitList;
    std::vector<PSIMACEMWPCHit>* fpMWPCHitList;
public:
    void SubmitMCPHitList(std::vector<PSIMACEMCPHit>* hitList) { fpMCPHitList = hitList; }
    void SubmitCsIHitList(std::vector<PSIMACECsIHit>* hitList) { fpCsIHitList = hitList; }
    void SubmitMWPCHitList(std::vector<PSIMACEMWPCHit>* hitList) { fpMWPCHitList = hitList; }
    void AnalysisAndWrite();

private:
    static size_t fSignalSN;

    void WriteCoincidentMCPHit(const PSIMACEMCPHit& CMCPHit) const;
    void WriteCoincidentCsIHit(std::list<const PSIMACECsIHit*>& CCsIHitList) const;
    void WriteCoincidentMWPCHit(std::list<const PSIMACEMWPCHit*>& CMWPCHitList) const;
};

#endif
