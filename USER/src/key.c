#include "key.h"
#include "delay.h"

/******************************************************************************
**������Ϣ ��key_init
**�������� ��������ʼ��Ϊ����GPIO
**������� ��
**������� ��
**������ʾ ��
******************************************************************************/
void key_init()
{
  RCC->AHB1ENR |= 1 << 0;   //PAʱ��ʹ��
  GPIOA->MODER &= ~(3 << 0);//PA0   ͨ������
  GPIOA->PUPDR &= ~(3 << 0);//PA0   ��������
}
/******************************************************************************
**������Ϣ ��key_scan
**�������� ���������
**������� ��
**������� ���������£�����1�������ɿ�����0
**������ʾ ��
******************************************************************************/
u8 key_scan()
{
  static u8 key_sta = 1;
  
  if (key_sta &&  ( KEY==1))   //�������£���״̬�����ڽ���״̬
  {
    key_sta = 0; //���ϰ���״̬��
    delay_ms(10);//ȥ����
    
    if (KEY == 1)//ȥ�����󣬰����������ƽΪ�ߵ�ƽ���򰴼�����
    {
      return 1;  //�������£�����1
    }
    
  }
  else if (KEY == 0)
  {
    key_sta = 1;
  }
  
  return 0;
}