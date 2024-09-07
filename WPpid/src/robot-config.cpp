#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
// digital_out Hang = digital_out(Brain.ThreeWirePort.H);
// digital_out Balancer = digital_out(Brain.ThreeWirePort.C);
// digital_out Left_Wing = digital_out(Brain.ThreeWirePort.G); //Flipped
// digital_out Right_Wing = digital_out(Brain.ThreeWirePort.F); 
// limit triballsensor = limit(Brain.ThreeWirePort.D);


digital_out Claw = digital_out(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}