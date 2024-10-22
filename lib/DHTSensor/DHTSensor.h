/**
 * Class        DHTSensor
 * Author       2024-10-19 Charles Geiser
 * 
 * Purpose      A class to measure temperature and relative humidity by means of a DHT11 or
 *              DHT22 sensor.It also calculates the temperature in Fahrenheit and the dewpoint.  
 * 
 * Board        ESP32 DoIt DevKit V1
 * 
 * Wiring       DHT11-Sensor Breakout Elegoo
 *                  ----.
 *                  ° ° |==== GND  --> 0V
 *                  ° ° |==== Vcc  --> 3.3 .. 5V
 *                  ° ° |==== DATA --> Digital InputPin (14)
 *                  ----'
 * 
 *              DHT22-Sensor (AM2302)
 *                  ----.
 *                  ° ° |==== GND  --> 0V
 *                  ° ° |==== NC
 *                  ° ° |==== DATA --> Digital InputPin (14)
 *                  ° ° |==== Vcc  --> 3.3 .. 5V
 *                  ----'
 * 
 * Remarks
 * References   
 */  
#pragma once

#include <Arduino.h>
#include <DHT.h>
#include "SensorData.h"
#include "Isensor.h"


class DHTSensor : public ISensor, DHT
{  
    public:
        DHTSensor(uint8_t typeDHT, uint8_t pinADC, SensorData& sensorData) : DHT(pinADC, typeDHT),
                 _typeDHT(typeDHT), _pinADC(pinADC), _sData(sensorData)
        {}

        void  setup() override;       // initializes the DHT sensor or stops if none is present
        void  readSensor() override;  // refresh the sensor readings
        float getCelsius() override;
        void  printData()  override;  // prints the sensor readings from sensor data struct
        SensorData& getDataReference() override;  // returns a referenc to the sensor data struct which holds the sensor readings

    private:
        float _calculateDewPoint();
        uint8_t _typeDHT;
        uint8_t _pinADC;
        SensorData& _sData;
};