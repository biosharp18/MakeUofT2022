
#include <math.h>
#include <MPU6050.h>
void setup ()
{
 //Analog input for microphone array
 pinMode(A0, INPUT);
 pinMode(A1, INPUT);
 pinMode(A2, INPUT);
 pinMode(3, OUTPUT);
 Serial.begin (9600); // Serial output with 9600 bps
 //digital output for haptic motors
 pinMode(0 ,OUTPUT);
 pinMode(1 ,OUTPUT);
 pinMode(2 ,OUTPUT);
 pinMode(3 ,OUTPUT);
 pinMode(4 ,OUTPUT);
 pinMode(5 ,OUTPUT);
 
 //standard MPU6050 accelerometer code
  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // If you want, you can set accelerometer offsets
  // mpu.setAccelOffsetX();
  // mpu.setAccelOffsetY();
  // mpu.setAccelOffsetZ();
  
  checkSettings();
}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}
 
}
//define previous value of sound intensity
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
 //check previous value and current value for spike
 if(pow(cur_val0 - prev_val0,2) > 20 && pow(cur_val1 - prev_val1,2) > 20){
  int haptic_tobe_activated = round(cur_val0/(cur_val0 + cur_val1)); //dynamically choose to activate closest haptic to sound
  digitalWrite(haptic_tobe_activated, HIGH);
 }
 if(pow(cur_val1 - prev_val1,2) > 20 && pow(cur_val2 - prev_val2,2) > 20){
  int haptic_tobe_activated = round(cur_val0/(cur_val0 + cur_val1)) + 4;
  digitalWrite(haptic_tobe_activated, HIGH);
 }
 if(pow(cur_val0 - prev_val0,2) > 20 && pow(cur_val2 - prev_val2,2) > 20){
  int haptic_tobe_activated = round(cur_val0/(cur_val0 + cur_val1)) + 8;
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
 
 //detect head rotation with accelerometer
 Vector norm = mpu.readNormalizeGyro();

 // Calculate Pitch, Roll and Yaw
 pitch = pitch + norm.YAxis * timeStep;
 roll = roll + norm.XAxis * timeStep;
 yaw = yaw + norm.ZAxis * timeStep;
 //Adjust the triggered haptic to follow head movement
 haptic_tobe_activated = haptic_tobe_activated + yaw*(normAccel.XAxis);
 //finish off iteration by activating the haptic
 digitalWrite(haptic_tobe_activated, HIGH);
 delay(20);
}
