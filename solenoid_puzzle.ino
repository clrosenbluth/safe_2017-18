//declare all variables, make sure no repeats, get all RGB on PWM. If necessary, the last 2 RGBs can be on the same pins since they turn on together.

//FSR and solenoids
int fsrPin1 = A0;    //the bus   
int fsrReading1;
int solenoid1 = 8;    //the bus
int fsrPin2 = A1;    //the statue of liberty
int fsrReading2;
int solenoid2 = 12;    //the taxi

//LDR stuff
int AAA= A3;
int CCC = A4;
int SensorValue1 = 0;
int SensorValue2 = 0;
int xxx=0;
int yyy=0;
int zzz=0;
int startingTime;

//RGBs
int red1 = 10;    //for the bus
int green1 = 11;    //for the bus
//these are the ones after the LDR
int red2 = 3;    //statue of liberty
int red3 = 5;    //taxi
int green2 = 6;    //statue of liberty
int green3 = 9;    //taxi

//declare bools here to control how they advance through the code?
  bool toLDR = false;
  bool toFSR2 = false;
  bool finished = false;
  

void setup() {
  // put your setup code here, to run once:

  //pinModes
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(red3, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(solenoid2, OUTPUT);
  pinMode(solenoid1, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(green1, OUTPUT);

  //RGBs on or off as needed
  digitalWrite(red1, HIGH);
  digitalWrite(green1, LOW);
  digitalWrite(red2, HIGH);
  digitalWrite(red3, HIGH);
  digitalWrite(green2, LOW);
  digitalWrite(green3, LOW);

  //for testing
  Serial.begin(9600);
  Serial.println("Setup complete");

  //startingTime starts here (let it reset itself when they get up to that part of the code)
  long startingTime = millis();
  Serial.print("Starting time: ");
  Serial.println(startingTime);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //check FSR1 and control solenoid 1
  fsrReading1 = analogRead(fsrPin1);  
  Serial.print("Analog reading of FSR1= ");
  Serial.println(fsrReading1);   // the raw analog reading
  delay(100);

   if (fsrReading1 > 75){       //this is what can be readjusted for FSR1
    digitalWrite(solenoid1, HIGH);    //Should this be low?
    delay(100);
    digitalWrite(red1, LOW);
    digitalWrite(green1, HIGH);

    //ready to progress to LDR
    toLDR = true;
    Serial.println("toLDR is now true");
    }
      
  /* else {
    digitalWrite(solenoid1, LOW);
   }*/
   //end of FSR1 and solenoid 1

  
  //IF solenoid 1 > 11 (check number), do LDR code - either write it out or make it a function
  while (toLDR){

    Serial.println("Entered toLDR while loop");
    SensorValue1 = analogRead(AAA);
    Serial.print("SensorValue1 ");
    Serial.println (SensorValue1);
    SensorValue2 = analogRead(CCC);
    Serial.print("SensorValue2 ");
    Serial.println (SensorValue2);
    
    if ((SensorValue1 < 90)&&(zzz<30)&&(xxx==0)&&(yyy==0)){
      Serial.println("less then 90");
      xxx = xxx+1;
      Serial.print ("xxx =  ");
      Serial.println (xxx);
    
       //timing
      int currentTime = millis();
      if (currentTime - startingTime >= 10000) {
      Serial.println("Too long, starting over.");
      xxx = 0;
      yyy = 0;
      zzz = 0;
      startingTime = millis();
    }
    }
    
    if ((SensorValue1 <90) && (zzz<30)&& (xxx==1)&&(yyy==0)) {
      SensorValue1 = analogRead(AAA);
      SensorValue2 = analogRead(CCC);
      Serial.print("Sensor value is  ");
      Serial.print(SensorValue1);
      Serial.println(" and xxx is 1");
    
      //timing
      int currentTime = millis();
      if (currentTime - startingTime >= 10000) {
      Serial.println("Too long, starting over.");
      xxx = 0;
      yyy = 0;
      zzz = 0;
      startingTime = millis();
    }
    }
     
    if ((SensorValue2 <90) && (zzz<30) && (xxx==1)&&(yyy==0)){
      yyy = yyy+2;
      Serial.print ("yyy =  ");
      Serial.println (yyy);
    
      //timing
      int currentTime = millis();
      if (currentTime - startingTime >= 10000) {
      Serial.println("Too long, starting over.");
      xxx = 0;
      yyy = 0;
      zzz = 0;
      startingTime = millis();
    }
    }
    
     if ((xxx==1) && (yyy==2)){
      //timing
      int currentTime = millis();
      if (currentTime - startingTime >= 10000) {
      Serial.println("Too long, starting over.");
      xxx = 0;
      yyy = 0;
      zzz = 0;
      startingTime = millis();
      }
      
      zzz =zzz+yyy+xxx;
      Serial.print ("zzz when z x and y are added together is  =  ");
      Serial.println (zzz);
      xxx=0;
      yyy=0;
     }
    
     if (zzz==30) {
      toLDR = false;
      toFSR2 = true;
      Serial.println("Finished with LDRs");
      digitalWrite(green2, HIGH);
      digitalWrite(red2, LOW);
      }

      
     }
    
  
  //IF zzz==30 and time <= 10000, check FSR1 and control solenoid 2
  while (toFSR2){
    fsrReading2 = analogRead(fsrPin2);
    Serial.print("AnalogRead of FSR2: ");
    Serial.println(fsrReading2);
    delay(100);
    if (fsrReading2 > 50) {
       digitalWrite(solenoid2, HIGH);    //Should this be low?
       digitalWrite(green3, HIGH);
       digitalWrite(red3, LOW);
       delay(5000);
       toFSR2 = false;
      }
      finished = true;
    }
  //include resets as necessary - write in here, then commment out to check what happens when the battery pack is turned off
  while (finished) {
    startingTime = millis();
    zzz=0;
    xxx=0;
    yyy=0;
    fsrReading1 = 0;
    fsrReading2 = 0;
    
    digitalWrite(red1, HIGH);
    digitalWrite(green1, LOW);
    digitalWrite(red2, HIGH);
    digitalWrite(red3, HIGH);
    digitalWrite(green2, LOW);
    digitalWrite(green3, LOW);
    
    Serial.println("Completely finished");
    }
  
}
