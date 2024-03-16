# MACE

<img align="right" src="document/picture/MACE_logo_100x100.png"/>

- [MACE](#mace)
- [Pre-built binaries](#pre-built-binaries)
- [Dependencies](#dependencies)
  - [Toolchain](#toolchain)
  - [Libraries](#libraries)
- [Cite](#cite)

![SimMACE](document/picture/SimMACE_20240315.png)

# Pre-built binaries

Pre-built, optimized binaries are available through [Apptainer](https://apptainer.org/) (formerly known as Singularity).

Obtain the apptainer image file (.sif) by
```shell
apptainer pull oras://docker.io/zhaoshh/mace:mpich
```
or
```shell
apptainer pull oras://docker.io/zhaoshh/mace:openmpi
```
depending on the MPI implementation you are using.
For more information, please check out [the image repository homepage](https://hub.docker.com/r/zhaoshh/mace).

# Dependencies

## Toolchain

1. A C++ compiler (that supports ≥ C++20. [GCC](https://gcc.gnu.org/) ≥ 12, [LLVM Clang](https://clang.llvm.org/) ≥ 15, or MSVC ≥ 19.30 (i.e., [Visual Studio](https://visualstudio.microsoft.com/) 2022 ≥ 17.0))
2. A C++ library (that supports ≥ C++20. [libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/) ≥ 12, or [MSVC STL](https://github.com/microsoft/STL) with [Visual Studio](https://visualstudio.microsoft.com/) 2022 ≥ 17.0)
3. [CMake](https://cmake.org/) (≥ 3.16)
4. A build system compatible with CMake ([GNU Make](https://www.gnu.org/software/make/), [Ninja](https://ninja-build.org), or etc.)

## Libraries

Required:

1. [MPI](https://www.mpi-forum.org/) (≥ 3.0, [MPICH](https://www.mpich.org/), [OpenMPI](https://www.open-mpi.org/), [Intel MPI](https://www.intel.cn/content/www/cn/zh/developer/tools/oneapi/mpi-library.html), [Microsoft MPI](https://github.com/Microsoft/Microsoft-MPI), etc. On your frequency)
2. [Eigen](https://eigen.tuxfamily.org/) (≥ 3.4.0)
3. [Geant4](https://geant4.web.cern.ch/) (≥ 11.0.0, with GDML support)
4. [ROOT](https://root.cern/) (≥ 6.30.00)

Required, built-in if not found (network or pre-downloaded source is required):

1. [argparse](https://github.com/p-ranav/argparse) (≥ 2.6, built-in if not found)
2. [backward-cpp](https://github.com/bombela/backward-cpp) (≥ 1.6, built-in if not found)
3. [fmt](https://github.com/fmtlib/fmt) (≥ 10.0.0, built-in if not found)
4. [zhao-shihan/GenFit](https://github.com/zhao-shihan/GenFit) (a GenFit fork, built-in if not found)
5. [Microsoft.GSL](https://github.com/Microsoft/GSL) ([ISO C++ guidelines support library](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#gsl-guidelines-support-library)) (≥ 4.0.0, built-in if not found)
6. [PMP](https://www.pmp-library.org/) (Polygon Mesh Processing Library) (≥ 3.0.0, built-in if not found)
7. [yaml-cpp](https://github.com/jbeder/yaml-cpp) (≥ 0.8.0, built-in if not found)

# Cite

1. [A.-Y. Bai et al. (MACE working group), Snowmass2021 Whitepaper: Muonium to antimuonium conversion, in 2022 Snowmass Summer Study (2022), arXiv:2203.11406.](https://arxiv.org/abs/2203.11406)
2. [Shihan Zhao and Jian Tang, Optimization of muonium yield in perforated silica aerogel, arXiv:2401.00222.](https://arxiv.org/abs/2401.00222)
