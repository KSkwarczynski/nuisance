// Copyright 2016-2021 L. Pickering, P Stowell, R. Terri, C. Wilkinson, C. Wret

/*******************************************************************************
*    This file is part of NUISANCE.
*
*    NUISANCE is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    NUISANCE is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with NUISANCE.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "MINERvA_SignalDef.h"

#include "MINERvA_CCCOHPI_XSec_1DEpi_nu.h"


//********************************************************************
MINERvA_CCCOHPI_XSec_1DEpi_nu::MINERvA_CCCOHPI_XSec_1DEpi_nu(nuiskey samplekey) {
//********************************************************************

  // Sample overview ---------------------------------------------------
  std::string descrip = "MINERvA_CCCOHPI_XSec_1DEpi_nu sample. \n" \
                        "Target: CH \n" \
                        "Flux: MINERvA Forward Horn Current numu \n" \
                        "Signal: Any event with 1 mu-, 1pi+, and no other FS particles \n";

  // Setup common settings
  fSettings = LoadSampleSettings(samplekey);
  fSettings.SetDescription(descrip);
  fSettings.SetXTitle("E_{#pi} (GeV)");
  fSettings.SetYTitle("d#sigma/dE_{#pi} (cm^{2}/GeV/C^{12})");
  fSettings.SetAllowedTypes("FIX,FREE,SHAPE/DIAG,FULL/NORM/MASK", "FIX/FULL");
  fSettings.SetEnuRange(1.5, 20.0);
  fSettings.DefineAllowedTargets("C,H");
  fSettings.DefineAllowedSpecies("numu");
  fSettings.SetTitle("MINERvA_CCCOHPI_XSec_1DEpi_nu");

  fSettings.SetDataInput( GeneralUtils::GetTopLevelDir() + "/data/MINERvA/CCcoh/Epi_nu_data.csv");
  fSettings.SetCovarInput(GeneralUtils::GetTopLevelDir() + "/data/MINERvA/CCcoh/Epi_nu_cov.csv");
			   
  FinaliseSampleSettings();

  // Scaling Setup ---------------------------------------------------
  // ScaleFactor automatically setup for DiffXSec/cm2/Nucleon
  fScaleFactor = GetEventHistogram()->Integral("width") * double(1E-38) / double(fNEvents)/TotalIntegratedFlux("width")*13;
   
  // Plot Setup -------------------------------------------------------
  SetDataFromTextFile( fSettings.GetDataInput() );
  SetCovarFromMultipleTextFiles(fSettings.GetCovarInput());

  // Final setup  ---------------------------------------------------
  FinaliseMeasurement();
};


void MINERvA_CCCOHPI_XSec_1DEpi_nu::FillEventVariables(FitEvent *event) {

  if (event->NumFSParticle(211) == 0) return;

  TLorentzVector Ppi = event->GetHMFSParticle(211)->fP;
  fXVar = Ppi.E()/1000.;

  return;
};

//********************************************************************
bool MINERvA_CCCOHPI_XSec_1DEpi_nu::isSignal(FitEvent *event) {
//********************************************************************
  // Signal: numu + 12C --> mu- + pi+ + 12C'
  return SignalDef::isCCCOH(event, 14, 211, EnuMin, EnuMax);
}

