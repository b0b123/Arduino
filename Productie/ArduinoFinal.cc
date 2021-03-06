// Pin numbers
const int temperaturePin = 1;
const int ldrPin = 0;
const int ledGroen = 8;
const int ledGeel = 9;
const int ledRood = 10;

boolean automatisch = true;

boolean blinken = false;
// standaard afstand schermen 
int afstandscherm = 5;
int uitrolafstand = 160;

int ledState = LOW;

int ldrReading = 0;
int countLight = 0;
float countTemp = 0;
int averageTemp = 10;
int averageLight = 300; 

int averageTemp2 = averageTemp;
int averageLight2 = averageLight;
 


int standaardtemp = 15;
int standaardlux = 700;

// elk "event/timer" (voor input,output) krijgt zijn eigen variabele
unsigned long previousMillis = 0;
unsigned long previousMillis1s = 0;
unsigned long previousMillis40 = 0;
unsigned long previousMillis30 = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis10 = 0;
unsigned long previousMillis15 = 0;
unsigned long previousMillis20 = 0;
unsigned long previousMillis4= 0;
unsigned long previousMillisblink = 0;



int interval20 = 20000; // 20sec
int interval40 = 40000; // 40sec
int interval30 = 30000; // 30sec
int interval10 = 10000; // 10sec
int interval15 = 15000; // 15se
int interval1 = 1000; // 1sec
int interval1s = 1000; // 1sec

void setup()
{
  //Start Serial port
  Serial.begin(9600);        // start serial for output - for testing
  pinMode(ledGroen, OUTPUT);
  pinMode(ledGeel, OUTPUT);
  pinMode(ledRood, OUTPUT);
  digitalWrite(ledGroen, HIGH);
}

