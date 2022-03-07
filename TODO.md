# ToDo-List

- [ToDo-List](#todo-list)
  - [DataModel](#datamodel)
    - [Utility](#utility)
  - [EventDisplay](#eventdisplay)
  - [Geometry](#geometry)
    - [Utility](#utility-1)
    - [Interface](#interface)
    - [Coding](#coding)
  - [ReconSpectrometer](#reconspectrometer)
    - [Utility](#utility-2)
    - [Interface](#interface-1)
- [SimCalorimeter](#simcalorimeter)
- [SimMACE](#simmace)
    - [Physics](#physics)
    - [Messengers](#messengers)
    - [Primary Generator](#primary-generator)
    - [Detector](#detector)
    - [Action](#action)
    - [Other](#other)
    - [Coding Style](#coding-style)
  - [SimMTransport](#simmtransport)
    - [Utility](#utility-3)
    - [Coding Style](#coding-style-1)
  - [SimSpectrometer](#simspectrometer)
  - [ThirdParty](#thirdparty)
  - [Utility](#utility-4)
  - [Other](#other-1)
  - [Defect](#defect)

## DataModel

### Utility

1. Add momentum, vertex momentum in SpectrometerSimHit.
2. Add vertex time in Track (for vertex time coincidence).
3. Implement PhysicsTrack. It can be transformed from and to HelixTrack.
4. How to store fully-reconstructed event?
5. (Long-term) Implement RawHit.
6. (Long-term) Implement SimRawHit.
7. (Completed) ~~With new way of manage the relation between beam repetition and G4Event, trackID is not longer identical, need to save eventID. (see also ReconSpectrometer-Utility-1)~~
8. (Completed) ~~Track should hold time.~~
9. (Completed) ~~Branch name's first letter should be lower-cased.~~

## EventDisplay

## Geometry

### Utility

1. (Completed) ~~CDC cell's sensitive volume should be a cylinder instead of parallepipe. This behaviour is now act in SD as an if(...), draw it down directly in geometry is simpler.~~
2. (Completed) ~~CDC cells and layers transform and size (and layerId for cells) list should be constructed in description.~~
3. (Completed) ~~In geometry hierarchy, solenoid and field volume is at the same level. Maybe the field as solenoid's mother is better.~~ (Note: fixed a lot of "stuck")
4. (Cancelled) ~~Like above, but for shields.~~
5. (Cancelled) ~~Add a geometry constructor for universial usage.~~
6. (Ongoing) Consider location constraints. E.g. solenoid has exactly the same length as the corresponding field, down-stream field is connect to the up-stream field, etc. Benefits for dynamic geometry.
7. (Completed) ~~Add spectrometer magnet.~~
8. Add vacuum chamber shell.
9. (Completed) ~~CDC herierachy: Body - ReadOutLayer - Cell - (FieldWire, Sensitive - SenseWire)~~
10. (Completed) ~~Using a more resonable way of constructing spectrometer (instead of making a large bunch of logical volumes...).~~
11. (Completed) ~~Fix sensitive volume overlaps.~~

### Interface

1. (Cancelled) ~~Update description interface for pure G4 geometry usage.~~

### Coding

1. Using correct (or better) version of G4PVPlacement constructor. Fooled by exampleB1.

## ReconSpectrometer

### Utility

1. (Completed) ~~With new way of manage the relation between beam repetition and G4Event, trackID is not longer identical. Use both trackID and eventID in TrueFinder to recognize tracks. (see also DataModel-Utility-7)~~

### Interface

1. (Cancelled) ~~Keep the status quo.~~
2. New herierachy: Tracker - (GlobalFinder - LocalFinder - Fitter)

# SimCalorimeter

# SimMACE

### Physics

1. Add decay: u->eeevv, together with muonium and anti-muonium.
2. Add muon/muonium/anti-muonium decay with spin, review code from musr.
3. Review MuoniumDecayChannel/AntiMuoniumDecayChannel.
4. Better and modern implementation of MuoniumTransport. See also SimMTransport.
5. Investigate parameterisation and fast simulation interface of G4.
6. Investigate physics processes that really need.

### Messengers

1. Dynamic geometry. Need geometry messenger and other supports. Geometry messenger hold a DetectorConstruction and sets entities. Implement geometry messenger as a single class is ok.
2. More physics options. E.g. control rest muon electron capture probability (using exp(.)'s CDF), adjust decay mode, muonium transport parameters, etc.

### Primary Generator

1. (Ongoing) Time structure of bunch?
2. Correct momentum. Using degrader to slow muon down.

### Detector

1. (Completed) ~~Setup G4Regions, like calorimeter region, solenoid region, shield region, etc.~~
2. Set cut for solenoid and shield to acclerate simulation in certain case.

### Action

1. (Cancelled, replaced by SimMACE-Detector-2) ~~SteppingAction for killing track in spectrometer magnet and shield.~~

### Other

1. Note: now, as fast simulation, MCP may not annihilate e+ but scatter it back instead. In this case, calorimeter will not detect annihilate photons.
2. (Completed) ~~Customized RunManager.~~

### Coding Style

1. (Completed) ~~More inline namespaces.~~

## SimMTransport

### Utility

1. (Long-term) Need to connect to G4, a little bit of performance lose is ok. Already have some preliminary ideas: e.g when true random walk displacement exceeds a threshold then create a step in G4 (though there are many more true step); Defining target overall shape in G4 but use bool expression to define its fine structure; Target has many part, each part is applied with a bool expression, and using MC to define the exact material density used by G4; etc.

### Coding Style

1. Modern-er.

## SimSpectrometer

1. Extract SD, Hit and other relative part from SimMACE.
2. Geometry from Geometry module.
3. Primaries could be e+, e- with known momentum.

## ThirdParty

1. (Completed) ~~Better CMakeLists.txt for G4mpi.~~

## Utility

1. Running timings and time statistics.
2. (Completed) ~~Filename generator and result file management for MPI.~~
3. Common random seed distributor.
4. Config file reader?
5. (Completed) ~~G4MPIRunManager!~~
6. (Suspended) ~~Better eventID distribution on ranks for G4MPIRunManager.~~
7. Use std::filesystem features to allow independent process of root file merging.

## Other

1. (Ongoing) Better CMakeLists coding.
2. (Ongoing) Use C++20 feature.
3. (Completed) ~~Suppress all of -Wall and -Wextra warnings (excluding ThirdParty).~~
4. (Cancelled, tough) ~~Consider to use built-in mimalloc as replacement of default allocator. (see also Defect-1)~~
5. Planning global interface of data analysis: Initialize - Process - Finalize, ReconSpectormeter and other could use the concept.
6. (Completed) ~~Investigate G4 vis engine.~~

## Defect

1. (Ignored) ~~Base-class of class that handles by G4Allocator should not have inlined virtual deconstructor. Maybe we can implement an alternative allocator. (see also Other-4)~~
2. (Completed, lead to Defect-5) ~~In TTreeViewer, the sub-branch of same name (like VertexPos.fX and HitPos.fX) is conflict. Maybe adjust split level could help?~~
3. (Completed) ~~Geometry::Description should use c'tor w/o noexcept, otherwise compile fail on clang (reported by S. S. Wan)~~
4. Using inline namespace just under namespace MACE (that is, Core, Simulation, Reconstruction, etc.) would confuse VSCode's C++ extension. However, the semantic and concept of MACE project herierachy is conserved.
5. Now use un-split class branch, causing root file's size larger: ~112% original size.
