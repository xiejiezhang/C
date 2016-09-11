/*******************************************Copyright(c)**************************************************
**                        Guangzhou ZHIYUAN electronics Co.,LTD
**
**                           http://www.embedtools.com
**
**---------------File Info--------------------------------------------------------------------------------
** File Name:              nrf24l1.c
** Lastest modified Date:  2014-08-27
** Latest Version:         V1.0
** Description:            GPIO��ʼ��������ʵ��
**
**--------------------------------------------------------------------------------------------------------
** Created By:             Xie JieZhang
** Created date:           2014-08-27
** Version:                V1.0
** Description:            nrf24l01����ʵ��GPIO
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
** Descriptions:       GPIO��ʼ��
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
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
** Descriptions:       �ر�����LED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
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
** Descriptions:       ������LED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
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
** Descriptions:       ��������ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledBlueOpen (void)
{
    GPIO_CLR(B,0);
    GPIO_CLR(B,3);
    GPIO_CLR(C,0);
}
/*********************************************************************************************************
** Function name:      ledBlueClose
** Descriptions:       �ر�������ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledBlueClose (void)
{
    GPIO_SET(B,0);
    GPIO_SET(B,3);
    GPIO_SET(C,0);
}
/*********************************************************************************************************
** Function name:      ledBlueToggle
** Descriptions:       ȡ��������ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledBlueToggle (void)
{
    GPIO_TOG(B,0);
    GPIO_TOG(B,3);
    GPIO_TOG(C,0);
}
/*********************************************************************************************************
** Function name:      ledRedOpen
** Descriptions:       �����к�ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledRedOpen (void)
{
    GPIO_CLR(B,1);
    GPIO_CLR(B,4);
    GPIO_CLR(C,1);
}
/*********************************************************************************************************
** Function name:      ledRedClose
** Descriptions:       �ر����к�ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledRedClose (void)
{
    GPIO_SET(B,1);
    GPIO_SET(B,4);
    GPIO_SET(C,1);
}
/*********************************************************************************************************
** Function name:      ledRedToggle
** Descriptions:       ȡ�����к�ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledRedToggle (void)
{
    GPIO_TOG(B,1);
    GPIO_TOG(B,4);
    GPIO_TOG(C,1);
}

/*********************************************************************************************************
** Function name:      ledYellowOpen
** Descriptions:       �����л�ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledYellowOpen (void)
{
    GPIO_CLR(B,2);
    GPIO_CLR(B,5);
    GPIO_CLR(C,2);
}
/*********************************************************************************************************
** Function name:      ledYellowClose
** Descriptions:       �ر����л�ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledYellowClose (void)
{
    GPIO_SET(B,2);
    GPIO_SET(B,5);
    GPIO_SET(C,2);
}
/*********************************************************************************************************
** Function name:      ledYellowRedToggle
** Descriptions:       ȡ�����л�ɫLED
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
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
