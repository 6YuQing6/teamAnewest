#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

// motor leftMotorA = motor(PORT18, ratio6_1, true); 
// motor leftMotorB = motor(PORT19, ratio6_1, true);
// motor leftMotorC = motor(PORT20, ratio6_1, true);
// motor leftMotorD = motor(PORT1/*placeholder!!!!*/, ratio18_1, true);//also placeholder!!!!
// motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC, leftMotorD);

// motor rightMotorA = motor(PORT11, ratio6_1, false);
// motor rightMotorB = motor(PORT12, ratio6_1, false);
// motor rightMotorC = motor(PORT13, ratio6_1, false);
// motor rightMotorD = motor(PORT1/*placeholder!!!!*/, ratio18_1, true);//also placeholder!!!!
// motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC, rightMotorD);

// inertial DrivetrainInertial = inertial(PORT21);
// smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 10.21018, 10.8, 12, inches, 0.6);
// //controller Controller1 = controller(primary);
// motor Intake = motor(PORT14, ratio6_1, false);
// motor Cata = motor(PORT15, ratio6_1, false);
// motor Cata1 = motor(PORT16, ratio6_1, false);

///////////////////

motor leftDriveA = motor(PORT9, ratio6_1, true);
motor leftDriveB = motor(PORT20, ratio6_1, false); 
motor leftDriveC = motor(PORT5, ratio6_1, true);

motor rightDriveA = motor(PORT10, ratio6_1, false);
motor rightDriveB = motor(PORT7, ratio6_1, true); //works
motor rightDriveC = motor(PORT8, ratio6_1, false);  //8

inertial DrivetrainInertial = inertial(PORT8);

controller Controller1 = controller(primary);

motor Intake = motor(PORT1, ratio6_1, false);
motor Arm = motor(PORT2, ratio18_1, true); // 5.5W motor 
motor Intake2 = motor(PORT15, ratio18_1, false); // 5.5W Motor 

motor_group LeftDriveSmart = motor_group(leftDriveA, leftDriveB, leftDriveC);

motor_group RightDriveSmart = motor_group(rightDriveA, rightDriveB, rightDriveC);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 299.24, 320, 40, mm, 1.3334);

rotation forwad = rotation(PORT17);
rotation sideway = rotation(PORT4);
Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
TANK_TWO_ROTATION,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2"

//Left Motors:
LeftDriveSmart,

//Right Motors:
RightDriveSmart,

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT3,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
1.3333334,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
PORT17, //Will do later

//Input the Forward Tracker diameter (reverse it to make the direction switch):
-2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-0.125
,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
PORT4,

//Sideways tracker diameter (reverse to make the direction switch):
2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
3.125

);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  while(auto_started == false){            //Changing the names below will only change their names on the
    Brain.Screen.clearScreen();            //brain screen for auton selection.
    // switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
    //   case 0:
    //     Brain.Screen.printAt(50, 50, "Drive Test");
    //     break;
    //   case 1:
    //     Brain.Screen.printAt(50, 50, "Drive Test");
    //     break;
    //   case 2:
    //     Brain.Screen.printAt(50, 50, "Turn Test");
    //     break;
    //   case 3:
    //     Brain.Screen.printAt(50, 50, "Swing Test");
    //     break;
    //   case 4:
    //     Brain.Screen.printAt(50, 50, "Full Test");
    //     break;
    //   case 5:
    //     Brain.Screen.printAt(50, 50, "Odom Test");
    //     break;
    //   case 6:
    //     Brain.Screen.printAt(50, 50, "Tank Odom Test");
    //     break;
    //   case 7:
    //     Brain.Screen.printAt(50, 50, "Holonomic Odom Test");
    //     break;
    // }
    // if(Brain.Screen.pressing()){
    //   while(Brain.Screen.pressing()) {}
    //   current_auton_selection ++;
    // } else if (current_auton_selection == 8){
    //   current_auton_selection = 0;
    // }
    task::sleep(10);
  }
}
//void auton_red_left() {
  
  // chassis.set_coordinates(-50, 23, 90);
  // Claw.set(true); //change later after sayansh tests it
  // chassis.drive_to_point(-23.5, 23.5);
  // //Get the mobile goal
  // Claw.set(false);
  // chasis.turnFor(-90, degrees);
  // chassis.drive_to_point(-23.776, 40.5);
  // chassis.turnFor(180, degrees);
  // chassis.drive_to_point(-23.8, 32.4);
  // chassis.turnFor(-120, degrees);
  // chassis.drive_to_point(-11.6, 38.7);
  // chassis.turnFor(150, degrees);
  // chassis.drive_to_point(-10.7, 12.5);
