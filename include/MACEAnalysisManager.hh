#ifndef MACEAnalysisManager_h
#define MACEAnalysisManager_h 1

#include <list>
#include <fstream>
#include "hit/MACECsIHit.hh"
#include "hit/MACEMCPHit.hh"
#include "hit/MACEMWPCHit.hh"

#include "globals.hh"

class MACEAnalysisManager {
private:
    G4ThreadLocal static MACEAnalysisManager fInstance;
public:
    static MACEAnalysisManager& ThreadLocalInstance() { return fInstance; }
private:
    MACEAnalysisManager();
    ~MACEAnalysisManager();
    MACEAnalysisManager(const MACEAnalysisManager&) = delete;
    const MACEAnalysisManager& operator=(const MACEAnalysisManager&) = delete;

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
    std::vector<MACEMCPHit>* fpMCPHitList;
    std::vector<MACECsIHit>* fpCsIHitList;
    std::vector<MACEMWPCHit>* fpMWPCHitList;
public:
    void SubmitMCPHitList(std::vector<MACEMCPHit>* hitList) { fpMCPHitList = hitList; }
    void SubmitCsIHitList(std::vector<MACECsIHit>* hitList) { fpCsIHitList = hitList; }
    void SubmitMWPCHitList(std::vector<MACEMWPCHit>* hitList) { fpMWPCHitList = hitList; }
    void AnalysisAndWrite();

private:
    static size_t fSignalSN;

    void WriteCoincidentMCPHit(const MACEMCPHit& CMCPHit) const;
    void WriteCoincidentCsIHit(std::list<const MACECsIHit*>& CCsIHitList) const;
    void WriteCoincidentMWPCHit(std::list<const MACEMWPCHit*>& CMWPCHitList) const;
};

#endif
