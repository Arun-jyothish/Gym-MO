
#include<Wire.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

/* double x, y, z; */

//#define led  LED_BUILTIN

void setup() {
  SerialBT.begin("ESP32test");   /// bt code
  delay(1000);
  pinMode(LED_BUILTIN,OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);

  Wire.endTransmission(true);
  Serial.begin(9600);
}
void init_fn(int& x,int& y,int& z){

    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    int xAng = map(AcX, minVal, maxVal, -90, 90);
    int yAng = map(AcY, minVal, maxVal, -90, 90);
    int zAng = map(AcZ, minVal, maxVal, -90, 90);

    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
    y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
	

}
void main_fn(String msg)

{
    int lower_angle = 290;
    int highier_angle = 65 ;

	if (msg == "leg" || msg == "LEG"){
    lower_angle = 290;
    highier_angle = 65 ;
		Serial.println("LEG exercise Selected !");
		SerialBT.println("LEG exercise Selected !");
	}
	else if (msg == "arm" || msg == "ARM"){
    lower_angle = 290;
    highier_angle = 65 ;
		Serial.println("ARM exercise Selected !");
		SerialBT.println("ARM exercise Selected !");
	}
	else {
		Serial.println("Command Not Found !");
		return;
	}
		SerialBT.print("lower angle: ");
		SerialBT.println(lower_angle);
		SerialBT.print("upper angle: ");
		SerialBT.println(highier_angle);

		int x,y,z;
		init_fn(x,y,z);

    Serial.println(x);
    if ( x > highier_angle && x < 120) {
      SerialBT.println("Wrong, Too low");
      /* Serial.println("Wrong, Too low"); */

    }
    else if ( x < lower_angle && x > 120) {
      SerialBT.println("Wrong, Too high");
      /* Serial.println("Wrong, Too high"); */

    }

    else {
      SerialBT.println(" perfect ");
      /* Serial.println(" perfect "); */
    }
	Serial.println(x);
  }


void loop(){
	String msg;

   SerialBT.available()) {
    digitalWrite(LED_BUILTIN, LOW);   // BT CONNECTED INDICATION
		msg = SerialBT.readString();
		msg.trim();
  }
  main_fn(msg);
  else
    digitalWrite(LED_BUILTIN, HIGH);
}
