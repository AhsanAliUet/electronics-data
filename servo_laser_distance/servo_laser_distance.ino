#include "Servo.h"
#include "Adafruit_VL53L0X.h"
 
Adafruit_VL53L0X lox = Adafruit_VL53L0X()

void setup_laser_sensor(){
  Serial.begin(115200);
 
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
 
  Serial.println(" VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

void loop_laser_sensor(){
  VL53L0X_RangingMeasurementData_t measure;
 
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
 
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
 
  delay(1000);
}

Servo servo_1;
Servo servo_2;

#define servo_1_signal_pin 13
#define servo_2_signal_pin 14

void setup() {
  // put your setup code here, to run once:
  servo_1.attach(servo_1_signal_pin);
  servo_2.attach(servo_2_signal_pin);
  setup_laser_sensor();

}

void loop() {
  loop_laser_sensor();

  // Sweep from 0 to 180 degrees:
  for (int angle = 0; angle <= 180; angle += 1) {
    servo_1.write(angle);
    delay(15);
  }

  // And back from 180 to 0 degrees:
  for (int angle = 180; angle >= 0; angle -= 1) {
    servo_1.write(angle);
    delay(15);
  }

  delay(1000);
}
