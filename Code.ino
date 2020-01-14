#include <SoftwareSerial.h>
#include<String.h>

SoftwareSerial GSMModule(9, 10);//In bracket indicate in order the Tx And Rx pin usend on Arduino Board


void setup(){
    GSMModule.begin(9600);//Begin the comunication with GSM Module
    Serial.begin(9600);//Begin the Serial comunication
    delay(1000);
}

void loop(){
    String messages = Serial.ReadLine();
    String[] message = messages.Split('`');
    String prefix = message[0];
    String telephone = message[1];
    String text = message[2];
    SendMessage(prefix,telephone,text);
    delay(100);
}

void SendMessage(String a, String b, String c ){
  mySerial.println("AT+CMGF=1");//Set the GSM Module to send texts
  delay(500);//Delay half second
  mySerial.println("AT+CMGS=\""+"+"+a+b+"+\"\r");
  delay(500);//delay half second
  mySerial.println(c);//
  delay(100);//delay 100 milliseconds
   mySerial.println((char)26);//casting of the interruption 
  delay(1000);
}