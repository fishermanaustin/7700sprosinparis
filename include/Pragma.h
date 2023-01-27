
#ifndef _PROS_PRAGMA_H_
#define _PROS_PRAGMA_H_
#include "api.h"
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::ADIDigitalOut expansion('B', false);
pros::ADIDigitalIn limswitch('A');
pros::Motor left_frt(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor left_bck(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor left_mid(3, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor right_frt(4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor right_bck(5, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor right_mid(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor intake_1(7, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor cata(8, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Imu gyro1(9);
pros::Imu gyro2(10);
#endif 
