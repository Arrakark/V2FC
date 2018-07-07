#include <track.h>

track::track(HTHING * _motor){
    motor = _motor;
}

void track::run(int speed){
    motor->run(speed);
}

void track::stop(){
    motor->stop();
}