# MACE

## Introduction

This software is designed for MACE experiment. For now, it's for designing the experiment.  
MACE software consists of several modules: SimMACE, SimMTransport, ReconSpectrometer, Geometry, DataModel. "SimMACE" is designed for the simulation of the whole experiment. "SimMTransport" handles the transport of muonium in target after produced, as a physics process in SimMACE. "SimMTransport" can be run independently aim at calculate the yield of a target, see it's README for detail. "ReconSpectrometer" handles track reconstruction in the spectrometer. "Geometry" handles the construction of detector geometry, provides a universial interface of detector geometry. "DataModel" provides a interface for datamodel of each detector, transportable between modules.

## How to Build

To build MACE software from source, there are a few prerequisites.

### External dependencies:  
MPI-3   (MPICH, OpenMPI, Intel MPI, etc. On your frequency.)  
Geant4  (min: 4.11.0, with C++17, gdml enabled)  
ROOT    (min: 6.24.02, C++17)  
Eigen3  (min: 3.3.9)

G4mpi is bulit in. (in ./ThirdParty)  

### (Tested) Platform:  
Linux, with gcc(9,10,11)

### Prepare for your PC:  
Geant4 and ROOT can be compiled and installed on your PC following the official guides. They should be compiled against C++17.  
On your PC, MPI-3 and Eigen3 can be installed via package manager (apt, yum, etc.) respect to your linux distrbution. For example, you can install MPICH and Eigen3 on Ubuntu with
```shell
sudo apt update
sudo apt install mpich libeigen3-dev
```

### Prepare for cluster/supercomputer:  
You cannot work as root in most case, which means package manager won't work. Thus, you might use MPI-3 and Eigen3 pre-installed on the cluster/supercomputer. That's delightful if they provides both, but in most scene MPI-3 is pre-installed while Eigen3 not. In this case just install Eigen3 manually.

### Build
After everything prepared, it's time to build.  

MACE software follows a classical cmake & make procedure, as
```shell
mkdir build
cd build
cmake <MACE_ROOT_DIR>
make
```
That's ok to use ninja or other make tools, respect to your preference.  
Notice: MACE is compiled against C++17, configured forcibly in ./CMakeLists.txt. Your own -DCMAKE_CXX_STANDARD flag might not work. Be note that other C++ standard is not supported or tested, we might do that later.  

## How to Run

### SimMACE
In sequential mode with graphics:
```shell
./SimMACE
```
In sequential mode with a macro:
```shell
./SimMACE run.mac
```
In parallel mode with a macro:
```shell
mpirun -n N ./SimMACE run.mac
```

### SimMTransport
With a configuation file sample.cfg, parallely:
```shell
mpirun -n N ./SimMTransport sample.cfg
```
Note that N=1 or without mpirun is not supported, because there should always a master process.

### SimCalorimeter
(Development in progess.)

### SimSpectrometer
(Development in progess.)

### ReconSpectrometer
Run as
```shell
./ReconSpectrometer SimMACEResult.root <...>
```
(Development in progess.)

### Geometry
Just
```shell
./MakeGeometry
```
This is mainly used for test. A gdml file and a root file will be generated and you can keep it for another purpose. Be note that SimMACE use this module internally.

### Datamodel
No standalone executable file for this module. It appears nowhere, it appears everywhere.
