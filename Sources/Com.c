/*
 * Com.c
 *
 *  Created on: Mar 5, 2014
 *      Author: Yao
 */
#include "Com.h"
#include "string.h"

/*
 ---------------------------------------------------------------------------------------------------------
   |  0xB7   |   Branch_Num  |   DataLenH  | DataLenL |  TimestampH  |TimestampL    |
   ---------------------------------------------------------------------------------------------------------
   |	
   ---------------------------------------------------------------------------------------------------------
   |                       stateH	| stateL	|	Data	|	0xED                 |
   ---------------------------------------------------------------------------------------------------------
*/
//Prepare the data frame into right format to transmit 
void DataFrame_Format(byte *p )
{
	int i;
	p[0] = 0xB7;
	p[1] = BRANCH_NUM;
	p[2] = BRANCH_DATA_SIZE >> 8;
	p[3] = (byte) BRANCH_DATA_SIZE;
	p[4] = 0; //TimestampH
	p[5] = 0; //TimestampL
	p[6] = 0; //stateH
	p[7] = 0; // stateL
	p += 8;
	for (i = 0; i < USING_CHANNEL_COUNT ;i++)
	{
		*p = 0x11;
		*(p+1) = BRANCH_NUM*USING_CHANNEL_COUNT+i;
		p += CHANNEL_BUF_SIZE;
				
	}
	*p = 0xED;
}

//Push channel data,
void DataFrame_Prepare(byte *p)
{
	p += 8;// Skip the header field
	uint8 i;
	for (i = 0; i < USING_CHANNEL_COUNT ;i++)
	{
		memcpy(p+2, tMCU.mcuData.channelData[i], CHANNEL_DATA_SIZE);//Copy data to transfer buffer
		p += CHANNEL_BUF_SIZE;				
	}

}

void PrepareTheMSG()
{
	int i, j;
		unsigned char *p, *q;
		p = tARM.armDataLeft.dataFrame;
		q = tARM.armDataRight.dataFrame;
		p[0] = q[0] = 0xb7;//branch header
		p[1] = q[1] = BRANCH_NUM;
		p[2] = q[2] = 1616 >> 8;
		p[3] = q[3] = (unsigned char) 1616;
		p += 4;
		q += 4;
		for (i = 0; i < 8; i++)
		{
			*p = *q = 0x11;//channel header
			p++;
			q++;
			*p = *q = i+8*BRANCH_NUM;//channel num
			p++;
			q++;
			for (j = 3; j < 203; j++)
			{
				*p = *q = j;
				p++;
				q++;

			}
		}
		*p = *q = 0xED;//packet end 
}
void MoniData()
{
	int i, j;
	unsigned char *p, *q;
	float r ;
	static  int period = 100; 

	p = tARM.armDataLeft.dataFrame;
	q = tARM.armDataRight.dataFrame;
	p += 4;
	q += 4;
	for (i = 0; i < 1; i++)
	{
		*p = *q = 0x11;//channel header
		p++;
		q++;
		*p = *q = i+8*BRANCH_NUM;//channel num
		p++;
		q++;
		for (j = 0; j < 100; j++)
		{
			r= 1+sin(2*3.1416*j/period);
			*p = *q = (char)(((unsigned int )(r*10000))>>8);
			p++;
			q++;
			*p = *q = (char) ((unsigned int )(r*10000));
			p++;
			q++;

		}
	}

	if(period == 20)
		period = 100;
	else 
		period --;
}
