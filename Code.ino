/**
 * The project is entirely developed by Russi Antonio
 * The Component used are:
 *  -Arduino Uno
 *  -SIM900 GSM Module
 * 
 * Remember that, as written in the code below, you have to connect
 *          ARDUINO DATASHEET <-------------------> GSMModule DATASHEET
 *                   Tx Pin 9 <-------------------> Rx Pin
 *                  Rx Pin 10 <-------------------> Tx Pin
*/

#include <SoftwareSerial.h>//including the library to permitt the comunication with the GSM Module
#include<String.h>//including the library to manage the Strings

SoftwareSerial GSMModule(9, 10);//In bracket indicate in order the Tx And Rx pin usend on Arduino Board

void setup(){
    GSMModule.begin(9600);//Begin the comunication with GSM Module
    Serial.begin(9600);//Begin the Serial comunication
    delay(1000);
}

int trace;//variable that contain the index of the backtick `
String prefix;//variable for the prefix of the telephone number
String telephone;//variable for the telephone number
String text;//variable for the text that needs to be sent
String temp;//variable to help in the splitting process

void loop(){
    String messages = Serial.readString();//Read the string passed through serial comunication
    
    //Incoming message looks like -----> prefix`cellphone_number`message_to_be_sent

    /**
     * The following code is used to split the string of the message in thre different parts:
     *  -Prefix
     *  -Telephone Number
     *  -Message
     * Using the Substring method of the class String
    */
    prefix = messages.substring(0,messages.indexOf('`'));
    trace = messages.indexOf('`') + 1;
    temp = messages.substring(trace,messages.length());
    telephone = temp.substring(0,temp.indexOf('`'));
    text = temp.substring(temp.indexOf('`')+1,temp.length());
    SendMessage(prefix,telephone,text);
    delay(100);
}

/**
 *The following is a function that is used to Send the message calling it into the main(loop) 
*/
void SendMessage(String a, String b, String c ){
  GSMModule.println("AT+CMGF=1");//Set the GSM Module to send texts
  delay(500);//Delay half second
  GSMModule.println("AT+CMGS=\"+" + a + b + "\"\r");//Set the prefix and telephone number
  delay(500);//delay half second
  GSMModule.println(c);//Set the message
  delay(100);//delay 100 milliseconds
  GSMModule.println((char)26);//casting of the interruption command Ctrl+D
  delay(1000);
}