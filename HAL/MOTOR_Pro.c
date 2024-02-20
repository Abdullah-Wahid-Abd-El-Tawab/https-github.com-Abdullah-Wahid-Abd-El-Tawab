#include "StdTypes.h"
#include "DIO_Int.h"
#include "MOTOR_Int.h"
#include "MOTOR_Cfg.h"
#include "MOTOR_Priv.h"


void MOTOR_Init(void)
{
	// future use
}

void MOTOR_Stop(MOTOR_t motor)
{
	DIO_WritePin( MotorArray[motor][IN1] ,LOW);
	DIO_WritePin( MotorArray[motor][IN2] ,LOW);
}

void MOTOR_CW(MOTOR_t motor)
{
	DIO_WritePin( MotorArray[motor][IN1] ,HIGH);
	DIO_WritePin( MotorArray[motor][IN2] ,LOW);
}

void MOTOR_CCW(MOTOR_t motor)
{
	DIO_WritePin( MotorArray[motor][IN1] ,LOW);
	DIO_WritePin( MotorArray[motor][IN2] ,HIGH);
}