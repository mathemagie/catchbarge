#include <Bridge.h>
#include <HttpClient.h>
#include <Servo.h> 

int val;

char tmpVal;

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
  String res;
  char c;
  client.get("http://mathemagie.net/train/xhr/get_aiguillage.php");

  while (client.available()) {
     c = client.read();
     res += c;
    
  }
  Serial.println(c);
 
  if (c == '1') {
     Serial.println('valeur  1 from get ');
    myservoa.write(95);
    myservob.write(95);
    
  }
  if (c == '0') {
     Serial.println('valeur  0 from get');
     myservoa.write(0);
     myservob.write(0);
    
  }
  
 // tmpVal = res;

 
  Serial.flush();

  delay(100);
}
