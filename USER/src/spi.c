/***********************************************************************************************************************
Copyright 2008 - 2016 深圳市信盈达电子有限公司. All rights reserved.
文件名:        spi.c
描述   :       spi底层驱动
作者   :        
版本   :       V1.0
修改   :   
完成日期：     2016.10.13
信盈达官网：http://www.edu118.com/
信盈达网校：http://www.edu118.cn/
Notice    :本程序只供学习使用，未经作者许可，不得用于其它任何用途。版权所有，盗版必究。
************************************************************************************************************************/

/***********************************************************************************************************************
 * INCLUDES
 */
#include "spi.h"

/***********************************************************************************************************************
 * CONSTANTS
 */


/***********************************************************************************************************************
 * TYPEDEFS
 */


/***********************************************************************************************************************
 * LOCAL VARIABLES
 */
 
/***********************************************************************************************************************
 * LOCAL FUNCTIONS  DECLARE
 */


/***********************************************************************************************************************
 * LOCAL FUNCTIONS  
 */



/***********************************************************************************************************************
 * PUBLIC FUNCTIONS
 */
/**********************************************************************************************************
* 函数名    ：   Spi1_init
* 功能描述  ：   SPI1初始化
* 作者      ：      
* 参数说明  ：  
* 返回值说明：
* 修改记录  ：
* 其他      :
*							PB3----SCK
*							PB4----MISO
*							PB5----MOSI
**********************************************************************************************************/
void Spi1_init(void)
{
	RCC->AHB1ENR |= 1<<1;//PB时钟使能  
	RCC->APB2ENR |= 1<<12;//SPI1  
	
	/* PB3/4/5 AF5功能 */
	GPIOB->MODER &= ~(0X3F << 6);
	GPIOB->MODER |= 0X2A << 6;
	
	GPIOB->AFR[0] &= ~(0XFFF << 12);
	GPIOB->AFR[0] |= 0X555 << 12;//   af5功能
	
	GPIOB->OSPEEDR &= ~(0X3F << 6);// io输出速度 50MHZ
	GPIOB->OSPEEDR |= 0X2A << 6;
		
	/* SPI1配置 */  
	SPI1->CR1 = 0;
	SPI1->CR1 |= 3 << 8;//SSM  SSI
	
	SPI1->CR1 |= 1 << 2;//主模式
	
//	SPI1->CR1 |= 4 << 3;//速度  100/64 MHZ
	
	SPI1->CR1 |= 1 << 6;//使能SPI1
}
/**********************************************************************************************************
* 函数名    ：   Spi1_RevSendByte
* 功能描述  ：   SPI1收发一个字节
* 作者      ：      
* 参数说明  ：   val：待发送的数据
* 返回值说明：   接收到一个字节
* 修改记录  ：
* 其他      :
*							PB3----SCK
*							PB4----MISO
*							PB5----MOSI
**********************************************************************************************************/
u8 Spi1_RevSendByte(u8 val)
{
	while ((SPI1->SR & (1<<1)) == 0)
	{
		;//等待发送缓存区为空
	}
	SPI1->DR = val;
	
	while ((SPI1->SR & (1<<0)) == 0)
	{
		;//等待接收缓存区非空
	}
	
	return (SPI1->DR);
}

/***********************************************************************************************************************
***********************************************************************************************************************/
