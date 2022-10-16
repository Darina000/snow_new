#include"DetectorConstruction.hh"
#include"SensitiveDetector.hh" 
#include<G4NistManager.hh>
#include<G4Box.hh>
#include "G4Orb.hh"
#include<G4LogicalVolume.hh>
#include<G4PVPlacement.hh>
#include<G4SDManager.hh>
#include<G4VisAttributes.hh>
#include "G4SystemOfUnits.hh"

#include <G4UniformMagField.hh>
#include <G4ClassicalRK4.hh>
#include <G4TransportationManager.hh>
#include <G4EqMagElectricField.hh>
#include "G4EquationOfMotion.hh"
#include "G4ElectroMagneticField.hh"
#include "G4EqEMFieldWithSpin.hh"
#include "G4PropagatorInField.hh"



#include <G4VPVParameterisation.hh>
#include <G4PVParameterised.hh>

#include <random>


#include "G4ChargeState.hh"

#include "G4ElectroMagneticField.hh"

using namespace std;

#define Mat(x) (G4NistManager::Instance()->FindOrBuildMaterial(x))

DetectorConstruction::DetectorConstruction(): G4VUserDetectorConstruction(),fScoringVolume(0)
{ }

DetectorConstruction::~DetectorConstruction()
{ }

ChamberParameterisation::ChamberParameterisation(G4int NoChambers1, G4double startZ1, G4double spacing1, G4double widthChamber1, G4double lenInitial1, G4double lenFinal1 ): NoChambers(NoChambers1), startZ(startZ1), spacing(spacing1), widthChamber(widthChamber1), lenInitial(lenInitial1), lenFinal(lenFinal1){}

ChamberParameterisation::~ChamberParameterisation(){}


void ChamberParameterisation::ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
    G4double Zposition = (std::rand() % 20000 - 10000); // надо world_sizeX*2- world_sizeXY в см
    G4double Yposition = (std::rand() % 20000 - 10000);
    G4double Xposition = (std::rand() % 20000 - 10000);
    
    G4ThreeVector origin(Xposition*cm, Yposition*cm, Zposition*cm);
    
    physVol->SetTranslation(origin); //эта функция отвечает за положение каждой частицы
 // physVol->SetRotation(0);
}



World::World(double size_x, double size_y, double size_z,  G4Material *mater_): mater(mater_), sizex(size_x), sizey(size_y), sizez(size_z)
{

    
	//double size05 = size/2;
	solid = new G4Box("world", sizex, sizey, sizez);
	logic = new G4LogicalVolume(solid, mater, "World", 0, 0, 0);
	physic = new G4PVPlacement(0, G4ThreeVector(), logic, "World",  0, false, 0);             
}



G4VPhysicalVolume* DetectorConstruction::Construct()
{
    
    G4String name, symbol;
    G4double fractionmass, densityW, densityA;
    G4int nel, ncomponents;
    
    G4NistManager* nist = G4NistManager::Instance();
    G4int nvar = 8;
//fMinStep = 0.001*mm ;
    G4bool isotopes = true;
//    G4bool checkOverlaps = true;
    
    
    auto nistManager = G4NistManager::Instance();
      
    densityA = 0.413*kg/m3;
    densityW = 900.0*kg/m3;
    fMinStep = 0.01*mm ;
//gejkynhbhm hhpasx     
    auto water = nistManager ->BuildMaterialWithNewDensity("WaterDensity", "G4_WATER", densityW);
    auto air = nistManager ->BuildMaterialWithNewDensity("AirDensity", "G4_AIR", densityA);
        

    world = new World(200*m, 200*m, 202*m, air);
    
    /*
    
    G4Box *solidTgt = new G4Box("solidTgt", 0.5*200*m, 0.5*200*m, 0.5*200*m);
    G4LogicalVolume *logiclTgt = new G4LogicalVolume(solidTgt, air, "logiclTgt");
    G4PVPlacement *physilTgt = new G4PVPlacement(0, G4ThreeVector(0,0,0), logiclTgt,
                             "physilTgt", world->getLogic(), false, 0);
    
    */
    
    G4Box *solidDet = new G4Box("solidDet",  0.5*200*m, 0.5*200*m, 0.5*200*m);
    G4LogicalVolume *logicDet = new G4LogicalVolume(solidDet, air, "logicDet");
    G4PVPlacement *physiDet = new G4PVPlacement(0, G4ThreeVector(0,0,0*m), logicDet, "physiDet", world->getLogic(), false, 0);
     
     
//    G4Box *solidSliceDet = new G4Box("solidSliceDet",  0.5*200*m, 0.5*200*m, 0.5*1*m);
//   G4LogicalVolume *logicSliceDet = new G4LogicalVolume(solidSliceDet, air, "logicSliceDet");
//    G4PVPlacement *physiSliceDet = new G4PVPlacement(0, G4ThreeVector(0,0,100.5*m), logicSliceDet, "physiSliceDet", world->getLogic(), false, 0);



    

       
       
    G4VSolid* sol;
    G4LogicalVolume* logicSol;
       // G4VPhysicalVolume* chamberPhys;
       // G4int kZAxis = 0.0;
    
    sol = new G4Orb("chamber", 1.0*cm); //10*m)
    logicSol = new G4LogicalVolume(sol, water, "Chamber", 0, 0, 0);
        
        G4int NoChambers = 6;
        G4double startZ = 0.0 * mm; // Z of centre of first
        G4double spacing = 0.001 * cm; // Z spacing of centres
        G4double widthChamber = 1.0 * mm; // Width chamber
        G4double lenInitial  =  1.0 * mm; // length first chamber
        G4double lenFinal = 1.0 * mm;
    
        
        G4VPVParameterisation* chamberParam = new ChamberParameterisation(NoChambers, startZ, spacing, widthChamber, lenInitial, lenFinal); //
        G4VPhysicalVolume* physChamber = new G4PVParameterised( "Chamber", logicSol, logicDet, kZAxis, 100, chamberParam, true);
    

        physChamber->CheckOverlaps();     
        

 
    
        SensitiveDetector *detector = new SensitiveDetector("hi there");
    
        G4SDManager* SDman = G4SDManager::GetSDMpointer();
        SDman->AddNewDetector(detector);
        logicDet->SetSensitiveDetector(detector);
    
        world->getLogic()->SetVisAttributes (G4VisAttributes::Invisible);
    
    
    
    
 
    
    G4ElectricField* magField_5 = new G4UniformElectricField( G4ThreeVector(0.0,0.0,
                                                                          -200*kilovolt/m)); //минус - ускорение, + поворот
    G4EqMagElectricField* fEquation1_5 = new G4EqMagElectricField(magField_5);
    G4MagIntegratorStepper* fStepper1_5 = new G4ClassicalRK4( fEquation1_5, nvar );
    G4FieldManager* localFieldMgr1_5
            = new G4FieldManager(magField_5);
    logicDet->SetFieldManager(localFieldMgr1_5, true);
    G4MagInt_Driver* fIntgrDriver1_5 = new G4MagInt_Driver(fMinStep,
                                     fStepper1_5,
                                     fStepper1_5->GetNumberOfVariables() );
    G4ChordFinder* fChordFinder1_5 = new G4ChordFinder(fIntgrDriver1_5);
       localFieldMgr1_5->SetChordFinder( fChordFinder1_5 );
    
     
    
    
    
    
    return world->getPhysic();
}
