# MACE offline software system

[![GitHub License](https://img.shields.io/github/license/zhao-shihan/MACESW?color=red)](COPYING)
![GitHub Created At](https://img.shields.io/github/created-at/zhao-shihan/MACESW?color=green)
![GitHub top language](https://img.shields.io/github/languages/top/zhao-shihan/MACESW?color=f34b7d)
[![GitHub activity](https://img.shields.io/github/commit-activity/m/zhao-shihan/MACESW)](https://github.com/zhao-shihan/MACESW/pulse)
![GitHub last commit](https://img.shields.io/github/last-commit/zhao-shihan/MACESW)
![GitHub repo size](https://img.shields.io/github/repo-size/zhao-shihan/MACESW)

[![Build (AMD64 GNU/Linux GCC)](https://github.com/zhao-shihan/MACESW/actions/workflows/build-with-gcc.yml/badge.svg)](https://github.com/zhao-shihan/MACESW/actions/workflows/build-with-gcc.yml)
[![Build (AMD64 GNU/Linux Clang, unity build)](https://github.com/zhao-shihan/MACESW/actions/workflows/build-with-clang.yml/badge.svg)](https://github.com/zhao-shihan/MACESW/actions/workflows/build-with-clang.yml)

[![Regression test (AMD64 GNU/Linux GCC)](https://github.com/zhao-shihan/MACESW/actions/workflows/regression-test-with-gcc.yml/badge.svg)](https://github.com/zhao-shihan/MACESW/actions/workflows/regression-test-with-gcc.yml)
[![Regression test (AMD64 GNU/Linux Clang, unity build)](https://github.com/zhao-shihan/MACESW/actions/workflows/regression-test-with-clang.yml/badge.svg)](https://github.com/zhao-shihan/MACESW/actions/workflows/regression-test-with-clang.yml)

- [MACE offline software system](#mace-offline-software-system)
  - [Introduction](#introduction)
  - [How to build](#how-to-build)
    - [For basic users: Build with RGB image](#for-basic-users-build-with-rgb-image)
      - [1. Install Apptainer](#1-install-apptainer)
      - [2. Download RGB image](#2-download-rgb-image)
      - [3. Build MACESW](#3-build-macesw)
      - [4. Run MACESW](#4-run-macesw)
    - [For advanced users or developers: Build from scratch](#for-advanced-users-or-developers-build-from-scratch)
      - [Toolchain Requirements](#toolchain-requirements)
      - [Dependencies](#dependencies)
  - [Cite](#cite)
    - [Major citations](#major-citations)
    - [Literatures list (sort by disclosure date)](#literatures-list-sort-by-disclosure-date)

## Introduction

<img src="document/picture/MACE_logo_v2.svg" alt="MACE logo" width="300" 
     style="float: right; margin: 15px 0px 15px 20px;">

The **Muonium-to-Antimuonium Conversion Experiment (MACE)** is a next-generation particle physics experiment designed to search for the spontaneous conversion of muonium ($\mathrm{M}$, a bound state of $\mu^+$ and $e^-$) to antimuonium ($\overline{\mathrm{M}}$, a bound state of $\mu^-$ and $e^+$)—a charged lepton flavor violation (cLFV) process. Observing this rare conversion would provide clear evidence of new physics beyond the Standard Model, with implications for understanding neutrino masses, matter-antimatter asymmetry, and other fundamental phenomena.

The MACE offline software system (MACESW) provides comprehensive support for the experiment's full lifecycle—from simulation and reconstruction to data analysis—enabling high-precision studies of muonium-to-antimuonium conversion and related physics researches.

MACESW is developed based on the [Mustard framework](https://github.com/zhao-shihan/Mustard).

## How to build

### For basic users: Build with [RGB](https://github.com/zhao-shihan/RGB) image

The recommended approach for basic user to build MACESW is using the RGB Apptainer/Docker image, which contains all necessary dependencies.

#### 1. Install Apptainer

Download and install Apptainer from the [official releases](https://github.com/apptainer/apptainer/releases). For Debian-based systems:
```bash
# Replace the version as needed; see the Apptainer releases page for the latest version and links
wget https://github.com/apptainer/apptainer/releases/download/v1.4.3/apptainer_1.4.3_amd64.deb -O apptainer.deb
sudo apt install ./apptainer.deb
```

#### 2. Download RGB image

Pull the RGB Apptainer image:
```bash
apptainer pull oras://ghcr.io/zhao-shihan/rgb
```
This creates an image file `rgb.sif` in your current directory.

#### 3. Build MACESW

Start an interactive shell within the RGB image:
```bash
apptainer shell ./rgb.sif
```
(Note that opening a shell is not necessary, you can also run something with the image by `./rgb.sif <command>`, but here we work inside the container shell for simplicity)

Then, in the container shell, clone and build MACESW:
```bash
git clone https://github.com/zhao-shihan/MACESW.git
cd MACE
mkdir build && cd build
cmake ..
make -j8
```

#### 4. Run MACESW

After successful compilation, test the executable:
```bash
./MACE --help
```

### For advanced users or developers: Build from scratch

For advanced users or developers building from source or contributing to MACESW:

#### Toolchain Requirements

- **C++ Compiler**: GCC ≥ 13 or LLVM Clang ≥ 16 (C++20 support required)
- **C++ Standard Library**: libstdc++ ≥ 13 or equivalent
- **Build System**: CMake ≥ 3.21 with GNU Make or Ninja

#### Dependencies

Required external libraries (via [Mustard](https://github.com/zhao-shihan/Mustard)):

1. [Eigen](https://eigen.tuxfamily.org/) ≥ 3.4.0
2. [Geant4](https://geant4.org/) ≥ 11.0.0 (with GDML support)
3. [ROOT](https://root.cern/) ≥ 6.30.00 (with GDML support)
4. [MPI](https://www.mpi-forum.org/) ≥ 3.1 (MPICH, OpenMPI, or equivalent)

Optional built-in dependencies (automatically downloaded if not found):

1. [Mustard](https://github.com/zhao-shihan/Mustard) ≥ 0.25.1015
2. [zhao-shihan/GenFit](https://github.com/zhao-shihan/GenFit)
3. [PMP Library](https://www.pmp-library.org/) ≥ 3.0.0
4. [MACE Offline Data](https://code.ihep.ac.cn/zhaoshh7/mace_offline_data)

## Cite

### Major citations

**If you use MACESW, please cite the following papers**:

- **BAI Ai-Yu, CAI Hanjie, CHEN Chang-Lin, et al (MACE working group). Conceptual Design of the Muonium-to-Antimuonium Conversion Experiment (MACE) [DB/OL]. arXiv preprint, 2024: 2410.18817 [hep-ex]. https://arxiv.org/abs/2410.18817.**

### Literatures list (sort by disclosure date)

- LU Guihao, ZHAO Shihan, CHEN Siyuan, et al. Positron Transport System for Muonium-to-Antimuonium Conversion Experiment [DB/OL]. arXiv preprint, 2025: 2508.07922 [hep-ex]. https://arxiv.org/abs/2508.07922.
- AN FengPeng, BAI Dong, CHEN Siyuan, et al. High-Precision Physics Experiments at Huizhou Large-Scale Scientific Facilities [DB/OL]. arXiv preprint, 2025: 2504.21050 [hep-ph]. https://arxiv.org/abs/2504.21050.
- BAI Ai-Yu, CAI Hanjie, CHEN Chang-Lin, et al. Conceptual Design of the Muonium-to-Antimuonium Conversion Experiment (MACE) [DB/OL]. arXiv preprint, 2024: 2410.18817 [hep-ex]. https://arxiv.org/abs/2410.18817.
- CHEN Siyuan, ZHAO Shihan, XIONG Weizhi, et al. Design of a CsI(Tl) calorimeter for muonium-to-antimuonium conversion experiment [J]. Front. Phys., 2025, 20: 035202. DOI: 10.15302/frontphys.2025.035202. arXiv: 2408.17114 [physics.ins-det]. https://doi.org/10.15302/frontphys.2025.035202.
- ZHAO Shihan, TANG Jian. Progress of muonium-to-antimuonium conversion experiment [J]. Nucl. Part. Phys. Proc., 2024, 345: 24-28. DOI: 10.1016/j.nuclphysbps.2024.05.005. https://doi.org/10.1016/j.nuclphysbps.2024.05.005.
- CORRODI S., OKSUZIAN Y., EDMONDS A., et al. Workshop on a future muon program at FNAL [C]. arXiv preprint, 2023: 2309.05933 [hep-ex]. https://arxiv.org/abs/2309.05933.
- BAI Ai-Yu, CHEN Yu, CHEN Yukai, et al. Snowmass2021 Whitepaper: Muonium to Antimuonium Conversion [DB/OL]. arXiv preprint, 2022: 2203.11406 [hep-ph]. https://arxiv.org/abs/2203.11406.
