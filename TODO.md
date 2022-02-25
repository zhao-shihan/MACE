# ToDo

## DataModel

### Utility

1. Add momentum, vertex momentum in SpectrometerSimHit.
2. Add vertex time in Track (for vertex time coincidence).
3. Implement PhysicsTrack. It can be transformed from and to HelixTrack.
4. How to store fully-reconstructed event?
5. (Long-term) Implement RawHit.
6. (Long-term) Implement SimRawHit.

## EventDisplay

## Geometry

### Utility

1. CDC cell's sensitive volume should be a cylinder instead of parallepipe. This behaviour is now act in SD as an if(...), draw it down directly in geometry is simpler.
2. CDC cells and layers transform and size (and layerId for cells) list should be constructed in description.
3. (Completed) ~~In geometry hierarchy, solenoid and field volume is at the same level. Maybe the field as solenoid's mother is better.~~ (Note: fixed a lot of "stuck")
4. (Cancelled) ~~Like above, but for shields.~~
5. (Cancelled) ~~Add a geometry constructor for universial usage.~~
6. (Ongoing) Consider location constraints. E.g. solenoid has exactly the same length as the corresponding field, down-stream field is connect to the up-stream field, etc. Benefits for dynamic geometry.

### Interface

1. Update description interface for pure G4 geometry usage.

## ReconSpectrometer

### Utility

1.

### Interface

1. Keep the status quo.

## SimCalorimeter

## SimMACE

### Physics

1. Add decay: u->eeevv, together with muonium and anti-muonium.
2. Add muon/muonium/anti-muonium decay with spin, review code from musr.
3. Review MuoniumDecayChannel/AntiMuoniumDecayChannel.
4. Better and modern implementation of MuoniumTransport. See also SimMTransport.
5. Investigate parameterisation and fast simulation interface of G4.

### Messengers

1. Dynamic geometry. Need geometry messenger and other supports. Geometry messenger hold a DetectorConstruction and sets entities. Implement geometry messenger as a single class is ok.
2. More physics options. E.g. control rest muon electron capture probability (using exp(.)'s CDF), adjust decay mode, muonium transport parameters, etc.

### Primary Generator

1. Time structure of bunch?
2. Correct momentum. Using degrader to slow muon down.

### Other

1. Note: now, as fast simulation, MCP may not annihilate e+ but scatter it back instead. In this case, calorimeter will not detect annihilate photons.

### Coding Style

1. More inline namespaces.

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

## Other

1. (Ongoing) Better CMakeLists coding.
2. (Ongoing) Use C++20 feature.
3. (Completed) ~~Suppress all of -Wall and -Wextra warnings (excluding ThirdParty).~~