void loop()
{   
  

  ldrReading = analogRead(ldrPin);
  float voltage,degreesC;
  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;

  // geef huidige tijd
  unsigned long currentMillis = millis();


  // lees waarde van LDR per seconde en stop het in de variabele averageLight
  if((unsigned long)(currentMillis - previousMillis1) >= interval1){
    previousMillis1 = currentMillis;
    countLight += ldrReading;
    countTemp += degreesC;
    delay(1000);

  }
  if((unsigned long)(currentMillis - previousMillis10) >= interval10){
    averageLight = countLight / 10;
    countLight = 0;
    previousMillis10 = currentMillis;
  }
  if((unsigned long)(currentMillis - previousMillis15) >= interval15) {
    previousMillis15 = currentMillis;
    averageTemp = countTemp / 15;
    countTemp = 0;
  
  }

if((unsigned long)(currentMillis - previousMillis20) >= interval20) {
    previousMillis20 = currentMillis;
    averageTemp2 = averageTemp;
    averageLight2 = averageLight;

  }
     

if (automatisch == true){

// inrollen als de temperatuur of lux niet voldoet
if (averageTemp2 < standaardtemp || averageLight2 < standaardlux){
  if (afstandscherm > 5){
    

      digitalWrite(ledRood, HIGH);
      digitalWrite(ledGroen, LOW);
      changeledState();
      digitalWrite(ledGeel, ledState);
      

      afstandscherm -= 10;
     
     }
  else if (afstandscherm <5){
    digitalWrite(ledGroen, HIGH);
    digitalWrite(ledGeel, LOW);
    digitalWrite(ledRood, LOW);
    afstandscherm = 5;

    }
}
//inrollen
if (averageTemp2 >= standaardtemp && averageLight2 >= standaardlux){
if (afstandscherm > uitrolafstand){

      digitalWrite(ledRood, HIGH);
      digitalWrite(ledGroen, LOW);
      changeledState();
      
      digitalWrite(ledGeel, ledState);
      
      afstandscherm -=10;
      if(afstandscherm <= uitrolafstand){
      digitalWrite(ledGroen, LOW);
      digitalWrite(ledGeel, LOW);
      digitalWrite(ledRood, HIGH);
      afstandscherm = uitrolafstand;

        }
      if(afstandscherm == 5){
      digitalWrite(ledGroen, HIGH);
      digitalWrite(ledGeel, LOW);
      digitalWrite(ledRood, LOW);
        }
}

}
//uitrollen
if (averageTemp2 >= standaardtemp && averageLight2 >= standaardlux){
  if (afstandscherm < uitrolafstand){

      digitalWrite(ledRood, LOW);
      digitalWrite(ledGroen, HIGH);
      changeledState();
      
      digitalWrite(ledGeel, ledState);
      
      afstandscherm +=10;
      if(afstandscherm >= uitrolafstand){
      digitalWrite(ledGroen, LOW);
      digitalWrite(ledGeel, LOW);
      digitalWrite(ledRood, HIGH);
      afstandscherm = uitrolafstand;

        }

}

}
}
//handmatig uitrollen
if(automatisch == false){

  if (afstandscherm < uitrolafstand){

      digitalWrite(ledRood, LOW);
      digitalWrite(ledGroen, HIGH);
      changeledState();
      digitalWrite(ledGeel, ledState);
      
      afstandscherm +=10;
      if(afstandscherm >= uitrolafstand){
      digitalWrite(ledGroen, LOW);
      digitalWrite(ledGeel, LOW);
      digitalWrite(ledRood, HIGH);
      afstandscherm = uitrolafstand;

        }

}

 
if (afstandscherm > uitrolafstand){

      digitalWrite(ledRood, HIGH);
      digitalWrite(ledGroen, LOW);
      changeledState();
      digitalWrite(ledGeel, ledState);
      
      afstandscherm -=10;
      if(afstandscherm <= uitrolafstand){
      digitalWrite(ledGroen, LOW);
      digitalWrite(ledGeel, LOW);
      digitalWrite(ledRood, HIGH);
      afstandscherm = uitrolafstand;

        }
      if(afstandscherm == 5){
      digitalWrite(ledGroen, HIGH);
      digitalWrite(ledGeel, LOW);
      digitalWrite(ledRood, LOW);
        }
}
  } 
  
  
  
  
//int afstandscherm = 5;
//int uitrolafstand = 5;


  if (Serial.available()) {
        char serialListener = Serial.read();
        if (serialListener == 'H') {
            digitalWrite(ledGeel, HIGH);
        }
        else if (serialListener == 'L') {
            digitalWrite(ledGeel, LOW);
        }

        else if(serialListener == 'V') {
          Serial.print(averageLight);
          Serial.print(",");
          Serial.print(averageTemp);
          Serial.print("\n");
         }

         else if(serialListener == 'X') {
          
         }

         else if(serialListener == 'Y') {
         
         }
         
         else if (serialListener == '1') { //change the standaard + 5
             standaardtemp += 1;
                   
         }
         else if (serialListener == '2') { //change the standaard + 5
             standaardtemp += 5;
                   
         }
         else if (serialListener == '3') { //change the standaard -1
             standaardtemp -= 1;
             //Serial.print(standaardtemp);
             //Serial.print("\n");                       
         }
         else if (serialListener == '4') { //change the standaard + 5
          
             standaardtemp -= 5;
                      
         }
         else if (serialListener == '5') { //change the standaardtemp naar  + 5
             standaardlux = 0;
                     
         }
         else if (serialListener == '6') { //change the standaard lux 
             standaardlux = 350;
                 
         }
         else if (serialListener == '7') { //change the standaardlux
             standaardlux = 700;
      
                      
         }
         else if (serialListener == '8') { //change the standaardlux 
             standaardlux =1000;
                                
         }

         else if (serialListener == '0') { //change the standaardlux 
             setAutomatisch();
           }

         else if (serialListener == 'A'){
          uitrolafstand = 5;
          }
         else if (serialListener == 'B'){
          uitrolafstand = 30;
          }
          else if (serialListener == 'C'){
          uitrolafstand = 60;
          }
         else if (serialListener == 'D'){
          uitrolafstand = 90;
          }
         else if (serialListener == 'E'){
          uitrolafstand = 120;
          }
         else if (serialListener == 'F'){
          uitrolafstand = 160;
          }
         


}
}

//void blinkGeelHigh(){
// unsigned long currentblinktime = millis();
//     for (int i = 0; i<6; i++){
//      if (currentblinktime - previousblinktime > 1000){
//      currentblinktime = previousblinktime;
//      digitalWrite(ledGeel, (ledState) ? LOW : HIGH);
//              ledState = !ledState;
//      }
//     }
//}

void blinkGeelin(void){
  unsigned long currentMillis = millis();
  blinken =! blinken;  
  digitalWrite(ledRood, HIGH);
  digitalWrite(ledGroen, LOW);  

 if (blinken == true){
  if (currentMillis - previousMillisblink >= 1000) {
    previousMillisblink = currentMillis;
    if (ledState == LOW){
      ledState = HIGH;}
    else{
      ledState = LOW;}
    digitalWrite(ledGeel, ledState);
  if( currentMillis - previousMillis4 >= 6000){
    blinken =! blinken;
    digitalWrite(ledGroen, HIGH);
    digitalWrite(ledRood, LOW);
    afstandscherm = 5;
    }
    
}
}
}

boolean setAutomatisch(){
  automatisch =! automatisch;
  }

void changeledState(void){
  if (ledState == LOW){
    ledState = HIGH;}
  else{
    ledState = LOW;
    }
  }

float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}
