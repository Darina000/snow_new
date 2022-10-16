#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include"SensitiveDetector.hh"
#include "G4SystemOfUnits.hh"

using namespace std;

SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name),
						     HIST_MAX(100*MeV),
						     HIST_MIN(10 *keV)
{
//  for(int i = 0; i<NOBINS; i++)
 //   histogram[i] = 0;
}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{
    
    
    G4ThreeVector direction = step->GetTrack()->GetMomentumDirection();
    G4ThreeVector position =  step->GetTrack() -> GetPosition();
    
    G4double energy = step->GetTrack()->GetKineticEnergy();
    //G4double x = (aTrack->GetPosition()).x();
    //G4double y = (aTrack->GetPosition()).y();
    G4double z = (step->GetTrack()->GetPosition()).z();
    
    

    G4int trackID  = step->GetTrack()->GetTrackID();
    G4int parentID =step->GetTrack()->GetParentID();
    G4String name = step->GetTrack()->GetDefinition()->GetParticleName();
    
//    if (energy/CLHEP::MeV > 1){
        
        cout << name  << " z/m " <<  z/m<< G4endl;
        std::ofstream outf("all_run1kElect5MeV_yach200_field200ac_10k_snow_R1cm_1.csv", std::ios::app);
        outf <<  name <<  " z/m " <<  z/m << " energy/CLHEP::keV " <<  energy/CLHEP::keV << std::endl;
  //  }

    //G4int trackID  = aTrack->GetTrackID();
   // G4int parentID = aTrack->GetParentID();

    /*
    cout << name << " name " << " z/m " <<  z/m<< G4endl;
    
    if (name == "e-" ){
        /*
        std::ofstream outf("rungamma4MeV_400_field500_p4_electron_start_progon11.mac", std::ios::app);
        outf << "/gun/particle " << name  << std::endl;
        outf << "/gun/direction " << direction.x() << " " << direction.y()  << " " << direction.z() << std::endl;
        outf << "/gun/position " << position.x()  << " " << position.y() << " "  <<  10 << " mm" << std::endl;
        outf << "/gun/energy " << energy/CLHEP::MeV << " MeV"<< std::endl;
        outf << "/run/beamOn 1"<< std::endl;

        
        std::ofstream ou("r_e4MeV_200_f500.mac", std::ios::app);
        ou << name  << " "  << energy << std::endl;
    }
    
    */
    
    
// double energy = step->GetTrack()->GetDynamicParticle()->GetTotalEnergy();
  //double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
//  int index = int(floor((energy-HIST_MIN)/bin_width));
//  if(index >= 0 && index < NOBINS)
 //   histogram[index]++;

//  step->GetTrack()->SetTrackStatus(fStopAndKill);
  return true;
}


void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}



SensitiveDetector::~SensitiveDetector()
{
  //std::ofstream file("spectrum.dat");
  
  //double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
//  for(int i = 0; i<NOBINS; i++)
//  {
 //   double energy = i*bin_width + HIST_MIN;
//    file << std::setw(15) << energy/MeV << " "
//	 << std::setw(15) << histogram[i] << std::endl;
//  }
}
