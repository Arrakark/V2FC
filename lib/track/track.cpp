#include <track.h>

track::track(HTHING * _motor){
    motor = _motor;
}

void track::run(int vector){
    motor->run(vector);
}

void track::stop(){
    motor->stop();
}