
#include "main.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
 //pragma
 #include "Pragma.h"
#include "pros/screen.hpp"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/*void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//pros::lcd::initialize();
	//on_center_button();
	left_frt.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	left_bck.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_frt.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_bck.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	left_mid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}


void brake(){
	left_frt.move(0);
	left_bck.move(0);
	right_frt.move(0);
	right_bck.move(0);
	left_mid.move(0);
	right_mid.move(0);
}

void intakeBrake(){
	intake_1.move(0);
}


void drive(float l, float r){
	left_frt.move(l);
	left_bck.move(l);
	left_mid.move(l);
	right_frt.move(r);
	right_bck.move(r);
	right_mid.move(r);
}

void intake(float speed){
	intake_1.move(speed);
}

bool shootFlag = true;
bool limitToggle = true;

 void pullbackShoot(){
    shootFlag = !shootFlag;
    limitToggle = !limitToggle;

 while(!limswitch.get_value()&& shootFlag){
   cata.move(70);
   pros::delay(10);
   }
   while(limswitch.get_value()&& !shootFlag){
   cata.move(70);
   pros::delay(10);
   }
   cata.move(0);  


if (limitToggle == true){
      cata.move(0);
  }
  
}

void InchDrive(float target, int speed){
	float x = 0;
	while(x <= target) {
    x = left_bck.get_position()*3.1415*2.75;
	left_frt.move(speed);
	left_bck.move(speed);
	left_mid.move(speed);
    right_frt.move(speed);
	right_bck.move(speed);
	right_mid.move(speed);
    pros::delay(20);
  }
	left_bck.tare_position();
    brake();
}



void task(float speed, float yaw, float error){

	left_bck.move(speed*yaw+(error*abs(int(yaw))));
    right_frt.move(speed*yaw+(error*abs(int(yaw))));
    right_bck.move(-speed-(error*abs(int(yaw))));
	left_frt.move(-speed-(error*abs(int(yaw))));
	pros::screen::print(pros::E_TEXT_LARGE, 5, "Heading: %3f", gyro1.get_yaw());
}



void InchDriveBck(float target, int speed){
	left_bck.tare_position();
	float x = 0;
	while(x >= -target) {
    x = left_bck.get_position()*3.1415*4.0;
	left_frt.move(-speed);
	left_bck.move(-speed);
    right_frt.move(-speed);
	right_bck.move(-speed);
    pros::delay(20);
  }
    brake();
}


void pidTurn(float target, int time){
	float kp = 1;
	float ki = 0;
	float kd = 0.2;
	float error = 0;
	float errorTotal = 0;
	float errorLast = 0;
	float pTerm = 0;
	float iTerm = 0;
	float dTerm = 0;
	float power = 0;
	for (int i = 0; i < time; i+=20){
		errorLast = error;
		error = target - ((((gyro1.get_yaw())+(gyro2.get_yaw()))/(2)));
		errorTotal += error;
		pTerm = error * kp;
		iTerm = ki * errorTotal;
		dTerm = kd * (error - errorLast);
		power = pTerm + iTerm + dTerm;
		left_frt.move(power);
		left_bck.move(power);
		left_mid.move(power);
		right_frt.move(-power);
		right_bck.move(-power);
		right_mid.move(-power);
		pros::delay(20);
	}
	brake();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	left_frt.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	left_bck.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_frt.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_bck.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	left_mid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_mid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	expansion.set_value(false);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
/*	left_bck.tare_position();
	//InchDriveLeft(19, 120);
	//back up and roll roller
	pros::delay(100);
	InchDriveBck(2, 100);
	pros::delay(200);
	InchDriveLeft(19.5, 100);					//ransom
	//pros::delay(1000);
	//InchDrive(2.6, 40);
	drive(50, 50);
	pros::delay(500);
	intake(-84);
	pros::delay(120);
	brake();
	intakeBrake();
	pros::delay(500);
	//drive to spot
	//drive(-50, -50);
	InchDriveBck(3, 100);
	pros::delay(300);
	brake();
	pros::delay(200);
	InchDriveRight(18.5, 90);
	pros::delay(600);
	drive(50,50);
	pros::delay(600);
	brake();
	InchDriveBck(12, 90);
	pros::delay(500);
	//run flywheel and turn
	flywheel(95);
	pidTurn(-179, 2600);
	//brake();
	left_bck.tare_position();
	InchDrive(4, 70);
	//drive(40,40);
	pros::delay(850);
	brake();
	//pros::delay(100);
	//shoot 
	shoot(120);
	flywheel(93);
	pros::delay(1600);
	shoot(120);
	*/
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	left_frt.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	left_bck.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_frt.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_bck.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	left_mid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_mid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    double *x;
    double *y;
	
	bool intake_on = false;
	//piston.set_value(false);
	//int pistonDelay = 0;
	//gps.initialize_full(-0.01, 0.2, -1.8, 1.8, 0);
	//flywheel(85);
	/*
	pros::Task f_PID{ [] {
        while (pros::Task::notify_take(true, TIMEOUT_MAX)) {
            FlywheelPID(300, 72);
        }
    } };
	pros::Task Triple{ [] {
        while (pros::Task::notify_take(true, TIMEOUT_MAX)) {
            TripleShoot(200);
        }
    } }; */
	while (true) {
		//f_PID.notify();
		//pros::screen::print(pros::E_TEXT_LARGE, 1, "Heading: %3f", gyro.get_heading());
		//pros::screen::print(pros::E_TEXT_LARGE, 3, "Flywheel: %3f", flywheel_1.get_actual_velocity());
		//pros::screen::print(pros::E_TEXT_LARGE, 5, "Flywheel 2: %3f", flywheel_2.get_actual_velocity());
		//pros::screen::print(pros::E_TEXT_LARGE, 7, "Yaw: %3f", gyro.get_yaw());
		//MoveBaseTank();
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
			expansion.set_value(true);
		}

		drive(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
		
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
pullbackShoot();		};
/*

		
		if((master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))){
			//xpistonDelay += 3;
			shoot(130);
		}
		
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
			Triple.notify();
		}
		if((master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))){
			if(flywheel_on){
				flywheel(0);
				f_PID.suspend();
				flywheel_on = false;
			}
			else{
				f_PID.resume();
				flywheel_on = true;
			}
		}
		if((master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))){
			if(flywheel_on){
				flywheel(0);
				f_PID.suspend();
				flywheel_on = false;
			}
			else{
				flywheel(127);
				f_PID.suspend();
				flywheel_on = true;
			}
		} */
		if((master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))){
			intake(127);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			intake(-127);
		}
		else{
			intake(0);
		}
	}
	pros::delay(20);
}
