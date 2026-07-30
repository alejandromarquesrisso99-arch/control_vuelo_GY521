#include <Wire.h>

// Dirección I2C predeterminada del MPU-6050
const int MPU_ADDR = 0x68; 

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Despertar el MPU-6050 (por defecto entra en modo de reposo)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Registro PWR_MGMT_1
  Wire.write(0);    // Pone en 0 para encenderlo
  Wire.endTransmission(true);
  
  Serial.println("GY-521 Inicializado correctamente.");
}

void loop() {
  // Apuntar al primer registro de datos (ACCEL_XOUT_H = 0x3B)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  
  // Solicitar 14 registros (6 acelerómetro, 2 temperatura, 6 giroscopio)
  Wire.requestFrom(MPU_ADDR, 14, true);
  
  // Lectura de 16 bits combinando byte alto y byte bajo
  AcX = Wire.read() << 8 | Wire.read(); 
  AcY = Wire.read() << 8 | Wire.read(); 
  AcZ = Wire.read() << 8 | Wire.read(); 
  Tmp = Wire.read() << 8 | Wire.read(); 
  GyX = Wire.read() << 8 | Wire.read(); 
  GyY = Wire.read() << 8 | Wire.read(); 
  GyZ = Wire.read() << 8 | Wire.read(); 

  // Mostrar datos en el Monitor Serie
  Serial.print("Acel: X="); Serial.print(AcX);
  Serial.print(" | Y="); Serial.print(AcY);
  Serial.print(" | Z="); Serial.print(AcZ);
  Serial.print("  ||  Giro: X="); Serial.print(GyX);
  Serial.print(" | Y="); Serial.print(GyY);
  Serial.print(" | Z="); Serial.println(GyZ);

  delay(200);
}