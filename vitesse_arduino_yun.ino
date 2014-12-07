#include <Bridge.h>
#include <HttpClient.h>
#include <Servo.h> 

int val;

String tmpVal;

Servo myservo;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Serial.begin(9600);
  myservo.attach(8);  //set vitesse train

}

void loop() {
  HttpClient client;
  String res;
  char c;
  client.get("http://mathemagie.net/train/xhr/get_vitesse.php");

  while (client.available()) {
     c = client.read();
    res += c;
  }

  if (res != tmpVal) {
    Serial.println(res);
     myservo.write(res.toInt());
    
  }
  tmpVal = res;
 
  Serial.flush();

  delay(10);
}
