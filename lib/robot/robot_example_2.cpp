//just some ideas of whats

//using the the robot class
#include <Wire.h>
#include <Arduino.h>
#include <robot.h>
#include <irsensor.h>
#include <armControl.h>
#include <SLIFT.h>
#include <linefollower.h>
#include <HBRIDGE.h>
#include <IRBEACON.h>

//creating robot object
robot atb = robot(); //admiral track bar

//global variables
bool ewok_trigger = false;
bool left_trigger = false;
bool right_trigger = false;
int num_ewok_grabbed = 0;
unsigned long start_event_time = 0;
unsigned long end_event_time = 0;

//function prototypes (might be changed to robot member functions) (feel free to edit)
void ewok_triggering();
void sweep_find_ewok();
void sweep_back();
void grab_ewok();

//stage function prototypes
void second_stage();
void third_stage();
void fourth_stage();
void fifth_stage();
void zipline_finish();

//functions that is based on the correct calibration of m/s and rad/s
void second_stage_2();
void third_stage_2();
void fourth_stage_2();
void fifth_stage_2();

//==============================================================================================================

void setup()
{
    Serial.begin(9600); // Start Serial ***
    Serial.println("Sketch begin");
    // Wire.begin(); // ***
    atb.init();
}

void loop()
{
}

//==============================================================================================================

//stage  functions

/*
    Second Stage of Competition

    Before: robot just fully crossed the first gap (straight and in the middle of tap)
            arm is horizontal 
            grabber is open

    Goals:  - pickup second ewok (at the right)
            - sense appropriate IR Beacon signal (10 kHz)
            - line follow through the archway within 5 seconds the start of 10 kHz signal
*/

void second_stage()
{
    //pick up second ewok (to the right)

    //line follow until ewok is detected
    while (!ewok_trigger)
    {
        ewok_triggering();

        if (ewok_trigger)
            break;

        atb.line_follower->follow_line();
    }

    atb.left_motor->stop();
    atb.right_motor->stop();

    //when ewok is detected, rotate robot to sweep for ewok
    sweep_find_ewok();
    //grab ewok
    grab_ewok();
    //rotate robot back to original position before sweeping
    sweep_back();

    //----------------------------------------------------------------

    //sense appropriate IR Beacon signal (10 kHz)

    //adjust arm position for IR Beacon sensing
    ARMCONTROL::armVertical(); //***

    //robot line follow until it is positioned in front of IR Beacon

    int value;

    while (true)
    {
        value = IRBEACON::read(PA5);

        if (value == 1 || value == 2)
        {
            atb.left_motor->stop();
            atb.right_motor->stop();
            break;
        }

        else
        {
            atb.line_follower->follow_line();
        }
    }

    //robot waits until IR Beacon sensor senses 10kHz signal
    while (true)
    {
        value = IRBEACON::read(PA5);

        if (value == 2) //10 kHz detection
        {
            //line follow to cross the archway once 10kHz detected
            break;
        }
    }

    //line follow to go through archway
    while (true)
    {
        atb.line_follower->follow_line();
    }
}

void second_stage_2()
{
    //pick up second ewok (to the right)

    atb.line_follow_meters(0.3); //***
    atb.sweep_for_ewok(45);      //***
    grab_ewok();
    atb.turn_degrees(-45); //turn back to original position

    //----------------------------------------------------------------

    //sense appropriate IR Beacon Signal

    //line follow to appropriate IR Beacon Position
    atb.line_follow_meters(0.4); //***

    //adjust robot arm to appropriate IR Beacon sensing position
    ARMCONTROL::armVertical();

    //IR Beacon Sensing

    while (true)
    {
        int value = IRBEACON::read(PA5);

        if (value == 2) //10 kHz detection
        {
            //cross the archway when 10kHz detected
            atb.line_follow_meters(0.5); // ***
            break;
        }

        else //robot stays as it is when detect other signals
        {
            atb.left_motor->stop();
            atb.right_motor->stop();
        }
    }
}

//=======================================

/*
    Third Stage of Competition

    Before: robot just fully crossed the archway and following the line
            stormtroppers are not moving
            grabber is open 
            arm is vertical (from IR Detection)

    Goals:  - pickup third ewok (to the left)
            - align robot -> getting ready to cross the second gap
*/

