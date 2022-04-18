# MACE

<img align="right" src="document/picture/MACE_logo_100x100.png"/>

- [MACE](#mace)
  - [Introduction](#introduction)
  - [How to Build](#how-to-build)
    - [External dependencies](#external-dependencies)
    - [(Tested) Platform](#tested-platform)
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

0. C/C++ compiler that supports ≥ C++20. (gcc-10/11 recommended)
1. CMake   (≥ 3.16)
2. MPI-3   (MPICH, OpenMPI, Intel MPI, etc. On your frequency.)
3. Geant4  (≥ 4.11.0, with ≥ C++17, gdml enabled)
4. ROOT    (≥ 6.24.02, ≥ C++17)
5. Eigen3  (≥ 3.3.0)

G4mpi, yaml-cpp is bulit in. (in ./external)  

### (Tested) Platform

Linux with gcc10, gcc11

### Prepare for your PC  

Geant4 and ROOT can be installed on your PC following the official guides. They should be built at least with C++17.  
On your PC, MPI-3 and Eigen3 can be installed via package manager (apt, yum, etc.) respect to your linux distrbution. For example, you can install MPICH and Eigen3 on Ubuntu with

```shell
sudo apt update
sudo apt install mpich libeigen3-dev
```

### Prepare for cluster/supercomputer  

You cannot work as root in most case, which means package manager won't work. Thus, you might use MPI-3 and Eigen3 pre-installed on the cluster/supercomputer. That's great if they provides both, but in most scene MPI-3 is pre-installed while Eigen3 not. In this case just install Eigen3 manually.

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
