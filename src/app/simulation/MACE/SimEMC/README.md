# **G**amma-**RA**y **SP**ectrometer of **M**uonium-**A**ntimuonium **C**onvertion **E**xperiment (MACE-GRASP)

- [**G**amma-**RA**y **SP**ectrometer of **M**uonium-**A**ntimuonium **C**onvertion **E**xperiment (MACE-GRASP)](#gamma-ray-spectrometer-of-muonium-antimuonium-convertion-experiment-mace-grasp)
  - [Geometry Definition](#geometry-definition)
  - [Physics](#physics)
    - [Optical](#optical)
    - [Others](#others)
  - [Primary Generator](#primary-generator)
    - [Annihilation Gamma](#annihilation-gamma)
    - [Cosmic-ray Muon](#cosmic-ray-muon)
    - [Radioactive Source](#radioactive-source)
  - [How to Run](#how-to-run)
    - [In sequential mode with graphics](#in-sequential-mode-with-graphics)
    - [In parallel mode with a macro file](#in-parallel-mode-with-a-macro-file)
    - [ROOT file merging](#root-file-merging)
  - [References](#references)

## Geometry Definition
The GRASP is a spheroid detector formed by 162 CsI(Tl) scintillator units coupled with PMT.
`src/lib/detector/Mustard/Detector/Description/EMC.c++` where the parameters such as dimensions, optical properties and etc. can be initialized and modified, generate the GRASP's geometry definition.

## Physics
### Optical

### Others
## Primary Generator
### Annihilation Gamma
### Cosmic-ray Muon
### Radioactive Source
TBD.

## How to Run

### In sequential mode with graphics
```bash
./SimEMC
```
### In parallel mode with a macro file
```bash
mpirun -n N_THREAD ./SimEMC MACRO_NAME.mac
```

### ROOT file merging
```bash
hadd -ff ROOT_NAME.root PATH/*
```
## References

Data of *Material Composition*:
- https://geant4-userdoc.web.cern.ch/UsersGuides/AllGuides/html/index.html
- Detwiler R.S., R.J. McConn, T.F. Grimes, S.A. Upton, and E.J. Engel. 2021. Compendium of Material Composition Data for Radiation Transport Modeling Richland, WA: Pacific Northwest National Laboratory.

Data of *Isotopes*:
- https://www.chemlin.org/chemical-elements/isotopes.php

Optical properties of *Silicone Oil* and other potentially useful liquid
- Tonkyn, Russell G.; Danby, Tyler O.; Birnbaum, Jerome C.; Taubman, Matthew S.; Bernacki, Bruce E.;Johnson, Timothy J.; Myers, Tanya L., Measurement of infrared refractive indices of organic and organophosphorous compounds for optical modeling, Proc. SPIE 10183, Chemical, Biological, Radiological, Nuclear, and Explosives (CBRNE) Sensing XVIII, 1018306, May 3, 2017, https://doi.org/10.1117/12.2264384.

- Myers, Tanya L.; Tonkyn, Russell G.; Danby, Tyler O.; Taubman, Matthew S.; Bernacki, Bruce E.; Birnbaum, Jerome C.;Sharpe, Steven W.; Johnson, Timothy J., Accurate Measurement of the Optical Constants n and k for a Series of 57 Inorganic and Organic Liquids for Optical Modeling and Detection, Appl. Spectrosc., 2018, 72, 535-550, https://doi.org/10.1177/0003702817742848.

Optical properties of *CsI(Tl)* crystal:
- https://www.luxiumsolutions.com/radiation-detection-scintillators/crystal-scintillators/csi-cesium-iodide

Optical surface properites of scintillator *Reflective Coat*:
- M. Janecek, “Reflectivity Spectra for Commonly Used Reflectors,” IEEE Trans. Nucl. Sci., vol. 59, no. 3, pp. 490–497, Jun. 2012, https://10.1109/TNS.2012.2183385.

Data of *Photomultiplier Tube*:
- https://et-enterprises.com/products/photomultipliers/product/p9269b-series
