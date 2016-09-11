/*******************************************Copyright(c)**************************************************
**                        Guangzhou ZHIYUAN electronics Co.,LTD
**
**                           http://www.embedtools.com
**
**---------------File Info--------------------------------------------------------------------------------
** File Name:              nrf24l1.c
** Lastest modified Date:  2014-08-27
** Latest Version:         V1.0
** Description:            GPIO初始化，功能实现
**
**--------------------------------------------------------------------------------------------------------
** Created By:             Xie JieZhang
** Created date:           2014-08-27
** Version:                V1.0
** Description:            nrf24l01功能实现GPIO
**
**--------------------------------------------------------------------------------------------------------
** Modified By:            
** Modified date:          
** Version:                
** Description:            
**
*********************************************************************************************************/
#include "pic.h"
#include "GPIO.h"

/*********************************************************************************************************
** Function name:      gpioInit
** Descriptions:       GPIO初始化
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void gpioInit (void)
{
    GPIO_CONF_OUT(B,0);
    GPIO_CONF_OUT(B,1);
    GPIO_CONF_OUT(B,2);
    GPIO_CONF_OUT(B,3);
    GPIO_CONF_OUT(B,4);
    GPIO_CONF_OUT(B,5);
    GPIO_CONF_OUT(C,0);
    GPIO_CONF_OUT(C,1);
    GPIO_CONF_OUT(C,2);
}
/*********************************************************************************************************
** Function name:      ledAllClose
** Descriptions:       关闭所有LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledAllClose (void)
{
    GPIO_SET(B,0);
    GPIO_SET(B,1);
    GPIO_SET(B,2);
    GPIO_SET(B,3);
    GPIO_SET(B,4);
    GPIO_SET(B,5);
    GPIO_SET(C,0);
    GPIO_SET(C,1);
    GPIO_SET(C,2);
}
/*********************************************************************************************************
** Function name:      ledAllOpen
** Descriptions:       打开所有LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledAllOpen (void)
{
    GPIO_CLR(B,0);
    GPIO_CLR(B,1);
    GPIO_CLR(B,2);
    GPIO_CLR(B,3);
    GPIO_CLR(B,4);
    GPIO_CLR(B,5);
    GPIO_CLR(C,0);
    GPIO_CLR(C,1);
    GPIO_CLR(C,2);
}

/*********************************************************************************************************
** Function name:      ledBlueOpen
** Descriptions:       打开所有蓝色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledBlueOpen (void)
{
    GPIO_CLR(B,0);
    GPIO_CLR(B,3);
    GPIO_CLR(C,0);
}
/*********************************************************************************************************
** Function name:      ledBlueClose
** Descriptions:       关闭所有蓝色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledBlueClose (void)
{
    GPIO_SET(B,0);
    GPIO_SET(B,3);
    GPIO_SET(C,0);
}
/*********************************************************************************************************
** Function name:      ledBlueToggle
** Descriptions:       取反所有蓝色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledBlueToggle (void)
{
    GPIO_TOG(B,0);
    GPIO_TOG(B,3);
    GPIO_TOG(C,0);
}
/*********************************************************************************************************
** Function name:      ledRedOpen
** Descriptions:       打开所有红色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledRedOpen (void)
{
    GPIO_CLR(B,1);
    GPIO_CLR(B,4);
    GPIO_CLR(C,1);
}
/*********************************************************************************************************
** Function name:      ledRedClose
** Descriptions:       关闭所有红色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledRedClose (void)
{
    GPIO_SET(B,1);
    GPIO_SET(B,4);
    GPIO_SET(C,1);
}
/*********************************************************************************************************
** Function name:      ledRedToggle
** Descriptions:       取反所有红色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledRedToggle (void)
{
    GPIO_TOG(B,1);
    GPIO_TOG(B,4);
    GPIO_TOG(C,1);
}

/*********************************************************************************************************
** Function name:      ledYellowOpen
** Descriptions:       打开所有黄色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledYellowOpen (void)
{
    GPIO_CLR(B,2);
    GPIO_CLR(B,5);
    GPIO_CLR(C,2);
}
/*********************************************************************************************************
** Function name:      ledYellowClose
** Descriptions:       关闭所有黄色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledYellowClose (void)
{
    GPIO_SET(B,2);
    GPIO_SET(B,5);
    GPIO_SET(C,2);
}
/*********************************************************************************************************
** Function name:      ledYellowRedToggle
** Descriptions:       取反所有黄色LED
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledYellowToggle (void)
{
    GPIO_TOG(B,2);
    GPIO_TOG(B,5);
    GPIO_TOG(C,2);
}


/*********************************************************************************************************
   End File
*********************************************************************************************************/
