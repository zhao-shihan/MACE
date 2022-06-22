# MACE

<img align="right" src="document/picture/MACE_logo_100x100.png"/>

- [MACE](#mace)
  - [Introduction](#introduction)
  - [How to Build](#how-to-build)
    - [External dependencies](#external-dependencies)
    - [Prepare for your PC](#prepare-for-your-pc)
    - [Prepare for cluster/supercomputer](#prepare-for-clustersupercomputer)
    - [Build](#build)
  - [How to Run](#how-to-run)
    - [SimMACE](#simmace)
    - [SimTarget](#simtarget)
    - [ReconTracks](#recontracks)

## Introduction

This software is designed for MACE experiment. It consists of several modules: Core, Reconstruction, Simulation, and Utility. The "Simulation" module implements the simulation part of the experiment based on GEANT4, including the simulation of the whole experiment (SimMACE) and the simulation of each subsystem (SimEMCal, SimMCP, SimCDC, etc.). The "Reconstruction" module implements the event reconstruction of the experiment. The "Core" module includes three sub modules: "Datamodel", "Geometry" and "Field", which implement the event data model required by mace (and the interface required for expansion), detector geometry, and electromagnetic field, respectively. The "Utility" module provides some common practicle tools that may be used in programming.

![SimMACE](document/picture/MACE_sim.png)

## How to Build

To build MACE software from source, there are a few prerequisites.

### External dependencies

Required:

1. C/C++ compiler that supports ≥ C++20. ([GCC](https://gcc.gnu.org/) ≥ 10, [Clang](https://clang.llvm.org/) ≥ 10, MSVC ≥ 19.30 ([Visual Studio](https://visualstudio.microsoft.com/) 2022))
2. [CMake](https://cmake.org/) (≥ 3.16)
3. [MPI](https://www.mpi-forum.org/) (≥ 2.0, [MPICH](https://www.mpich.org/), [OpenMPI](https://www.open-mpi.org/), [Intel MPI](https://www.intel.cn/content/www/cn/zh/developer/tools/oneapi/mpi-library.html), [Microsoft MPI](https://github.com/Microsoft/Microsoft-MPI), etc. On your frequency)
4. [Geant4](https://geant4.web.cern.ch/) (≥ 4.11.0, with ≥ C++17)
5. [ROOT](https://root.cern/) (≥ 6.24.02, ≥ C++17)

Required, built-in if not found:

1. Geant4::G4gdml (Geant4 optional component, built-in if not found)
2. [Eigen](https://eigen.tuxfamily.org/) (≥ 3.3.0, built-in if not found (network or pre-downloaded source is required))
3. [yaml-cpp](https://github.com/jbeder/yaml-cpp) (≥ 0.6.0, built-in if not found (network or pre-downloaded source is required))
4. [Xerces-C++](https://xerces.apache.org/xerces-c/) (not required if G4gdml is not required, ≥ 3.2.0, built-in if not found (network or pre-downloaded source is required))

### Prepare for your PC  

Geant4 and ROOT can be installed on your PC following the official guides. They should be built at least with C++17.  
On your PC, MPI and Eigen can be installed via package manager (apt, yum, etc.) respect to your linux distrbution. For example, you can install MPICH and Eigen on Ubuntu with

```shell
sudo apt update
sudo apt install mpich libeigen3-dev
```

### Prepare for cluster/supercomputer  

You cannot work as root in most case, which means package manager won't work. Thus, you might use MPI and Eigen pre-installed on the cluster/supercomputer. That's great if they provides both, but in most scene MPI is pre-installed while Eigen not. In this case just install Eigen manually.

### Build

After everything prepared, it's time to build.  

MACE software follows a classical cmake & make procedure, as

```shell
mkdir build
cd build
cmake <MACE_PROJECT_ROOT_DIR>
make
```

That's ok to use ninja or other make tools, respect to your preference.  

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

### SimTarget



### ReconTracks

Run as

```shell
./ReconTracks SimMACEResult.root <...>
```

(Development in progess.)
