#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"

BioloidController bioloid = BioloidController(1000000);

const int SERVOCOUNT = 5;
int id;
int pos;
boolean IDCheck;
boolean RunCheck;

void setup(){
   pinMode(0,OUTPUT);  
   
   //initialize variables 
   id = 1;
   pos = 0;
   IDCheck = 1;
   RunCheck = 0;
  //open serial port
   Serial.begin(9600);
   delay (3000);   
   Serial.println("###########################");    
   Serial.println("Serial Communication Established.");    
  
  
  
  // set position to center first
  
  // 0 position for Shoulder 1 is   2110
  // 0 position for Shoulder 2 is   2030
  // 0 position for Bicep Spin is   1030
  // 0 position for Elbow is        2000
  // 0 position for Forearm spin is 2040
 

  
  MoveCenter();
  MenuOptions(); 
  RunCheck = 1;
}

void loop(){
  // read the sensor:
  
    int inByte = Serial.read();

    switch (inByte) 
    {
    case '1':    
      ScanServo();
      break;

    case '2':    
      MoveCenter();
      break; 

     case '3':    
      RelaxServos();
      break;     

    case '4':
      FlexBicep();
      break;
    } 
  
}

//*************************************** Get Positions **************************************
void ScanServo(){
  id = 1;  
  Serial.println("###########################");
  Serial.println("Starting Servo Scanning Test.");
  Serial.println("###########################");
      
  while (id <= SERVOCOUNT){
  pos =  ax12GetRegister(id, 36, 2);
  Serial.print("Servo ID: ");
  Serial.println(id);
  Serial.print("Servo Position: ");
  Serial.println(pos);
  
  if (pos <= 0){
  Serial.println("###########################");
  Serial.print("ERROR! Servo ID: ");
  Serial.print(id);
  Serial.println(" not found. Please check connection and verify correct ID is set.");
  Serial.println("###########################"); 
  IDCheck = 0;
  }
  
  id = (id++)%SERVOCOUNT;
  delay(1000);
  }
  if (IDCheck == 0){
    Serial.println("###########################");
    Serial.println("ERROR! Servo ID(s) are missing from Scan. Please check connection and verify correct ID is set.");
    Serial.println("###########################");  
  }
  else{
  Serial.println("All servo IDs present.");
  }
    if (RunCheck == 1){
    MenuOptions();
  }

}

//************************************** Move Servos to Center *******************************************
void MoveCenter()
{
  //center positions of motors
  
  SetPosition(1, 2110);
  SetPosition(2, 2030);
  SetPosition(3, 1030);
  SetPosition(4, 2000);
  SetPosition(5, 2040);
}

//************************************************ FLex Bicep ********************************************
void FlexBicep(){
  Serial.println("###########################");
  Serial.println("Initializing Movement Sign Test");  
  Serial.println("###########################");
  delay(10);  
  
  // 0 position for Shoulder 1 is   2110
  // 0 position for Shoulder 2 is   2030
  // 0 position for Bicep Spin is   1030
  // 0 position for Elbow is        2000
  // 0 position for Forearm spin is 2040
  // 90 degrees is 1024
  // 180 degrees is 2048
  
  MoveCenter();
  delay(2000);
  
  int x;
  int Shoulder1_pos = 2110;
  int Shoulder2_pos = 2030;
  for (x = 0; x < 1024; x++)
  {
    // plus x or minus x to change direction
    SetPosition (1, Shoulder1_pos - x);
    SetPosition (2, Shoulder2_pos - x);
    SetPosition (4, Shoulder1_pos - x);
    delay(2);
  }
  
  //reverse the movements back to original position
  while (x > 0)
  {
    // plus x or minus x to change direction
    SetPosition (1, Shoulder1_pos - x);
    SetPosition (2, Shoulder2_pos - x);
    SetPosition (4, Shoulder1_pos - x);
    delay(2);
    x--;
  }
  
  //display menu options
   MenuOptions(); 
}


// ***************************************************Menu Options *******************************************
void MenuOptions(){
  
    Serial.println("###########################"); 
    Serial.println("Please enter option 1-5 to run individual tests again.");     
    Serial.println("1) Servo Scanning Test");        
    Serial.println("2) Move Servos to Center");    
    Serial.println("3) Relax Servos");            
    Serial.println("4) Flex Bicep");                    
    Serial.println("###########################"); 
}

//*********************************************Relax Servos ***************************************************
void RelaxServos(){
  id = 1;
  Serial.println("###########################");
  Serial.println("Relaxing Servos.");
  Serial.println("###########################");    
  while(id <= SERVOCOUNT){
    Relax(id);
    id = (id++)%SERVOCOUNT;
    delay(50);
  }
   if (RunCheck == 1){
      MenuOptions();
  }
}

    
