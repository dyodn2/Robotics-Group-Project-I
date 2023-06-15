#include "MPU9250.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <DFRobot_ADS1115.h>

#define BME280 2
#define SEALEVELPRESSURE_HPA (1013.25)

/* Mpu9250 object, I2C bus,  0x68 address */
MPU9250 IMU(Wire, 0x68);
/* BME280 object, I2C bus,  0x76 address */
Adafruit_BME280 bme;
/* ADS1115 object, I2C bus */
DFRobot_ADS1115 ads(&Wire);

void setup()
{
    int status;

    /* Serial to display data */
    Serial.begin(9600);
    while (!Serial)
        continue;
    ads.setAddr_ADS1115(0x48);     // 0x49
    ads.setGain(eGAIN_TWOTHIRDS);  // 2/3x gain
    ads.setMode(eMODE_SINGLE);     // single-shot mode
    ads.setRate(eRATE_128);        // 128SPS (default)
    ads.setOSMode(eOSMODE_SINGLE); // Set to start a single-conversion
    ads.init();
    /*
      MPU9250 SETUP
    */
    status = IMU.begin();
    if (status < 0)
    {
        Serial.println("IMU initialization unsuccessful");
        Serial.println("Check IMU wiring or try cycling power");
        Serial.print("Status: ");
        Serial.println(status);
    }
    /*
        BME280 SETUP
    */
    status = bme.begin(0x76, &Wire);
    if (!status)
    {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
    }
    Serial.println();
    delay(100); // let sensor boot up
}

void print_MPU9250()
{
    // read the sensor
    IMU.readSensor();
    // display the data
    Serial.print("--MPU9250 test---\n");
    Serial.print("AccelX_mss:");
    Serial.print(IMU.getAccelX_mss(), 6);
    Serial.print("\t");
    Serial.print("AccelY_mss:");
    Serial.print(IMU.getAccelY_mss(), 6);
    Serial.print("\t");
    Serial.print("AccelZ_mss:");
    Serial.print(IMU.getAccelZ_mss(), 6);
    Serial.print("\t\n");
    Serial.print("GyroX_rads:");
    Serial.print(IMU.getGyroX_rads(), 6);
    Serial.print("\t");
    Serial.print("GyroY_rads:");
    Serial.print(IMU.getGyroY_rads(), 6);
    Serial.print("\t");
    Serial.print("GyroZ_rads:");
    Serial.print(IMU.getGyroZ_rads(), 6);
    Serial.print("\t\n");
    Serial.print("MagX_uT:");
    Serial.print(IMU.getMagX_uT(), 6);
    Serial.print("\t");
    Serial.print("MagY_uT:");
    Serial.print(IMU.getMagY_uT(), 6);
    Serial.print("\t");
    Serial.print("MagZ_uT:");
    Serial.print(IMU.getMagZ_uT(), 6);
    Serial.print("\t\n");
    Serial.println(IMU.getTemperature_C(), 6);
    Serial.print("\n");
    delay(1000);
}

void print_BME280()
{
    Serial.print(F("--- BME280 test ---\n"));
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    Serial.println();
    delay(1000);
}

void print_ADS1115()
{
    if (ads.checkADS1115())
    {
        int16_t adc0, adc1, adc2, adc3;
        adc0 = ads.readVoltage(0);
        Serial.print("--ADS1115 test---\n");
        Serial.print("A0:");
        Serial.print(adc0);
        Serial.print("mV,  ");
        adc1 = ads.readVoltage(1);
        Serial.print("A1:");
        Serial.print(adc1);
        Serial.print("mV,  ");
        adc2 = ads.readVoltage(2);
        Serial.print("A2:");
        Serial.print(adc2);
        Serial.print("mV\n\n");
    }
    else
    {
        Serial.println("ADS1115 Disconnected!");
    }
    delay(2000);
}

void loop()
{
    print_MPU9250();
    print_BME280();
    print_ADS1115();
}