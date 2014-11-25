String readString;
#include <Servo.h> 
#include <SPI.h>
#include <Ethernet.h>
#include <PusherClient.h>

Servo myservoa, myservob, myservoc;  // create servo object to control a servo 

String val;
int aiguillage_1_status = 1;
int aiguillage_2_status = 1;
int aiguillage_3_status = 1;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xED, 0xFE };
PusherClient client;

void setup() {
  Serial.begin(9600);
   if (Ethernet.begin(mac) == 0) {
    Serial.println("Init Ethernet failed");
    for(;;)
      ;
  }
  
  delay(1000);
  
  //myservoa.writeMicroseconds(1500); //set initial servo position if desired

  myservoa.attach(9);  //the pin for the servoa control
  myservob.attach(8);  //the pin for the servob control
  myservoc.attach(6);  //the pin for the servoc control
  
  
  Serial.println("set up vitesse train"); // so I can keep track of what is loaded
  if(client.connect("848c05ddb5587c84c6d1")) {
  
     client.bind("toogle_aiguillage_1", toogle_aiguillage_1);
     client.bind("toogle_aiguillage_2", toogle_aiguillage_2);
     client.bind("toogle_aiguillage_3", toogle_aiguillage_3);
     client.bind("toogle_nord_sud", toogle_nord_sud);
     client.subscribe("train_channel");
     Serial.println("bind process");
  }
  else {
    while(1) {}
  }
}


void loop() {
  
   if (client.connected()) {
    
    client.monitor();
  
  }
  else {
    myservoa.write(0);
    myservob.write(0);
    myservoc.write(0);
  }
}

void toogle_aiguillage_1(String data) {
  Serial.println(data);
  if (aiguillage_1_status == 0) {
     myservoa.write(95);
  }else {
    myservoa.write(0);
  }
  aiguillage_1_status = !aiguillage_1_status;
}
 
void toogle_aiguillage_2(String data) {
  Serial.println(data);
  if (aiguillage_2_status == 0) {
     myservob.write(95);
  }else {
    myservob.write(0);
  }
  aiguillage_2_status = !aiguillage_2_status;
}
 
void toogle_aiguillage_3(String data) {
  Serial.println(data);
  if (aiguillage_3_status == 0) {
     myservoc.write(110);
  }else {
    myservoc.write(0);
  }
  aiguillage_3_status = !aiguillage_3_status;
}

void toogle_nord_sud(String data) {
  toogle_aiguillage_1(data);
  toogle_aiguillage_2(data);
}
