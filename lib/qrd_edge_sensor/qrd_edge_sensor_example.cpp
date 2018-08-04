#include <Arduino.h>
#include <qrd_edge_sensor.h">

qrd_edge_sensor edge_sensor = qrd_edge_sensor(PA2);

void setup()
{
    Serial.begin(9600);
    edge_sensor.init();
}

void loop()
{
    edge_sensor.update();
    Serial.println(edge_sensor.sensor_value);
    delay(20);
}