//}

void auton_red_right() {
  // chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  // chassis.set_heading_constants(6, .4, 0, 1, 0);
  // chassis.set_turn_constants(11, .3, .03, 3, 15);
  // chassis.set_swing_constants(12, .3, .001, 2, 15);
  // chassis.set_drive_exit_conditions(2, 60, 5000);
  // chassis.set_turn_exit_conditions(1, 300, 3000);
  // chassis.set_swing_exit_conditions(1, 300, 3000);
  // chassis.heading_max_voltage = 10;
  // chassis.drive_max_voltage = 8;
  // chassis.drive_settle_error = 3;
  //Intake.spin(forward, 100, pct);

  chassis.set_heading(270);
  chassis.set_coordinates(-60, -24, 270);
  chassis.set_heading(270);
  Claw.set(false); //change later after sayansh tests it
  chassis.turn_to_point(-200, -22);
  chassis.drive_to_point(-15, -22);
  //Get the mobile goal
  
  Claw.set(true);
  wait(0.5, sec);
  chassis.set_coordinates(-15, -24, 270);
  chassis.turn_to_point(-21, -58);
  Intake.spin(forward, 100, pct);
  Intake2.spin(forward, 100, pct);
  chassis.drive_to_point(-21, -52);
  //ring 2
  wait(0.5, sec);
  //chassis.drive_distance(-22);
  
  //Intake.stop();
  
  
  chassis.turn_to_point(-19, -37);
  wait(0.5, sec);
  Claw.set(false);
  wait(0.3, sec);
  chassis.drive_distance(5);
  chassis.turn_to_point(-40, -34);
  chassis.drive_distance(-24);
  Intake.stop();
  Claw.set(true);
  wait(0.5, sec);
  chassis.turn_to_point(-5, -13);
  chassis.drive_distance(25);

  Arm.spin(reverse, 40, pct);
  


  //chassis.drive_distance(10);


  /*
  //double angle1 = atan((-2.378) - chassis.odom.X_position /  (-45.593) - chassis.odom.Y_position);
  Brain.Screen.print(angle1);
  chassis.turn_to_angle(angle1 + 180);
  chassis.drive_distance(-20);
  chassis.drive_to_point(-2.378,-45.593);
  Claw.set(true);
  chassis.turn_to_point(-11, -17);
  chassis.drive_to_point(-11, -17);
  */




  /*
  chassis.turn_to_point(-47,0);
  Intake.spin(forward, 100, pct);
  chassis.drive_to_point(-47, 0);
  wait(1, sec);
  Intake.stop();
  */
  
}


void auton_blue_right() {
  // chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading(90);
  chassis.set_coordinates(60, -24, 90);
  chassis.set_heading(90);
  Claw.set(false); //change later after sayansh tests it
  chassis.turn_to_point(200, -23);
  chassis.drive_to_point(15, -23);
  //Get the mobile goal
  
  
  Claw.set(true);
  wait(0.5, sec);
  chassis.set_coordinates(15, -24, 90);
  chassis.turn_to_point(21, -58);
  Intake.spin(forward, 100, pct);
  chassis.drive_to_point(21, -53);
  //ring 2
  wait(0.5, sec);
  //chassis.drive_distance(-22);
  
  //Intake.stop();
  
  
  chassis.turn_to_point(19, -37);
  wait(0.5, sec);
  Claw.set(false);
  wait(0.3, sec);
  chassis.drive_distance(5);
  chassis.turn_to_point(40, -34);
  chassis.drive_distance(-24);
  Intake.stop();
  Claw.set(true);
  wait(0.5, sec);
  chassis.turn_to_point(5, -13);
  chassis.drive_distance(25);

  Arm.spin(reverse, 40, pct);
}





void auton_blue_left() {
  chassis.set_heading(90);
  chassis.set_coordinates(60, 24, 90);
  chassis.set_heading(90);
  Claw.set(false); //change later after sayansh tests it
  chassis.turn_to_point(200, 22);
  chassis.drive_to_point(16, 23);
  //Get the mobile goal
  
  Claw.set(true);
  wait(0.5, sec);

  //chassis.set_coordinates(-15, 24,270);
  chassis.turn_to_point(21, 58);
  Intake.spin(forward, 100, pct);
  Intake2.spin(forward, 100, pct);
  chassis.drive_to_point(21, 52);
  //ring 2
  wait(0.5, sec);
  chassis.drive_distance(-12);
  chassis.turn_to_point(2,50);
  chassis.drive_to_point(2,50);
  chassis.drive_distance(10);
  wait(2, sec);
 
  //ring 3
  chassis.turn_to_point(-8, 32);
  chassis.drive_distance(-20);
  chassis.turn_to_point(6, 50);
  chassis.drive_distance(20);
}

