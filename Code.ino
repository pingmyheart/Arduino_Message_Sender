#include <SoftwareSerial.h>
#include<String.h>

SoftwareSerial GSMModule(9, 10);//In bracket indicate in order the Tx And Rx pin usend on Arduino Board


void setup(){
    GSMModule.begin(9600);//Begin the comunication with GSM Module
    Serial.begin(9600);//Begin the Serial comunication
    delay(1000);
}

void loop(){
    String messages = Serial.readString();//Read the string passed through serial comunication
    
    //Incoming message looks like -----> prefix`cellphone_number`message_to_be_sent
    String[] message = strtok(*messages,*'`');
    String prefix = message[0];
    String telephone = message[1];
    String text = message[2];
    SendMessage(prefix,telephone,text);
    delay(100);
}

void SendMessage(String a, String b, String c ){
  GSMModule.println("AT+CMGF=1");//Set the GSM Module to send texts
  delay(500);//Delay half second
  GSMModule.println("AT+CMGS=\"+" + a + b + "\"\r");
  delay(500);//delay half second
  GSMModule.println(c);//
  delay(100);//delay 100 milliseconds
  GSMModule.println((char)26);//casting of the interruption command
  delay(1000);
}