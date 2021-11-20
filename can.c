#include <lpc17xx.h>
#include <stdint.h>
#include <can.h>

__inline static void Set_CAN1_Base_Config(void)
{
  CAN1_Pclk();
  CAN1_IOpins();
}
__inline static void Set_CAN1_Core_Config(void)
{
  CAN1_Bypass();
  CAN1_Normal_RM();
  CAN1_BTR();
  CAN1_Reset_RM();
}
void Init_CAN1(void)
{
  Set_CAN1_Base_Config();
  Set_CAN1_Core_Config();
}
void CAN_Sent_Frame(frame_can_t *can_frame)
{
  uint32_t id,format_type,frame,data_len, data1,data2;
  format_type=(can_frame->format_type) & 0x80000000;
  frame=(can_frame->frame) & 0x40000000;
  data_len=(can_frame->data_len<<16) & 0x000f0000;
  data_len=data_len|format_type|frame;
  if(CAN1_TBS_Status())
  {
    CAN1_TFI(datalen);
    CAN1_Id(can_frame->id);
    data1=*(uint32_t *)&can_frame->data[0];
    CAN1_Data1(data1);
    data2=*(uint32_t *)&can_frame->data[4];
    CAN1_Data2(data2);
    CAN1_CMR();
  }
}
void CAN_Receive_Frame(void)
{
  uint32_t can_data;
  CAN1_RS_Status();
  can_data=CAN1_RFS();
  frame_can.format_type=(can_data &0x80000000);
  frame_can.frame=(can_data & 0x40000000);
  frame_can.data_len=(can_data<<16)&0x000f0000;
  frame_can.id=CAN1_RID();
  if(frame_can.frame==DATA_FRAME)
  {
    *(uint32_t *) & frame_can.data[0]=CAN1_RDA();
    *(uint32_t *) & frame_can.data[4]=CAN1_RDB();
  }
}
