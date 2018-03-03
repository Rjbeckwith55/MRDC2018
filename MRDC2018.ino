#include<Servo.h>

//Variable for storing received data
char data = 0;   

//Servos
Servo servo_tilt1;
Servo servo_tilt2;
Servo servo_roller;
Servo servo_arm;
Servo actuator;
Servo servo_joint;

//commands for servos
//arm up, down, buttons released
//Y up, A down
String arm_commands[] = {"b21","b01","b20","b00"};

//claw open, claw close, buttons released
//Left bumper open, Right bumper close
String roller_commands[] = {"b51","b41","b50","b40"};

//ramp up, ramp down, buttons released
//Left trigger up, Right trigger down
String actuator_commands[] = {"ty8","tx8"};

//base up, base down, buttons released
//Left joystick up, Left joystick down
String tilt_commands[] = {"d21","d01","d20","d00"};

//joints up, joints down, buttons released
//Right joystick up, Right joystick down
String joint_commands[] = {"r-6","r+6"};

//for continuos servos
int servo_forward = 200;
int servo_off = 92;
int servo_reverse = 0;


String command;

//loop counter
int i;

void setup()
{
  //Sets the baud for serial data transmission  
  Serial.begin(9600);  

  //Set up servo pins for output
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
     
  //Servo pins for servo control
  servo_roller.attach(2); //thing to pull the rope down
  servo_tilt1.attach(3); //tilt the universal basket with the servo
  servo_tilt2.attach(4); //tilt the universal basket with the servo
  servo_arm.attach(5); //arm used for the hitting of the Simon Says game
  actuator.attach(13); //actuators for moving the basket
}

void loop()
{
  //Wait for data to be recieved
  if(Serial.available() > 0)      
  { 
    //Clear command
    command = "";

    //Store 3 char command
    for(i = 0; i < 3; ++i)
    {
      //Store incoming data
      data = Serial.read();
      command += data;
      delay(3);
    }

    //Move arm up
    if(command == arm_commands[0])
    {
      servo_arm.write(servo_forward);
    }
    //Move arm down
    else if(command == arm_commands[1])
    {
      servo_arm.write(servo_reverse);
    }
    //Stop movement
    else if(command == arm_commands[2] || 
        command == arm_commands[3])
    {
      servo_arm.write(servo_off);
    }

    //Turn on rollers
    if(command == roller_commands[0])
    {
      servo_roller.write(servo_forward);
    }
    //Rollers reverse
    else if(command == roller_commands[1])
    {
      servo_roller.write(servo_reverse);
    }
    //Stop movement
    else if(command == roller_commands[2] || 
        command == roller_commands[3])
    {
      servo_roller.write(servo_off);
    }

    //Actuators up commands
    if(command[1] == 'y' && 
        command[2] > actuator_commands[0][2])
    {
      actuator.write(180);
    }
    //Stop Movement
    else if(command[1] == 'y' &&
        command[2] < actuator_commands[0][2])
    {
      actuator.write(90);
    }
    //Actuators Down
    else if(command[1] == 'x' && 
        command[2] > actuator_commands[1][2])
    {
      actuator.write(0);
    }
    //Stop Movement
    else if(command[1] == 'x' &&
        command[2] < arm_commands[1][2])
    {
      actuator.write(90);
    }

    //Tilt for the bucket servos
    if(command == tilt_commands[0])
    {
      servo_tilt1.write(servo_forward);
      servo_tilt2.write(servo_forward);
    }
    //stop movement
    else if(command == tilt_commands[1])
    {
      servo_tilt1.write(servo_reverse);
      servo_tilt2.write(servo_reverse);

    }
    //stop movement
    else if(command == tilt_commands[3] || command == tilt_commands[2])
    {
      servo_tilt1.write(servo_off);
      servo_tilt2.write(servo_off);
    }

    //Joint up
    if(command[0] == 'r' && 
        command[1] == '-' && 
        command[2] > joint_commands[0][2])
    {
      servo_joint.write(servo_forward);
    }
    //stop movement
    else if(command[0] == 'r' && 
        command[1] == '-' && 
        command[2] < joint_commands[0][2])
    {
      servo_joint.write(servo_off);
    }
    //Joint down
    if(command[0] == 'r' && 
        command[1] == '+' && 
        command[2] > joint_commands[1][2])
    {
      servo_joint.write(servo_reverse);
    }
    //stop movement
    else if(command[0] == 'r' && 
        command[1] == '+' && 
        command[2] < joint_commands[1][2])
    {
      servo_joint.write(servo_off);
    }
    
  }

  //Send data out...
}
