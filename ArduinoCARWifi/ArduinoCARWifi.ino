#include "Wire.h"
#include "Servo.h"

Servo timonx ;

const uint8_t MPU_addr = 0x68; // I2C address of the MPU-6050

const float MPU_GYRO_250_SCALE = 131.0;
const float MPU_GYRO_500_SCALE = 65.5;
const float MPU_GYRO_1000_SCALE = 32.8;
const float MPU_GYRO_2000_SCALE = 16.4;
const float MPU_ACCL_2_SCALE = 16384.0;
const float MPU_ACCL_4_SCALE = 8192.0;
const float MPU_ACCL_8_SCALE = 4096.0;
const float MPU_ACCL_16_SCALE = 2048.0;



struct rawdata {
  int16_t AcX;
  int16_t AcY;
  int16_t AcZ;
  int16_t Tmp;
  int16_t GyX;
  int16_t GyY;
  int16_t GyZ;
};

struct scaleddata {
  float AcX;
  float AcY;
  float AcZ;
  float Tmp;
  float GyX;
  float GyY;
  float GyZ;
};

bool checkI2c(byte addr);
void mpu6050Begin(byte addr);
rawdata mpu6050Read(byte addr, bool Debug);
void setMPU6050scales(byte addr, uint8_t Gyro, uint8_t Accl);
void getMPU6050scales(byte addr, uint8_t &Gyro, uint8_t &Accl);
scaleddata convertRawToScaled(byte addr, rawdata data_in, bool Debug);

void setup() {
  // put your setup code here, to run once:

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT); // A
  pinMode(4,OUTPUT); // B
  pinMode(5,OUTPUT); // PWM
  digitalWrite(2,HIGH);
  timonx.attach(6);
  Wire.begin();
  mpu6050Begin(MPU_addr);
  Serial.begin(115200);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  int farox = topic.indexOf("/faros");
  int motor = topic.indexOf("/movimiento");
  int timon = topic.indexOf("/timon");

  
  if (farox == 0){
  Serial.println("faros");
  int ON = payload.indexOf("ON");
  int OFF = payload.indexOf("OFF");
if (ON == 0){
  digitalWrite(2,0);
}
if (OFF == 0){
  digitalWrite(2,1);
}
  }
  
  if (motor == 0){
    Serial.println("motor");
  int UP = payload.indexOf("UP");
  int DOWN = payload.indexOf("DOWN");
  int STOP = payload.indexOf("STOP");
  int PWMX = payload.toInt();
if (UP == 0){
  digitalWrite(3,1); digitalWrite(4,0);
}
if (DOWN == 0){
  digitalWrite(3,0); digitalWrite(4,1);
}
if (STOP == 0){
  digitalWrite(3,0); digitalWrite(4,0);
}
  analogWrite(5,PWMX);
  }

  if (timon == 0){
    Serial.println("timon");
    int PWMX = payload.toInt();
    timonx.write(PWMX);
    delay(10);
  }
}

void loop() {


}
