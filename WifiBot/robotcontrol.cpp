#include "robotcontrol.h"

RobotControl::RobotControl()
{

}

void RobotControl::move(short speed1, short speed2, BYTE speedFlag){
   BYTE sbuff[7];
   sbuff[0] = 255 ;
   sbuff[1] = 0x07 ;
   sbuff[2] = (BYTE) speed1 ;
   sbuff[3] = (BYTE) (speed1 >> 8 ) ;
   sbuff[4] = (BYTE) speed2 ;
   sbuff[5] = (BYTE) (speed2 >> 8) ;
   sbuff[6] = speedFlag + 1 ;
}