void third_stage()
{
    //pick up third ewok

    //put arm back to horizontal (or search??)
    ARMCONTROL::armHorizontal();

    //line follow until ewok on the right is detected
    while (!ewok_trigger)
    {
        ewok_triggering();

        if (ewok_trigger)
            break;

        atb.line_follower->follow_line();
    }

    atb.left_motor->stop();
    atb.right_motor->stop();

    //when ewok is detected, rotate robot to sweep for ewok
    sweep_find_ewok();
    //grab ewok
    grab_ewok();
    //rotate robot back to original position before sweeping
    sweep_back();

    //----------------------------------------------------------------

    //align robot to get ready to cross the second gap

    /*  
        line follow until robot hits edge 
        (could be a good position for rotating the robot to get ready for second gap)
    */
    while (atb.bottom_sensor->mean() < CLIFF_DISTANCE)
    {
        atb.line_follower->follow_line();
    }

    /*
        turn robot to the right 
        (let left sensor sees weighted mean of 4.5 +/- 1 
        <- should be the case when all ir sensors see competition floor)

        use inverse weighted mean?
    */
    while (atb.left_sensor->weighted_mean() >= 3.5 && atb.left_sensor->weighted_mean() <= 5.5)
    {
        atb.left_motor->run(TURN_SPEED);
        atb.right_motor->run(-TURN_SPEED);
    }
    atb.left_motor->stop();
    atb.right_motor->stop();
}

void third_stage_2()
{
    //pickup third ewok

    atb.line_follow_meters(0.8);
    atb.sweep_for_ewok(45); //***
    grab_ewok();
    atb.turn_degrees(-45); //turn back to original position

    //----------------------------------------------------------------

    //align robot to get ready to cross the second gap

    //line follow until robot hits edge
    atb.line_follower->follow_line();

    //turn robot 90 degrees right
    atb.turn_degrees(90);
}

//=======================================

/*
    Fourth Stage of Competition

    Before: robot properly aligned and is ready to cross the second gap
            stormtroppers are not moving
            grabber is open 
            arm is horizontal

    Goals:  - crosses second gap
            - pick up fourth ewok
            - align robot to face forward of the suspension bridge or 
              that it is ready for pid-ing on the suspension bridge with 
              the edge (left and right) sensors
*/

void fourth_stage()
{
    // crosses second gap

    /*
        use this method for now <- if doesn't work well, use delay functions?

        keep going forward until the open claw touches or is touching the ewok 
        that's in front of the "tower"

        use weighted mean instead?
    */
    while (!(atb.front_sensor->inverse_weighted_mean() == 4.5 && atb.front_sensor->min_distance() < 1))
    {
        atb.left_motor->run(SECOND_GAP_SPEED);
        atb.right_motor->run(SECOND_GAP_SPEED);
    }
    atb.left_motor->stop();
    atb.right_motor->stop();

    //----------------------------------------------------------------

    // pick up fourth ewok

    grab_ewok(); //grab ewok straight away since it's in front of us

    //----------------------------------------------------------------

    // align robot to face forward of the suspension bridge

    /*
        turn robot to the right 
        (let right sensor sees weighted mean of 4.5 +/- 1 
        <- should be the case when all ir sensors see competition floor)

        or just weighted mean < 4.5 and that max distance is 30?

        use inverse weighted mean?
    */
    while (atb.right_sensor->inverse_weighted_mean() < 4.5 && atb.right_sensor->max_distance() >= 30)
    {
        atb.left_motor->run(TURN_SPEED);
        atb.right_motor->run(-TURN_SPEED);
    }

    atb.left_motor->stop();
    atb.right_motor->stop();
}

//=======================================

/*
    Fifth Stage of Competition

    Before: robot is in a position that is ready for pid on the edges of the suspension bridge
            stormtroppers are not moving
            grabber is open 
            arm is horizontal

    Goals:  - cross the suspension bridge
            - grabs Chewy
            - align robot to face back to the bridge (ready for zipline finish)
*/

