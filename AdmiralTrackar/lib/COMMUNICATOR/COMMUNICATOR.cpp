#include <COMMUNICATOR.h>

COMMUNICATOR::COMMUNICATOR(int _transmit_pin, int _receive_pin) {
    transmit_pin = _transmit_pin;
    receive_pin = _receive_pin;
}

void COMMUNICATOR::init() {
    pinMode(transmit_pin,OUTPUT);
    digitalWrite(transmit_pin, HIGH);

    pinMode(receive_pin,INPUT_PULLUP);
}

void COMMUNICATOR::setTransmission(bool _signal) {
    if (_signal) digitalWrite(transmit_pin,LOW);
    else digitalWrite(transmit_pin,HIGH);
}

bool COMMUNICATOR::checkReveice() {
    if (digitalRead(receive_pin)) return (false);
    else return (true);
}

