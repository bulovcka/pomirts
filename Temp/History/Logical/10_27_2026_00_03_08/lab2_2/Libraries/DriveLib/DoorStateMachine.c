
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
#include "DriveLib.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void DoorStateMachine(struct DoorStateMachine* inst)
{
	// 
	switch (inst->state){
		case ST_INIT:
			inst->speed = 0;
			inst->state=ST_UNKNOWN;
			break;
		
		case ST_UNKNOWN:
			if (inst->sw1 && inst->direction == 0){
				inst->state = ST_OPEN;
				break;
			} else if (inst->sw4 && inst->direction == 1){
				inst->state = ST_CLOSE;
				break;
			} else {
				inst->speed = (inst->direction == 0)?-50:50;
				break;
			}
		
		case ST_OPEN:
			if (inst->direction == 0){
				inst->speed = 0;
				break;
			}
			else if (inst->direction == 1){
				inst->state = ST_ACC_POS;
				break;
			
			else {
				inst->state = ST_UNKNOWN;
				break;
			}
		
		case ST_ACC_POS:
			if (inst->direction == 1 && !inst->sw2){
				inst->speed = 100;	
				break;
			}
			else if (inst->direction == 1 && inst->sw2){
				inst->state = ST_POS;
				break;
			}
			else if (inst->direction == 0) {
				inst->state = ST_DEC_NEG;
				break;
			} 
			else {
				inst->speed = 0;
				inst->state = ST_UNKNOWN;
				break;
			}
		
		case ST_POS:
			if (inst->direction == 1 && !inst->sw3){
				inst->speed = 200;
				break;
			}
			else if (inst->direction == 1){
				inst->state = ST_DEC_POS;
				break;
			}
			else if (inst->direction == 0){
				inst->state = ST_NEG;
				break;
			}
			else{
				inst->state = ST_UNKNOWN;
				break;
			}
		
		case ST_DEC_POS:
			if (inst->direction == 1 && !inst->sw4){
				inst->speed=100;
				break;
			}
			else if (inst->direction == 1 && inst->sw4)
			{
				inst->state = ST_CLOSE;
				break;
			}
			else if (inst->direction == 0)
			{
				inst->state = ST_ACC_NEG;
				break;
			}
			else{
				inst->state = ST_UNKNOWN;
				break;
			}
		
		case ST_CLOSE:
			if (inst->direction == 1)
			{
				inst->speed = 0;
				break;
			}
			else if(inst->direction == 0){
				inst->state = ST_ACC_NEG;
				break;
			}
			else
			{
				inst->state = ST_UNKNOWN;
				break;
			}
		
		case ST_ACC_NEG:
			if (inst->direction == 0 && !inst->sw3){
				inst->speed = -100;
				break;
			}
			else if (inst->sw3){
				inst->state = ST_NEG;
				break;
			}
			else if (inst->direction == 1){
				inst->state = ST_DEC_POS;
				break;
			}
			else {
				inst->state = ST_UNKNOWN;
				break;
			}
		
		case ST_NEG:
			if (inst->direction == 0 && !inst->sw2){
				inst->speed = -200;
				break;
			}
			else if (inst->direction == 0) {
				inst->state = ST_DEC_NEG;
				break;
			}
			else if (inst->direction == 1){
				inst->state = ST_POS;
				break;
			}
			else{
				inst->state = ST_UNKNOWN;
				break;
			}
		case ST_DEC_NEG:
			if (inst->direction == 0 && !inst->sw1){
				inst->speed = -100;
				break;
			}
			else if(inst->direction == 0){
				inst->state = ST_OPEN;
				break;
			}
			else if (inst->direction == 1){
				inst->state = ST_ACC_POS;
				break;
			}
			else {
				inst->state = ST_UNKNOWN;
				break;
			}
				
	}
}