void fifth_stage()
{
    // cross suspension bridge

    // atb.follow_right_edge_until_ewok(); //maybe that alone might work but until left_sensor sees chewy ***

    // pid edge_follower = pid();
    // edge_follower.p_gain = 20;
    // edge_follower.p_limit = 50;

    // do
    // {
    //     // atb.front_sensor->update();
    //     atb.right_sensor->update();
    //     float error = atb.right_sensor->inverse_weighted_mean() - 5.3;
    //     float control = edge_follower.output(error);
    //     atb.right_motor->run(EWOK_SPEED + (int)control);
    //     atb.left_motor->run(EWOK_SPEED - (int)control);
    //     Serial.println(String(NORMAL_SPEED + (int)control));
    //     Serial.println(String(NORMAL_SPEED - (int)control));
    //     delay(100);
    // } while (atb.left_sensor->min_distance() > CLOSEST_DISTANCE_TO_EWOK);

    // atb.left_motor->stop();
    // atb.right_motor->stop();

    //----------------------------------------------------------------

    //pid edge following (pid wrt both left and right edges)
    pid lr_edge_follower = pid();
    lr_edge_follower.p_gain = 20;
    lr_edge_follower.p_limit = 50;

    //edge follow until Chewy (on the left) is detected
    do
    {
        // atb.front_sensor->update();
        atb.right_sensor->update();
        atb.left_sensor->update();

        float error =
            (atb.right_sensor->inverse_weighted_mean() + atb.left_sensor->inverse_weighted_mean()) / 2 - 4.5;

        float control = lr_edge_follower.output(error);

        atb.right_motor->run(EWOK_SPEED + (int)control);
        atb.left_motor->run(EWOK_SPEED - (int)control);
        Serial.println(String(NORMAL_SPEED + (int)control));
        Serial.println(String(NORMAL_SPEED - (int)control));
        delay(100);
    } while (atb.left_sensor->min_distance() > CLOSEST_DISTANCE_TO_EWOK);

    atb.left_motor->stop();
    atb.right_motor->stop();

    //----------------------------------------------------------------

    // grabs Chewy

    //as Chewy is detected, rotate robot to sweep for Chewy
    sweep_find_ewok();
    //grab Chewy
    grab_ewok();
    //rotate robot back to original position before sweeping
    sweep_back();

    //----------------------------------------------------------------

    // align robot to face back to the bridge (ready for zipline finish)

    //first make robot go front until bottom sensor detects edge

    while (atb.bottom_sensor->mean() < CLIFF_DISTANCE)
    {
        atb.left_motor->run(NORMAL_SPEED);
        atb.right_motor->run(NORMAL_SPEED);
    }

    //make a 180 degree (or approximately) turn
    while (atb.bottom_sensor->inverse_weighted_mean() == 4.5 && (atb.left_sensor->inverse_weighted_mean() >= 3.7 && atb.left_sensor->inverse_weighted_mean() <= 5.3) && (atb.right_sensor->inverse_weighted_mean() >= 3.7 && atb.right_sensor->inverse_weighted_mean() <= 5.3))
    {
        atb.left_motor->run(TURN_SPEED);
        atb.right_motor->run(-TURN_SPEED);
    }
}

//=======================================

/*
    Zipline Finish of Competition

    Before: robot is facing the suspension bridge (about to move down to the towers)
            stormtroppers are not moving
            grabber is open 
            arm is horizontal

    Goals:  - make scissor lift to go up
            - basket hooks to the zipline
            - robot will keep moving foward (in back direction) 
              until basket is detached from the robot
            - basket slides down the zipline
*/

void zipline_finish()
{
    // make scissor lift to go up

    //initialize scissor lift of robot (cancel some of the initializations that were made to avoid timer conflict?)
    atb.lift->init();

    //raise scissor lift and make it stay there
    atb.lift->moveUp();
    atb.lift->stay();

    //----------------------------------------------------------------

    //send ewoks and Chewy back

    /*
        make robot to move forward until reaching back to Tower 1
        while basket is hooked to zipline and is detached from the robot
    */

    //edge follow until robot reaches back to Tower 1 (bottom sensors senses CLIFF)

    //pid edge following (pid wrt both left and right edges)
    pid lr_edge_follower = pid();
    lr_edge_follower.p_gain = 20;
    lr_edge_follower.p_limit = 50;

    //edge follow until Chewy (on the left) is detected
    do
    {
        atb.bottom_sensor->update();
        atb.right_sensor->update();
        atb.left_sensor->update();

        float error =
            (atb.right_sensor->inverse_weighted_mean() + atb.left_sensor->inverse_weighted_mean()) / 2 - 4.5;

        float control = lr_edge_follower.output(error);

        atb.right_motor->run(EWOK_SPEED + (int)control);
        atb.left_motor->run(EWOK_SPEED - (int)control);
        Serial.println(String(NORMAL_SPEED + (int)control));
        Serial.println(String(NORMAL_SPEED - (int)control));
        delay(100);
    } while (atb.bottom_sensor->mean() < CLIFF_DISTANCE);

    atb.left_motor->stop();
    atb.right_motor->stop();
}

//==============================================================================================================

//functions (might be added to the robot class if needed)

/*
    function that triggers for ewok grabbing when ewok is near and stops the robot
    use this function in a while loop

    function ends when:
    left and right motors are stopped
    grabber is open
    arm is in search position

    this/similar functions like that would be useful after grabbing the first ewok
*/
void ewok_triggering()
{
    //updating all three sensors
    atb.left_sensor->update();
    atb.right_sensor->update();
    atb.front_sensor->update();

    //***
    //left sensor triggering
    if (atb.left_sensor->min_distance() < 4 && atb.left_sensor->inverse_weighted_mean() > 4.5)
    {
        left_trigger = true;
        ewok_trigger = true;
    }

    //right sensor triggering
    else if (atb.right_sensor->min_distance() < 4 && atb.right_sensor->inverse_weighted_mean() < 4.5)
    {
        right_trigger = true;
        ewok_trigger = true;
    }

    //front sensor trigger
    else if (atb.front_sensor->min_distance() < 4)
    {
        ewok_trigger = true;
    }

    atb.left_motor->stop();
    atb.right_motor->stop();
    ARMCONTROL::grabberOpen();
    ARMCONTROL::armSearch();
}

