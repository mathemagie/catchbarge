#include <Bridge.h>
#include <HttpClient.h>
#include <Servo.h> 

int val;

String tmpVal;

Servo myservoa, myservob;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Serial.begin(9600);
  myservoa.attach(8);  //set vitesse train
  myservob.attach(9);  //set vitesse train

}

void loop() {
  HttpClient client;
  char res;
  char c;
  client.get("http://mathemagie.net/train/xhr/get_aiguillage.php");

  while (client.available()) {
     c = client.read();
    res += c;
  }

  if (res == '1') {
    myservoa.write(95);
    myservob.write(95);
    
  }
  if (res == '0') {
     myservoa.write(0);
     myservob.write(0);
    
  }

 
  Serial.flush();

  delay(10);
}
