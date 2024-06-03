#!/bin/bash

V=pen-5cm
echo "$V is running..."
cd ~/work/mace/$V/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun ./SimMACEPhaseI test.mac
hadd -ff $V.root typePEN/*.root
mv $V.root ~/work/mace/lengthTest

V=pen-6cm
echo "$V is running..."
cd ~/work/mace/$V/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun ./SimMACEPhaseI test.mac
hadd -ff $V.root typePEN/*.root
mv $V.root ~/work/mace/lengthTest

V=pen-7cm
echo "$V is running..."
cd ~/work/mace/$V/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun ./SimMACEPhaseI test.mac
hadd -ff $V.root typePEN/*.root
mv $V.root ~/work/mace/lengthTest

V=pen-8cm
echo "$V is running..."
cd ~/work/mace/$V/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun ./SimMACEPhaseI test.mac
hadd -ff $V.root typePEN/*.root
mv $V.root ~/work/mace/lengthTest

V=pen-9cm
echo "$V is running..."
cd ~/work/mace/$V/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun ./SimMACEPhaseI test.mac
hadd -ff $V.root typePEN/*.root
mv $V.root ~/work/mace/lengthTest

V=pen-10cm
echo "$V is running..."
cd ~/work/mace/$V/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun ./SimMACEPhaseI test.mac
hadd -ff $V.root typePEN/*.root
mv $V.root ~/work/mace/lengthTest

echo "All simulations are done!"