//=======================================

/*
sweep for ewok, depending how the ewok triggered
function ends when robot (or front sensor) is directly in front of ewok

Thoughts: will claw hit the ewok when it's sweeping?
Do we need our robot to step back first
or
Have our claw open
(before ewok_triggering/after ewok_triggering?)

For now, assume these thoughts are not true

Regardless think we should have some functions that are like that after the first ewok
*/
void sweep_find_ewok()
{
    start_event_time = millis(); //use later for sweep_back()

    //sweep depending if the ewok is first sensed by the left or right sensor
    if (left_trigger)
    {
        atb.left_sensor->update();
        // ***
        //turn robot to the left until second (default orientation) sensor of front sensor is less than 30
        // or first 2 (default) sensors of front sensor?
        while (atb.front_sensor->distance_readings[1] < 30)
        {
            atb.left_motor->run(-EWOK_SPEED); //default speed for sweeping <- slow enough for sensors
            atb.right_motor->run(EWOK_SPEED); //default speed for sweeping <- slow enough for sensors

            atb.left_sensor->update();
        }

        //stop robot in the middle?

        //after ewok is centered, make left_trigger back to false
        //left_trigger = false;
    }

    else if (right_trigger)
    {
        atb.right_sensor->update();

        // ***
        //turn robot to the right until second last (default orientation) sensor of front sensor is less than 30
        // or last 2 (default) sensors of front sensor?
        while (atb.front_sensor->distance_readings[6] < 30)
        {
            atb.left_motor->run(EWOK_SPEED);   //default speed for sweeping <- slow enough for sensors
            atb.right_motor->run(-EWOK_SPEED); //default speed for sweeping <- slow enough for sensors

            atb.right_sensor->update();
        }

        //stop robot in the middle?

        //after ewok is centered, make right_trigger back to false
        //right_trigger = false;
    }

    //centering to ewok

    atb.front_sensor->update();

    while (atb.front_sensor->inverse_weighted_mean() != 4.5)
    {
        //to the left of sensor array (default orientation),but ewok to the robot's left -> turn left
        if (atb.front_sensor->inverse_weighted_mean() < 4.5)
        {
            atb.left_motor->run(-EWOK_SPEED); //default speed for sweeping <- slow enough for sensors
            atb.right_motor->run(EWOK_SPEED);
        }

        //to the right of sensor array (default orientation),but ewok to the robot's right -> turn right
        else if (atb.front_sensor->inverse_weighted_mean() > 4.5)
        {
            atb.left_motor->run(EWOK_SPEED); //default speed for sweeping <- slow enough for sensors
            atb.right_motor->run(-EWOK_SPEED);
        }

        atb.front_sensor->update();
    }

    //stop once ewok is located in front of the robot & front sensor
    atb.left_motor->stop();
    atb.right_motor->stop();

    end_event_time = millis(); //use later for sweep_back()
}

//=======================================

/*
	turns robot back to original position after it sweeps left or right to grab an ewok
	function should end when robot is stopped and is back to original position (maybe stepped a bit backwards)
*/
void sweep_back()
{
    unsigned long start_time = millis();

    while (millis() - start_time == end_event_time - start_event_time)
    {
        //if sees ewok in the left before and it swept left, sweep robot to right
        if (left_trigger)
        {
            left_trigger = false;
            atb.left_motor->run(EWOK_SPEED);
            atb.right_motor->run(-EWOK_SPEED);
        }

        //if sees ewok in the right before and it swept right, sweep robot to left
        if (right_trigger)
        {
            right_trigger = false;
            atb.left_motor->run(-EWOK_SPEED);
            atb.right_motor->run(EWOK_SPEED);
        }
    }

    start_event_time = 0;
    end_event_time = 0;
}

//=======================================

void grab_ewok()
{
    //***assume arm is open and in search position in the beginning

    //zero when limit switch is pressed

    //repeat motion of grab_ewok until grabber switch is PRESSED
    while (ARMCONTROL::switchStatus()) // ***
    {
        //arm going down first
        ARMCONTROL::armPickup();

        //close the grabber to get the ewok
        ARMCONTROL::grabberHug();

        //count number of ewoks grabbed or check if the switch is pressed
        if (!ARMCONTROL::switchStatus()) //***
            num_ewok_grabbed++;

        //bring arm up towards the robot's basket
        ARMCONTROL::armDropoff();

        //open grabber
        ARMCONTROL::grabberOpen();

        //set arm back to default horizontal position
        ARMCONTROL::armHorizontal();
    }
}
