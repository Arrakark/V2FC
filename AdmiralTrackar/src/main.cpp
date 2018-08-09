
#include <robot.h>
robot atb = robot();

void setup()
{
    //Start Serial
    Serial.begin(230400,  8E1);
    // Serial.begin(9600);
    atb.init();

    atb.establish_communication();
    //========================== FIRST EWOK ==========================
    atb.first_ewok_pick_up();
    //========================== SECOND EWOK ==========================
    atb.second_ewok_pick_up();
    //========================== IR BEACON ARCHWAY WAIT ==========================
    atb.archway_crossing();
    //========================== LINE FOLLOW TO THIRD EWOK ==========================
    atb.third_ewok_pick_up();
    //========================== RETURN HOME ========================================
    atb.return_home();


}

void loop()
{

}