void auton_rush_blue_left() {
  
}



void auton_red_left()  {
  vex::task runOdom(odom_test);
  // runOdom.stop();
  // odom_test();
  chassis.set_heading(270);
  chassis.set_coordinates(-60, 24, 270);
  chassis.set_heading(270);
  Claw.set(false); 
  chassis.turn_to_point(-200, 22);
  chassis.drive_to_point(-15, 22);
  // odom_test();
  //Get the mobile goal
//  runOdom.resume();
//   runOdom.stop();
  Claw.set(true);
  wait(0.5, sec);
  // odom_test();
  //chassis.set_coordinates(-15, 24,270);
  chassis.turn_to_point(-21, 58);
  Intake.spin(forward, 100, pct);
  Intake2.spin(forward, 100, pct);
  chassis.drive_to_point(-21, 50);
//  runOdom.resume();
// runOdom.stop();
  // odom_test();
  
  //ring 2
  //Intake.spin(forward, 100, pct);
  //Intake2.spin(forward, 100, pct);
  wait(0.5, sec);
  chassis.drive_distance(-10);
  chassis.turn_to_point(1,50);
  chassis.drive_to_point(1,50);
  chassis.drive_distance(-7);
  chassis.turn_to_point(-1,54);
  chassis.drive_to_point(-1,54);
  odom_test();
  //runOdom.resume();
  //runOdom.stop();

  //chassis.drive_distance(-22);
  
  //Intake.stop();
  
  
  // chassis.turn_to_point(-19, 37);
  // wait(0.5, sec);
  // //Claw.set(false);
  // wait(0.3, sec);
  // chassis.drive_distance(5);
  // chassis.turn_to_point(-40, 34);
  // chassis.drive_distance(-24);
  // Intake.stop();
  // Claw.set(true);
  // wait(0.5, sec);
  // chassis.turn_to_point(-5, 13);
  // chassis.drive_distance(25);

  // Arm.spin(reverse, 40, pct);
}
  


//skills functions


void firstStake() {
  chassis.set_coordinates(-59, 0, 0);
  chassis.turn_to_point(-67, 17);
  chassis.drive_to_point(-47, -24);
  Claw.set(true);
  Intake.spin(forward, 100, pct);
  Intake2.spin(forward, 100, pct);
  chassis.drive_to_point(-24, -24);
  chassis.turn_to_point(-23, -47);
  chassis.drive_to_point(-23, -47);
  chassis.turn_to_point(-47, -47);
  chassis.drive_to_point(-47, -47);

  chassis.drive_to_point(-59, -47);
  chassis.turn_to_point(-47, -59);
  chassis.drive_to_point(-47, -59);
  chassis.turn_to_point(0, -59);
  chassis.drive_to_point(0, -59);
  chassis.turn_to_point(-59, -59);
  chassis.drive_to_point(-59, -59);
  chassis.turn_to_point(-47, -47);
  Claw.set(false);
}


void secondStake() { 
  chassis.drive_to_point(-47, -24);
  chassis.turn_to_point(-47, -47);
  chassis.drive_to_point(-47, 24);
  Claw.set(true);
  Intake.spin(forward, 100, pct);
  Intake2.spin(forward, 100, pct);
  chassis.turn_to_point(-23, 23);
  chassis.drive_to_point(-23, 23);
  chassis.turn_to_point(-23, 47);
  chassis.drive_to_point(-23, 47);
  chassis.turn_to_point(-47, 47);
  chassis.drive_to_point(-47, 47);
  chassis.drive_to_point(-59, 47);
  chassis.turn_to_point(-47, 59);
  chassis.drive_to_point(-47, 59);
  chassis.turn_to_point(0, 59);
  chassis.drive_to_point(0, 59);
  chassis.turn_to_point(-61, 61);
  chassis.drive_to_point(-61, 61);
  chassis.turn_to_point(-47, -47);
  Claw.set(false);
}

void thirdStake() {
  chassis.turn_to_point(45, 29);
  chassis.drive_to_point(45, 29);
  chassis.turn_to_point(46, 39);
  chassis.drive_to_point(47, 0);
  Claw.set(true);
  chassis.turn_to_point(23, -23);
  chassis.drive_to_point(23, -23);
  chassis.turn_to_point(23, -47);
  chassis.drive_to_point(23, -47);
  chassis.turn_to_point(51, -47);
  chassis.drive_to_point(51, -47);
  chassis.turn_to_point(44, -63);
  chassis.drive_to_point(44, -63);
  chassis.turn_to_point(32, -63);
  chassis.drive_to_point(63, 65);
  Claw.set(false);
}


