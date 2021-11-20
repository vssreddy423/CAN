#ifndef __CAN_H__
#define __CAN_H__
#define STANDARD_ID 0
#define EXTENDED_ID 1
#define DATA_FRAME 0
#define REMOTE_FRAME 1
// CAN data format-- START|11 0r 29 bit identifier|RTR|IDE|DLC|DATA|CRC|ACK|EOF|IFS
typedef struct
{
uint16_t id;         //11 or 29 bit ID
uint8_t format_type; // RTR--Data frame-0, Remote frame-1
uint8_t frame;       //IDE --Standard-0, Extended-1
uint8_t data_len;    //data length
uint8_t data[8];     //data field
}

// Peripheral Clock
#define CAN1_Pclk()               LPC_SC->PCONP=(1<<13)
// Input and Output --TD1,RD1
#define CAN1_IOpins()             LPC_PINCON->PINSEL0=(5<<0)
// Bypass mode acive
#define CAN1_Bypass()             LPC_CANAF->AFMR=(2<<0)
// Reset mode - Normal & Reset
#define CAN1_Reset_RM()           LPC_CAN1->MOD=(1<<0)
#define CAN1_Normal_RM()          LPC_CAN1->MOD=0
// Baud Rate Prescalar, time segment 1&2
#define BRP   12
#define TSEG1 12
#define TSEG2  1
#define CAN1_BTR()                LPC_CAN1->BTR=(TSEG2<<20)|(TSEG1<<16)|(BRP<<0)
// Trasmit Buffer Status check to write in TFI
#define CAN1_TBS_Status()         LPC_CAN1->SR &(1<<2)
// Receive Status to read RFS
#define CAN1_RS_Status()          while(LPC_CAN1->SR &(1<<4))
//  Trasmission requirements
#define CAN1_TFI(datalen)         LPC_CAN1->TFI1=datalen
#define CAN1_Id(id)               LPC_CAN1->TID1=id
#define CAN1_Data1(data)          LPC_CAN1->TDA1=data
#define CAN1_Data2(data)          LPC_CAN1->TDB1=data
//  Receiver requirements
#define CAN1_RFS()                LPC_CAN1->RFS
#define CAN1_RID()                LPC_CAN1->RID
#define CAN1_RDA()                LPC_CAN1->RDA


__inline static void Set_CAN1_Base_Config(void);
__inline static void Set_CAN1_Core_Config(void);
void Init_CAN1(void);
void CAN_Sent_Frame(frame_can_t *can_frame);
void CAN_Receive_Frame(void);
#endif

