// #include <robot.h>
// #define DELAY 2000
// robot atb = robot();

// void setup()
// {
//     Serial.begin(230400, SERIAL_8E1); // Start Serial    Wire.begin();
//     //Initialize the tracks, scissor lift, and arm
//     //ARMCONTROL::init(PB8, PB9, PB12, PB1);
//     atb.init();
//     Wire.begin();
//     //atb.drive_until_cliff();
//     atb.follow_right_edge_until_ewok();
//     robot::delay_update(500);
//     ARMCONTROL::armPickup();
//     ARMCONTROL::grabberHug();
//     robot::delay_update(2000);
//     if (ARMCONTROL::switchStatus())
//     {
//         ARMCONTROL::armDropoff();
//         robot::delay_update(2000);
//         ARMCONTROL::grabberOpen();
//         robot::delay_update(2000);
//         ARMCONTROL::armHorizontal();
//     }
//     else
//     {
//         ARMCONTROL::grabberOpen();
//         robot::delay_update(2000);
//         ARMCONTROL::grabberHug();
//         robot::delay_update(2000);
//         ARMCONTROL::armDropoff();
//         robot::delay_update(2000);
//         ARMCONTROL::grabberOpen();
//         robot::delay_update(2000);
//         ARMCONTROL::armHorizontal();
//     }
// }

// void loop(void)
// {
// }