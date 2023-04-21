#include <IRremote.h>
#include <Servo.h>

const int RECV_PIN = 7;
const int servoPin = 3;
 Servo servo;

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

//setup variables
void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  servo.attach (servoPin);

}

int servoState = 0;
int increment = 10;

//recives IR codes and rotates toothbrush
void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        if (results.value == 0XFFFFFFFF) {
          Serial.println(servoState);
          results.value = key_value;
          if (servoState > 180) {
            increment = increment * -1;
          }
          if (servoState < 0) {
            increment = increment * -1;
          }
          servoState = servoState + increment;
        servo.write(servoState);
        }
        
        }
        key_value = results.value;
        irrecv.resume(); 
}
