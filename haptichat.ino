//www.elegoo.com
//2016.12.08
// Declaration and initialization of the input pin
#include <math.h>
void setup ()
{
 pinMode(A0, INPUT);
 pinMode(A1, INPUT);
 pinMode(A2, INPUT);
 pinMode(3, OUTPUT);
 Serial.begin (9600); // Serial output with 9600 bps
 pinMode(0 ,OUTPUT);
 pinMode(1 ,OUTPUT);
 pinMode(2 ,OUTPUT);
 pinMode(3 ,OUTPUT);
 pinMode(4 ,OUTPUT);
 pinMode(5 ,OUTPUT);
}
// The program reads the current value of the input pins
// and outputs it via serial out
float prev_val0 = 0;
float prev_val1 = 0;
float prev_val2 = 0;
void loop ()
{
 //reset all haptics
 digitalWrite(0, LOW); 
 digitalWrite(1, LOW); 
 digitalWrite(2, LOW); 
 digitalWrite(3, LOW); 
 digitalWrite(4, LOW); 
 digitalWrite(5, LOW); 
 float cur_val0 = analogRead(A0);
 float cur_val1 = analogRead(A1);
 float cur_val2 = analogRead(A2);
 if(pow(cur_val0 - prev_val0,2) > 20 && pow(cur_val1 - prev_val1,2) > 20){
  int haptic_tobe_activated = round(cur_val0/(cur_val0 + cur_val1));
  digitalWrite(haptic_tobe_activated, HIGH);
 }
 if(pow(cur_val1 - prev_val1,2) > 20 && pow(cur_val2 - prev_val2,2) > 20){
  int haptic_tobe_activated = round(cur_val0/(cur_val0 + cur_val1)) + 4;
  digitalWrite(haptic_tobe_activated, HIGH);
 }
 if(pow(cur_val0 - prev_val0,2) > 20 && pow(cur_val2 - prev_val2,2) > 20){
  int haptic_tobe_activated = round(cur_val0/(cur_val0 + cur_val1)) + 8;
  digitalWrite(haptic_tobe_activated, HIGH);
 }
 Serial.print(cur_val0);
 Serial.print(" ");
 Serial.print(cur_val1);
 Serial.print(" ");
 Serial.println(cur_val2);
 prev_val0 = cur_val0;
 prev_val1 = cur_val1;
 prev_val2 = cur_val2;
 //Serial.print ("Extreme value: ");
 delay(20);
}
