#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include<globals.hh>
#include<G4VUserDetectorConstruction.hh>
#include<G4VSolid.hh>
#include<G4LogicalVolume.hh>
#include<G4VPhysicalVolume.hh>
#include<G4Material.hh>

#include "G4EqMagElectricField.hh"
#include "G4UniformElectricField.hh"
#include <G4MagIntegratorStepper.hh>
#include <G4FieldManager.hh>
#include <G4ChordFinder.hh>
#include <G4MagIntegratorDriver.hh>

#include "G4SystemOfUnits.hh"
#include <G4ClassicalRK4.hh>

#include <G4PVParameterised.hh>
#include <G4VPVParameterisation.hh>

/** World -- класс самого внешнего объема в моделировании. */
class World {
protected:
    G4VSolid *solid;
    G4LogicalVolume *logic;
    G4VPhysicalVolume *physic;
    G4Material *mater;
    double sizex, sizey, sizez;
public:
    World(double size_x, double size_y, double size_z, G4Material *mater_=NULL);
    operator G4LogicalVolume*() {return logic;}
    G4LogicalVolume *getLogic() {return logic;}
  //	void setLogic(G4LogicalVolume *volA);
    G4VSolid *getSolid() {return solid;}
    G4VPhysicalVolume *getPhysic() {return physic;}
};



class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction();
  
  G4VPhysicalVolume* Construct();
  
protected:
  World *world;

public:
    G4ElectricField*        fEMfield;
    G4EqMagElectricField*   fEquation;
    G4MagIntegratorStepper* fStepper;
    G4FieldManager*         fFieldMgr;
    G4double                fMinStep ;
    G4ChordFinder*          fChordFinder ;
    G4MagInt_Driver*        fIntgrDriver;

  protected:
    G4LogicalVolume*  fScoringVolume;
};





class ChamberParameterisation : public G4VPVParameterisation
{
    public:
    ChamberParameterisation( G4int NoChambers, G4double startZ, G4double spacing, G4double widthChamber, G4double lenInitial, G4double lenFinal );
        ~ChamberParameterisation();
    
    void ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const;
    
 //   void ComputeDimensions (G4Orb& trackerLayer, const G4int copyNo, const G4VPhysicalVolume* physVol) const;
    
    G4int NoChambers;
    G4double startZ;
    G4double spacing;
    G4double widthChamber;
    G4double lenInitial;
    G4double lenFinal;
    
};

#endif