void autonomous(void) {
  // auton_blue_left();
  odom_forward_test();

 // tank_odom_test();
  // auton_red_left();
  //chassis.set_coordinates(0, 0, 0);
 //chassis.turn_to_point(10, 10);
  //chassis.drive_to_point(0, 10);
  // chassis.set_coordinates(0, 0, 0);
  // while(1){

  //   Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
  //   Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
  //   Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
  //   Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
  //   Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
  //   chassis.odom.update_position(chassis.get_ForwardTracker_position(), chassis.get_SidewaysTracker_position(), chassis.get_absolute_heading());
  //   task::sleep(20);
  //   Brain.Screen.clearScreen();
  // }


  // chassis.set_coordinates(-50, 23, 90);
  // Claw.set(true); //change later after sayansh tests it
  // chassis.drive_to_point(-23.5, 23.5);
  //Get the mobile goal
  // Claw.set(false);
  // chasis.turnFor(-90, degrees);
  // chassis.drive_to_point(-23.776, 40.5);
  // chassis.turnFor(180, degrees);
  // chassis.drive_to_point(-23.8, 32.4);
  // chassis.turnFor(-120, degrees);
  // chassis.drive_to_point(-11.6, 38.7);
  // chassis.turnFor(150, degrees);
  // chassis.drive_to_point(-10.7, 12.5);

//   current_auton_selection= 4;
//   switch(current_auton_selection){  
//     case 0:
//       drive_test(); //This is the default auton, if you don't select from the brain.
//       break;        //Change these to be your own auton functions in order to use the auton selector.
//     case 1:         //Tap the screen to cycle through autons.
//       drive_test();
//       break;
//     case 2:
//       turn_test();
//       break;
//     case 3:
//       swing_test();
//       break;
//     case 4:
//       full_test();
//       break;
//     case 5:
//       odom_test();
//       break;
//     case 6:
//       tank_odom_test();
//       break;
//     case 7:
//       holonomic_odom_test();
//       break;
//  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  bool DrivetrainLNeedsToBeStopped_Controller1 = true;
  bool DrivetrainRNeedsToBeStopped_Controller1 = true;

  bool Claw_toggle = false; 
  bool Arm_toggle = false;
  bool Hang_toggle = false;



  while (1) {
    // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis3.position();
      int drivetrainRightSideSpeed = Controller1.Axis2.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      if (Controller1.ButtonL1.pressing()) {
        Intake.spin(fwd, 100, pct);
        Intake2.spin(fwd, 100, pct);
      } else if (Controller1.ButtonL2.pressing()) {
        Intake.spin(reverse, 100, pct);
        Intake2.spin(fwd, 100, pct);
      } else {
        Intake.stop();
        Intake2.stop();
      }

      if (Claw_toggle) {             
        Claw.set(true);
      } else {
        Claw.set(false);
      }

      if (Controller1.ButtonA.pressing()) {
        Claw_toggle = !Claw_toggle;
        waitUntil(!Controller1.ButtonA.pressing());
      }
     

// up and down button
      if (Arm_toggle) {             
        ArmPump.set(true);
      } else {
        ArmPump.set(false);
      }

      if (Controller1.ButtonUp.pressing()) {
        Arm_toggle = true;
        waitUntil(!Controller1.ButtonUp.pressing());
      }
      else if (Controller1.ButtonDown.pressing()) {
        Arm_toggle = false;
        waitUntil(!Controller1.ButtonDown.pressing());
      }


// y button
      if (Hang_toggle) {             
        HangPump.set(true);
      } else {
        HangPump.set(false);
      }

      if (Controller1.ButtonY.pressing()) {
        Hang_toggle = !Hang_toggle;
        waitUntil(!Controller1.ButtonY.pressing());
      }
     




    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();


    if(Controller1.ButtonL1.pressing()) {
      Intake.spin(fwd, 100, pct);
      Intake2.spin(fwd, 100, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      Intake.spin(reverse, 100, pct);
      Intake2.spin(reverse, 100, pct);
    } else {
      Intake.stop(brake); // change to hold or coast or brake
      Intake2.stop(brake);
    }

  
    if(Controller1.ButtonR1.pressing()) {
      Arm.spin(fwd, 100, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      Arm.spin(reverse, 100, pct);
    } else {
      Arm.stop(hold); // change to hold or coast or brake
    }
    wait(20, msec); // Sleep the task for a short amount of time to

  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
