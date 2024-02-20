#include "StdTypes.h"
#include "DIO_Int.h"
#include "MOTOR_Cfg.h"
#include "MOTOR_Priv.h"

const DIO_Pin_t  MotorArray[NUMBER_OF_MOTORS][MOTOR_OF_PIN]={
	
	             /* IN1   IN1*/
	/*MOTOR 1*/  {M1_IN1,M1_IN2},
	/*MOTOR 1*/  {M2_IN1,M2_IN2},
	/*MOTOR 1*/  {M3_IN1,M3_IN2},
	/*MOTOR 1*/  {M4_IN1,M4_IN2}
};
