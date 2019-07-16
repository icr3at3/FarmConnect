
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
char auth[] = "bf5b0034654e483abed840bd9dd54dc0"; //Blynk Server
//char auth[] = "GwYJ0HazquNBdRWcDUCLUWX6AhfcX7ds";   //Local Server

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Sanket";
char pass[] = "2444666668888888";


BlynkTimer timer;

const byte L298N_A_In1_pin = D1; //GPI04
const byte L298N_A_In2_pin = D2; //GPI0

const byte L298N_B_In3_pin = D3; // GPI02
const byte L298N_B_In4_pin = D4; // GPIO14

/*
 * blynk ekranı
 * V0 joystick,  
 * v1,v2, v3, v4,v5,v6,v7,v8 Led  
 * v10  button push
 * v11 button switch
 */

void motorSpeed(byte prmA1, byte prmA2, byte prmB1, byte prmB2)
{ 
  digitalWrite(L298N_A_In1_pin,prmA1);
  digitalWrite(L298N_A_In2_pin,prmA2);
  digitalWrite(L298N_B_In3_pin,prmB1);
  digitalWrite(L298N_B_In4_pin,prmB2);
 
}


BLYNK_WRITE(V0) {
  int x = param[0].asInt();
  int y = param[1].asInt();
// x =  -2 -1 0 1 2 
// Y =  -2 -1 0 1 2 

 if ((x==512) && (y==512)) // Rest
 {
   motorSpeed(LOW,LOW,LOW,LOW); 
 }
 else if (y>=900) // Forward 
 {
  motorSpeed(HIGH,LOW,HIGH,LOW); 
  
 }
 else if (y<=200)// Backward
 { 
  motorSpeed(LOW,HIGH,LOW,HIGH); 
  }
 else if (x>=900)// Right
 {  
  motorSpeed(HIGH,LOW,LOW,HIGH); 
  
  }
 else if (x<=200)// Left
 { 
  motorSpeed(LOW,HIGH,HIGH,LOW); 
  }

}

void setup() {
  Serial.begin(9600);
 
  pinMode(L298N_A_In1_pin,OUTPUT);
  pinMode(L298N_A_In2_pin,OUTPUT);
  pinMode(L298N_B_In3_pin,OUTPUT);
  pinMode(L298N_B_In4_pin,OUTPUT);

 digitalWrite(L298N_A_In1_pin,LOW);
 digitalWrite(L298N_A_In2_pin,LOW);
 digitalWrite(L298N_B_In3_pin,LOW);
 digitalWrite(L298N_B_In4_pin,LOW);

 
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
}
