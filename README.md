# MACE

<img align="right" width="100" height="100" src="doc/pics/MACE_logo.png"/>

  - [Introduction](#introduction)
  - [How to Build](#how-to-build)
    - [External dependencies](#external-dependencies)
    - [(Tested) Platform](#tested-platform)
    - [Prepare for your PC](#prepare-for-your-pc)
    - [Prepare for cluster/supercomputer](#prepare-for-clustersupercomputer)
    - [Build](#build)
  - [How to Run](#how-to-run)
    - [SimMACE](#simmace)
    - [SimMTransport](#simmtransport)
    - [SimCalorimeter](#simcalorimeter)
    - [SimSpectrometer](#simspectrometer)
    - [ReconSpectrometer](#reconspectrometer)
    - [Geometry](#geometry)
    - [Datamodel](#datamodel)

## Introduction

This software is designed for MACE experiment.  
MACE software consists of several modules: SimMACE, SimMTransport, ReconSpectrometer, Geometry, DataModel. "SimMACE" is designed for the simulation of the whole experiment. "SimMTransport" handles the transport of muonium in target after produced, as a physics process in SimMACE. "SimMTransport" can be run independently aim at calculate the yield of a target, see it's README for detail. "ReconSpectrometer" handles track reconstruction in the spectrometer. "Geometry" handles the construction of detector geometry, provides a universial interface of detector geometry. "DataModel" provides a interface for datamodel of each detector, transportable between modules.

![SimMACE](doc/pics/MACE_sim.png)

## How to Build

To build MACE software from source, there are a few prerequisites.

### External dependencies

0. C/C++ compiler that supports ≥ C++20.
1. CMake   (≥ 3.16)
2. MPI-3   (MPICH, OpenMPI, Intel MPI, etc. On your frequency.)
3. Geant4  (≥ 4.11.0, with ≥ C++17, gdml enabled)
4. ROOT    (≥ 6.24.02, ≥ C++17)
5. Eigen3  (≥ 3.3.9)

G4mpi is bulit in. (in ./ThirdParty)  

### (Tested) Platform

Linux with gcc10, gcc11

### Prepare for your PC  

Geant4 and ROOT can be compiled and installed on your PC following the official guides. They should be compiled at least with C++17.  
On your PC, MPI-3 and Eigen3 can be installed via package manager (apt, yum, etc.) respect to your linux distrbution. For example, you can install MPICH and Eigen3 on Ubuntu with

```shell
sudo apt update
sudo apt install mpich libeigen3-dev
```

### Prepare for cluster/supercomputer  

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
