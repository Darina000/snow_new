#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include<G4Event.hh>
#include<G4ParticleGun.hh>
#include<G4ParticleTable.hh>
#include<G4ParticleDefinition.hh>
#include<globals.hh>

#include <chrono>
#include <thread>

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* myDC):myDetector(myDC)
{
	G4int n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle("e-");
  
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	particleGun->SetParticlePosition(G4ThreeVector(0, 0, -50*m));
	particleGun->SetParticleEnergy(5*MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    
    
	particleGun->GeneratePrimaryVertex(anEvent);
    
}
