/*
 * Com.h
 *
 *  Created on: Mar 5, 2014
 *      Author: Yao
 */

#ifndef COM_H_
#define COM_H_

#include "MyHeaders.h"


#define CHANNEL_DATA_SIZE         200  //200bytes
#define CHANNEL_BUF_SIZE          202 //1byte(0x01)+1byte(channel number)+200bytes(100ms data 2*100)
#define BRANCH_DATA_SIZE         ( CHANNEL_BUF_SIZE*USING_CHANNEL_COUNT )
#define MSG_SIZE 2000
#define BRANCH_NUM 0
#define SHAKEHAND_SIZE 8
#define CMD_SHKEHAND          1
#define CMD_TRANSFER          2
//ARMÉÏ·¢µÄ×´Ì¬×Ö

void DataFrame_Format(byte *p );
void DataFrame_Prepare(byte *p);

#define STATE_OK              1
#endif /* COM_H_ */
