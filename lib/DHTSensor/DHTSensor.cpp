/**
 * Class        DHTSensor
 * Author       2022-01-24 Charles Geiser
 * 
 * Purpose      Implements the class DHTSensor for DHT11 or DHT22  
 * 
 * Board        ESP32 DoIt DevKit V1
 *    
 */ 
#include "DHTsensor.h"

/** Initializes the sensor and reads the measurement data 
 * or gives an error message if the sensor was not found 
 * and stops the program
*/
void DHTSensor::setup()
{
    begin();
    _sData.sensorPin  = _pinADC;
    _sData.sensorType = _typeDHT;
    delay(2000);
    readSensor();
    if (isnan(_sData.tCelsius))
    {
        Serial.printf("DHT sensor not found at pin %d", _pinADC);
        while (true) delay(10000);
    }   
    log_i("==> done");
}


/**
 * Read the sensor and calculate the temperature 
 * in Fahrenheit and the dew point.
 */
void DHTSensor::readSensor()
{
    _sData.relHumidity = readHumidity();
    _sData.tCelsius    = readTemperature();
    _sData.tFahrenheit = _sData.tCelsius * 9.0 / 5.0 + 32.0;
    _sData.tKelvin     = _sData.tCelsius - _sData.Tabs; 
    _sData.dewPoint    = _calculateDewPoint();      
}


float DHTSensor::getCelsius()
{
    return _sData.tCelsius;
}


/**
 * Returns a reference to the sensor data struct
 */
SensorData&  DHTSensor::getDataReference()
{
    return(_sData);
}


void DHTSensor::printData()
{
    readSensor();

    Serial.printf(R"(---   Sensor Readings   ---
Sensor type        DHT%d    
Tc               %6.1f °C
Tf               %6.1f °F
Tk               %6.1f °K
Dewpoint         %6.1f °C
Humidity         %6.1f %%rH

)", _sData.sensorType, _sData.tCelsius, _sData.tFahrenheit, _sData.tKelvin, _sData.dewPoint, _sData.relHumidity);
}


/**
 * Calculate the dew point in °C from temperature and humidity
 */
float DHTSensor::_calculateDewPoint() 
{
    float k;
    k = log(_sData.relHumidity/100) + (17.62 * _sData.tCelsius) / (243.12 + _sData.tCelsius);
    return 243.12 * k / (17.62 - k);
}
