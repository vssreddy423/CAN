#include <lpc17xx.h>
#include <stdint.h>
#include <can.h>
frame_can_t frame_can;
uint8_t i=0;
uint8_t can_data[]={1,2,3,4,5,6,7,8};
void CAN_Msgsent_Frame(void)
{
	frame_can.id=0x25;
	frame_can.frame=DATA_FRAME;
	frame_can.format_type=STANDARD;
	frame_can.data_len=DATA_LENGTH;
	while(i<8)
	{
		frame_can.data[i]=can_data[i];
		i++;
	}
}
int main(void)
{
	Init_CAN1();
	CAN_Msgsent_Frame();
	CAN_Sent_Frame(&frame_can);
	CAN_Receive_Frame();
}
