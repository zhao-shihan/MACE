/***************************************************************************
 *  musrSim - the program for the simulation of (mainly) muSR instruments. *
 *          More info on http://lmu.web.PSIMACE.ch/simulation/index.html .     *
 *          musrSim is based od Geant4 (http://geant4.web.cern.ch/geant4/) *
 *                                                                         *
 *  Copyright (C) 2009 by Paul Scherrer Institut, 5232 Villigen PSIMACE,       *
 *                                                       Switzerland       *
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program; if not, write to the Free Software            *
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              *
 ***************************************************************************/
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//  Muonium yields as a function of initial mu+ energies.
//          The method GetYields is used by MuFormation.
//  Id    : yields.cc, v 1.1
//  Author: Taofiq PARAISO, T. Shiroka
//  Date  : 2007-12
//  Notes : First implemented in Fortran by A. Hofer
//          C++ conversion by T.K. Paraiso 04-2005
//          Slight modifications by T. Shiroka
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#include "physics/yields.hh"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <stdlib.h>

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 The Muonium Yield function as well as the parameters are taken from:
 M. Gonin, R. Kallenbach, P. Bochsler: "Charge exchange of hydrogen atoms
 in carbon foils at 0.4 - 120 keV", Rev.Sci.Instrum. 65 (3), March 1994
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

Yields:: Yields(){;}
Yields::~Yields(){;}

void Yields::GetYields(
       double E,          // kinetic energy in keV
       double mass,       // mass in keV/c**2
       double yvector[3]) // pointer to the yields table

{
  // Parameter NAMES  for the muonium yield function
  double a_zero, a_minus;
  double k_Fermi, k_zero, k_minus;
  double two_k_Fermi;
  double k_Fermi_Quad, k_zero_Quad, k_minus_Quad;
  double vc_minus, vc_plus, v_Bohr, v_rel;

  // Parameter VALUES for the muonium yield function
  a_zero   = 0.953;
  a_minus  = 0.029;
  k_Fermi  = 1.178;                 // [v_Bohr]
  k_Fermi_Quad = k_Fermi * k_Fermi;
  two_k_Fermi  = 2. * k_Fermi;
  k_zero       = 0.991*k_Fermi;     // [v_Bohr]
  k_zero_Quad  = k_zero * k_zero;
  k_minus      = 0.989*k_Fermi;     // [v_Bohr]
  k_minus_Quad = k_minus * k_minus;
  vc_minus = 0.284;
  vc_plus  = 0.193;                 // [v_Bohr]
  v_Bohr   = 7.2974E-3;             // [c]


  // std::cout<<"E = "<< E <<std::endl;

  // Abort in case of negative energies ---------------------------
  if (E < 0)
    {
      std::cout<< "Error in method ''Yields'':" <<std::endl;
      std::cout<< "E = "<< E <<" < 0!" <<std::endl;
      std::cout<< "-> ABORTED!" <<std::endl;
      return;
    }
  //---------------------------------------------------------------



  // Definition of variables (aux_n are some auxiliary variables)
  // Calculate energy in (classical) terms of speed (in units of v_Bohr):

  v_rel = sqrt(2.*E/mass)/ v_Bohr;

  aux1 = v_rel*v_rel;
  aux2 = two_k_Fermi*v_rel;
  Q_zero  = 1. + (k_zero_Quad  - k_Fermi_Quad - aux1) / aux2;
  Q_minus = 1. + (k_minus_Quad - k_Fermi_Quad - aux1) / aux2;

  aux1 = a_zero * Q_zero;
  aux2 = a_minus * Q_minus;
  aux3 = (1.-Q_zero)*(1.-Q_minus);
  D = aux1*(aux2 + (1.-Q_minus)) + aux3;

  Yield_minus = aux1*aux2 / D;
  Yield_plus  = aux3 / D;

  Yield_minus = Yield_minus* exp(-vc_minus/v_rel);
  Yield_plus  = Yield_plus * exp(-vc_plus /v_rel);

  if(Yield_minus > exp(-vc_minus/v_rel)) Yield_minus=exp(-vc_minus/v_rel);
  if(Yield_plus  > exp(-vc_plus/v_rel))  Yield_plus=exp(-vc_plus/v_rel);

  Yield_zero  = 1. - (Yield_minus + Yield_plus);

  yvector[0]=Yield_plus;
  yvector[1]=Yield_zero;
  yvector[2]=Yield_minus;

  // std::cout<<"Y+ : "<< Yield_plus << std::endl;
  // std::cout<<"Y0 : "<< Yield_zero << std::endl;
}
