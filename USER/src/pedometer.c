/***********************************************************************************************************************
Copyright 2008 - 2016 深圳市信盈达科技有限公司. All rights reserved.
文件名:        pedometer.c
描述   :       计步算法的应用层代码，不涉及算法。
作者   :       Jahol Fan
版本   :       V1.0
修改   :   
完成日期：     2016.9.25
************************************************************************************************************************/

/***********************************************************************************************************************
* INCLUDES
*/
#include "stm32f4xx.h"
#include "mpu6050.h"
//#include "includes.h"
//#include "stepAlgorithm.h"
#include "pedometer.h"

#include "led.h"

/***********************************************************************************************************************
* CONSTANTS
*/


/***********************************************************************************************************************
* TYPEDEFS
*/


/***********************************************************************************************************************
* LOCAL VARIABLES
*/
OS_TMR   * pedometer_timer;     //计步器软定时器pedometer_timer

/***********************************************************************************************************************
* LOCAL FUNCTIONS  DECLARE
*/
sportsInfo_t userSportsInfo;


/***********************************************************************************************************************
* LOCAL FUNCTIONS  
*/
void Pedometer_timerHandler(void);


/***********************************************************************************************************************
* PUBLIC FUNCTIONS
*/
/**********************************************************************************************************
* 函数名：   
* 功能描述：  
* 作者：          Jahol Fan  
* 参数说明：  
* 返回值说明：
* 修改记录：
**********************************************************************************************************/
u8 Pedometer_init(void)
{
  u8 err;
  //初始化mpu6050 .初始化mpu6050成功且可以获取到6050的ID号                    
  if(0 == MPU_Init())
  {
	  //计步器软定时器pedometer_timer，20ms执行一次
	  pedometer_timer=OSTmrCreate(2,2,OS_TMR_OPT_PERIODIC,
	                              (OS_TMR_CALLBACK)Pedometer_timerHandler,
	                              0,"pedometerTimer",&err);	
	 // Pedometer_startSoftTimer();//启动app_timer	,移到MPU6050读ID函数中
	 
	 return 0;//初始化成功
  }
  return 1;//初始化失败
 
  

                          //初始化成功
}
/**********************************************************************************************************
* 函数名：        Pedometer_startSoftTimer
* 功能描述：      打开计步器的软定时器
* 作者：          Jahol Fan  
* 参数说明：  
* 返回值说明：
* 修改记录：
**********************************************************************************************************/
void Pedometer_startSoftTimer(void)
{
  u8 err;
  OSTmrStart(pedometer_timer,&err);//启动app_timer
}
/**********************************************************************************************************
* 函数名：        Pedometer_stopSoftTimer
* 功能描述：      关闭计步器的软定时器
* 作者：          Jahol Fan  
* 参数说明：  
* 返回值说明：
* 修改记录：
**********************************************************************************************************/
void Pedometer_stopSoftTimer(void)
{
	u8 err;
	OSTmrStop(pedometer_timer,OS_TMR_OPT_NONE,0,&err);//关闭pedometer_timer
	IIC_stop();
}

/**********************************************************************************************************
* 函数名：        Pedometer_timerHandler
* 功能描述：      计步器软定时器
* 作者：          Jahol Fan  
* 参数说明：      none
* 返回值说明：    none
* 修改记录：
**********************************************************************************************************/
void Pedometer_timerHandler(void)
{

  App_postEvent(APP_CAL_STEP_EVENT);

}
/**********************************************************************************************************
* 函数名：        Pedometer_getSportsInfo
* 功能描述：      提供给外部获取计步信息
* 作者：          Jahol Fan  
* 参数说明：      none
* 返回值说明：    none
* 修改记录：
**********************************************************************************************************/
sportsInfo_t *Pedometer_getSportsInfo(void)
{
  return &userSportsInfo;
}

/***********************************************************************************************************************
***********************************************************************************************************************/
