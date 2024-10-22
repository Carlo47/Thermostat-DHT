#pragma once

// SensorData stores the values read by the sensor 
// and calculated on the basis of the measurements.
// This data structure depends on the capabilities of 
// the sensor and must be adapted accordingly.


using SensorData = struct sDat
{
    float tCelsius;
    float tFahrenheit;
    float tKelvin;
    float relHumidity;
    float dewPoint;
    uint8_t sensorPin;
    uint8_t sensorType;
    const double  Tabs = -273.15; // absolute temperature 
};