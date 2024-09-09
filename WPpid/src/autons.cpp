#include "vex.h"

void default_constants(){
  chassis.set_drive_constants(12, 0.6, 0.02, 4.8, 0);
  // chassis.set_heading_constants(6, .4, 0, 1, 0);
  // chassis.set_turn_constants(9, .4, 0.01, 4, 15);
  // chassis.set_swing_constants(12, .3, .001, 2, 15);
  // chassis.set_drive_exit_conditions(2, 60, 2000);
  // chassis.set_turn_exit_conditions(1, 300, 3000);
  // chassis.set_swing_exit_conditions(1, 300, 2000);
  // chassis.set_drive_constants(10, 0.6, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(10, .4, .035, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(2, 60, 2000);
  chassis.set_turn_exit_conditions(1, 300, 2000);
  chassis.set_swing_exit_conditions(1, 300, 2000);
}

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 12;
  chassis.drive_settle_error = 3;
  // default_constants();
  // chassis.heading_max_voltage = 10;
  // chassis.drive_max_voltage = 8;
  // chassis.drive_settle_error = 3;
}

void drive_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(0,-180);
}

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(12);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-18);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(12);
  chassis.turn_to_angle(0);
}

int odom_test(){
  // chassis.set_coordinates(0, 0, 0);
  while(1) {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
  return 0;
}

void odom_forward_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
 
  chassis.turn_to_angle(0);
  chassis.drive_to_point(0, 24);
chassis.turn_to_angle(0);

}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(12, 12);
  chassis.drive_to_point(12,12);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}