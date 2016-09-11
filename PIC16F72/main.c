/*******************************************Copyright(c)**************************************************
**                        Guangzhou ZHIYUAN electronics Co.,LTD
**
**                           http://www.embedtools.com
**
**---------------File Info--------------------------------------------------------------------------------
** File Name:              mian.c
** Lastest modified Date:  2014-08-28
** Latest Version:         V1.0
** Description:            main程序入口，逻辑控制
**
**--------------------------------------------------------------------------------------------------------
** Created By:             Xie JieZhang
** Created date:           2014-08-28
** Version:                V1.0
** Description:            main程序入口，逻辑控制
**
**--------------------------------------------------------------------------------------------------------
** Modified By:            
** Modified date:          
** Version:                
** Description:            
**
*********************************************************************************************************/
#include <pic.h>
#include "pic_spi.h"
/*********************************************************************************************************
** Function name:      spiInit
** Descriptions:       SPI初始化，配置I2C波特率
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/

#include<pic.h>
#include "GPIO.h"
#include "nrf24l01.h"
#define uchar unsigned char
#define uint unsigned int

uchar ucDlyCnt = 0;
uint uiDlyMsCnt = 0;
//系统配置
//关闭看门狗,选择高速晶振,上电延时复位,掉电复位使能,代码保护
__CONFIG(0x0012);
/*********************************************************************************************************
** Function name:      usDelay
** Descriptions:       us延时
** input parameters:   x: 延时参数
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void usDelay(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=100;b>0;b--)	NOP();
}
/*********************************************************************************************************
** Function name:      ledByteDisplay
** Descriptions:       LED显示一个字节
** input parameters:   ucData:  要显示的字节
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/

void ledByteDisplay (const uchar ucData)
{
    uchar ucIndex = 0;
    
    ledAllOpen();
    usDelay(2000);
    ucData & 0x1 ? ledYellowOpen(): ledYellowClose(); 
    ucData & 0x2 ? ledRedOpen(): ledRedClose(); 
    ucData & 0x4 ? ledBlueOpen(): ledBlueClose(); 
    usDelay(2000);
    
}
/*********************************************************************************************************
** Function name:      ledCommContrl
** Descriptions:       命令控制led
** input parameters:   ucComm:  要显示的字节
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void ledCommContrl(uchar ucComm)
{
    uchar ucTmp,ucIndex;
    for (ucIndex = 0; ucIndex < 3; ucIndex++) {
        ucTmp = ((ucComm   >> ucIndex) & 0x01);                         /* 获取指令                     */

        switch (ucIndex) {
                
        case 0:
            if ( ucTmp ) {
                ledBlueOpen();    
            } else {
                ledBlueClose();
            }
                break;
            case 1:
                if ( ucTmp ) {
                    ledRedOpen();    
                } else {
                    ledRedClose();
                }
                break;
            case 2:
                if ( ucTmp ) {
                    ledYellowOpen();    
                } else {
                    ledYellowClose();
                }
                break;
            default:
                break;
        }
    }
}
/*********************************************************************************************************
** Function name:      ledCommContrl
** Descriptions:       命令控制led
** input parameters:   pucData:  要显示的字节
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void timerInit (void)
{
//    INTCON |= 0xC0;                                                     /* 开总中断和外设中断           */
//    PIE1   |= 0x01;                                                     /* 使能定时器1中断              */
    PIR1    = 0x00;                                                     /* 清楚定时器中断               */ 
    TMR1L   = (65536-1000)%256;
    TMR1H   = (65536-1000)/256;
    T1CON   = 0x10;                                                     /* pre：1/2; Tclk：Fosc/4;T:1Mhz*/
    TMR1ON  = 1;                                                        /* 打开定时器1                  */
}

uint uiMsCnt = 0;
void interrupt timer1_ISR()
{
//    if (TMR1IF == 1) {
//        TMR1L   = (65536-60000)%256;
//        TMR1H   = (65536-60000)/256;
//        TMR1IF  = 0;                                                    /* 清楚中断标志                 */
//        uiDlyMsCnt++;
//        uiMsCnt++;
//        if (uiMsCnt == 18) {
//            uiMsCnt = 0;
//            ucDlyCnt++;                                                 /* 1s加一次                     */    
//        }                                           
//    }
}  
/*********************************************************************************************************
** Function name:      main
** Descriptions:       智能河灯实验（实验现象：）
** input parameters:   ucData:  要显示的字节
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void main(void)
{
    uchar ucIndex = 0;
    uchar ucTmp = 0;
    uchar ucTxBuf[10] = {0};
    uchar ucRxBuf[10] = {0};
    uchar ucStep   = 1;
    uchar ucState  = 0; 
    uchar ucMasterFlag = 1;
/*
*  初始化
*/
	             
    gpioInit();                                                         /* GPIO初始化                   */
    timerInit();                                                        /* 定时器初始化                 */
    spiInit();
    while (0!=nrfInit()) {
        ledRedToggle(); 
        usDelay(200);
    }                                                          /* 无线2.4初始化                */ 
    
    ledAllClose();

    //ledAllOpen();
    ucIndex = 20;
    while ((ucIndex--)>0)
    {
        //nrfRxModeSet();
        //if (nrfPacketRx(ucRxBuf)) {                                     /* 接收数据                     */
        //    ucMasterFlag = 0; 
        //    break;
        //}
        usDelay(200);
    }
    
	while(1)
	{	
        if (TMR1IF == 1) {
            TMR1L   = (65536-6000)%256;
            TMR1H   = (65536-6000)/256;
            TMR1IF  = 0;                                                    /* 清楚中断标志                 */
            uiDlyMsCnt++;
            uiMsCnt++;
            if (uiMsCnt == 180) {
                uiMsCnt = 0;
                ucDlyCnt++;                                                 /* 1s加一次                     */
            }                                           
        }


        switch (ucState) {
            
        case 0:                                                         /* 发送或接受命令               */
            if (ucMasterFlag) {
                ledRedClose();
                    
                nrfSetTxMode(ucTxBuf); 
                ledByteDisplay(ucTxBuf[0]++);
                //nrfRxModeSet();
                //if (nrfPacketRx(ucRxBuf)) {                             /* 接收数据                     */
                    //ledByteDisplay(ucRxBuf[0]);   
                //}               
            }
            else {
                nrfRxModeSet();
                if (nrfPacketRx(ucRxBuf)) {                             /* 接收数据                     */
                    ledByteDisplay(ucRxBuf[0]);   
                } else {
					ledRedOpen();    
                } 
                ucRxBuf[0] = 0x00;
            }

            ucState    = 0;
            uiDlyMsCnt = 0;
            break;

        case 1:                                                         /* 改变自身状态                 */                                       
            if (ucMasterFlag) {
                ucTxBuf[0] = ucStep;   
                //ledCommContrl(ucStep);
                ucStep++;
                if (ucStep > 0x07 ) {
                    ucStep = 0;
                }
            }
            ucState  = 2;
            ucDlyCnt = 0;

            break;
        case 2:
            if ( ucDlyCnt > 3 && ucMasterFlag == 1) {
                ucState = 1; 
            }else if (uiDlyMsCnt > 10) {
                ucState = 0;
            }
            break;

        default:
            break;       
        }
       
	}
}