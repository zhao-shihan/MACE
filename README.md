# MACE

## Introduction

This software is designed for MACE experiment. For now, it is mainly used for designing the experiment.  
MACE software are made up of several modules, including SimMACE, SimMTransport, ReconSpectrometer, Geometry, and DataModel. SimMACE is used for the simulation of whole experiment. SimMTransport handles the muonium transport in target after formed, and is used in SimMACE as a physics process. SimMTransport can also be run independently to calculate the yield of target, see it's README for detail. ReconSpectrometer handles the track reconstruction in the spectrometer. Geometry handles the construction of detector geometry, which provides a universial interface of detector geometry. DataModel provides a interface of datamodel for each detector, which is transportable between modules.

## How to Build

To build MACE software from source, there are a few prerequisites.

### External dependencies:  
MPI-3   (MPICH, OpenMPI, Intel MPI, etc. On your frequency.)  
Geant4  (min: 4.11.0, with C++17, and gdml enabled)  
ROOT    (min: 6.24.02, C++17)  
Eigen3  

G4mpi is bulit in. (in ./ThirdParty)    

### (Tested) Platform:  
Linux, with gcc(9,10,11)

### Prepare for your PC:  
Geant4 and ROOT can be compiled and installed on your computer following the official installation guides. They should be compiled against C++17 standard.  
MPI-3 and Eigen3 can also be installed via package manager (apt, yum, etc.) respect to your linux distrbution. For example, you can install MPICH and Eigen3 on Ubuntu with
```shell
sudo apt update
sudo apt install mpich libeigen3-dev
```

### Prepare for cluster/supercomputer:  
In most case, you do not have root privilege, thus you should always consider using MPI-3 and Eigen3 pre-installed on the cluster/supercomputer. Else, install MPI-3 and Eigen3 manually. Install Eigen3 is rather easy, because it is a template library which is header-only. Install MPI-3 you need to follow the official instruction.  

### Build

After everything prepared, it's time to build.  

MACE software follows a classical cmake & make procedure, as
```shell
mkdir build
cmake <MACE_ROOT_DIR>
make
```
Using ninja or other make tools is also OK, respect to your preference.  
Notice: MACE is compiled against C++17, which is configured directly in ./CMakeLists.txt, your -DCMAKE_CXX_STANDARD flag may not work. Other C++ standard is not supported or tested, we might do that later.  

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
Note that N=1 or without mpirun is not supported, because there is always a master process. We think that not matter much though, if there are any problem, just contact us and we can figure it out.

### Geometry
Just
```shell
./MakeGeometry
```
This is mainly used for test. A gdml file and a root file will be generated and you can keep it for another purpose. Be note that SimMACE use this module internally, which means you need not to import gdml into SimMACE manually, we already do that.

### Datamodel
No standalone executable file for this module. It appears nowhere, it appears everywhere.

### ReconSpectrometer
Run as
```shell
./ReconSpectrometer SimMACEResult.root
```
Development in progess.