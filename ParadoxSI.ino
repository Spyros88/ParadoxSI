//Paradox Serial Interface *tested on SP5500 panel.

#include <SoftwareSerial.h>
uint8_t Status = 0;        //0= unarmed 1= Armed 2= Sleep 3= Stay
uint8_t Zones[11] = {0,0,0,0,0,0,0,0,0,0,0};
uint8_t last_zone;



int data[37];
int newdata[37];
SoftwareSerial paradoxSerial(8,7);// blue 8, yellow 7, mauro ground
String inString = "";
void setup() {
    Serial.begin(115200);
    paradoxSerial.begin(9600);
    paradoxSerial.flush();
    Serial.println("Welcome to Paradox interface");
}
 
void loop()
{
  if(paradoxSerial.available()) {
     for(int i=0; i<=36; i++){
     data[i] = paradoxSerial.read();
     delay(75);
     //Serial.print(i);
     //Serial.print(":");
     //Serial.println(data[i]);
     }
     delay(20);
    moveArray();
    getdata();
    compare_data();
  }
}
void moveArray(){       //no point
for(int i=0; i<=36; i++){
newdata[i] = data[i];
  }
}

 void getdata(){
uint8_t e_month;
uint8_t e_day;
uint8_t e_hour;
uint8_t e_minute;
char e_time[15] = {0};
 //dtostrf(newdata[3], 1, 0, e_time);  // convert to char
/*Serial.print(newdata[4]);
Serial.print("/");
Serial.print(newdata[3]);
Serial.print("-");
Serial.print(newdata[5]);
Serial.print(":");
Serial.print(newdata[6]);
Serial.print(" Event: ");
Serial.print(newdata[7]);
Serial.print("-");
Serial.println(newdata[8]);
            */                                         
                                                       
 }

void compare_data(){
    if(newdata[7] == 0){
      Serial.print("Zone ");
      Serial.print(newdata[8]);
      Serial.println(" Closed");
      for(int i=1; i<=10; i++){
        if(i == newdata[8]){
          Zones[i] = 0;
          }
        }
      printZones();
      }
     if(newdata[7] == 1){
      Serial.print("Zone ");
      Serial.print(newdata[8]);
      Serial.println(" Opened");
       for(int i=1; i<=10; i++){
        if(i == newdata[8]){
          Zones[i] = 1;
          }
        }
      printZones();
      last_zone = newdata[8];
      }
     if(newdata[7] == 2 && newdata[8] == 14){
      Serial.print("Arming");
      }
     if(newdata[7] == 29){
      Serial.print("Armed from user ");
      Serial.print(newdata[8]);
      }
     if(newdata[7] == 2 && newdata[8] == 6){
      Serial.print("Alarm from Zone");
      Serial.print(last_zone);
      }
}


void printZones(){
  for(int i=1; i<=10; i++){
    Serial.print(Zones[i]);
    }
}
