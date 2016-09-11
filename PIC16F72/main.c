/*******************************************Copyright(c)**************************************************
**                        Guangzhou ZHIYUAN electronics Co.,LTD
**
**                           http://www.embedtools.com
**
**---------------File Info--------------------------------------------------------------------------------
** File Name:              mian.c
** Lastest modified Date:  2014-08-28
** Latest Version:         V1.0
** Description:            main������ڣ��߼�����
**
**--------------------------------------------------------------------------------------------------------
** Created By:             Xie JieZhang
** Created date:           2014-08-28
** Version:                V1.0
** Description:            main������ڣ��߼�����
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
** Descriptions:       SPI��ʼ��������I2C������
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/

#include<pic.h>
#include "GPIO.h"
#include "nrf24l01.h"
#define uchar unsigned char
#define uint unsigned int

uchar ucDlyCnt = 0;
uint uiDlyMsCnt = 0;
//ϵͳ����
//�رտ��Ź�,ѡ����پ���,�ϵ���ʱ��λ,���縴λʹ��,���뱣��
__CONFIG(0x0012);
/*********************************************************************************************************
** Function name:      usDelay
** Descriptions:       us��ʱ
** input parameters:   x: ��ʱ����
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void usDelay(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=100;b>0;b--)	NOP();
}
/*********************************************************************************************************
** Function name:      ledByteDisplay
** Descriptions:       LED��ʾһ���ֽ�
** input parameters:   ucData:  Ҫ��ʾ���ֽ�
** output parameters:  ��
** Returned value:     ��
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
** Descriptions:       �������led
** input parameters:   ucComm:  Ҫ��ʾ���ֽ�
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void ledCommContrl(uchar ucComm)
{
    uchar ucTmp,ucIndex;
    for (ucIndex = 0; ucIndex < 3; ucIndex++) {
        ucTmp = ((ucComm   >> ucIndex) & 0x01);                         /* ��ȡָ��                     */

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
** Descriptions:       �������led
** input parameters:   pucData:  Ҫ��ʾ���ֽ�
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void timerInit (void)
{
//    INTCON |= 0xC0;                                                     /* �����жϺ������ж�           */
//    PIE1   |= 0x01;                                                     /* ʹ�ܶ�ʱ��1�ж�              */
    PIR1    = 0x00;                                                     /* �����ʱ���ж�               */ 
    TMR1L   = (65536-1000)%256;
    TMR1H   = (65536-1000)/256;
    T1CON   = 0x10;                                                     /* pre��1/2; Tclk��Fosc/4;T:1Mhz*/
    TMR1ON  = 1;                                                        /* �򿪶�ʱ��1                  */
}

uint uiMsCnt = 0;
void interrupt timer1_ISR()
{
//    if (TMR1IF == 1) {
//        TMR1L   = (65536-60000)%256;
//        TMR1H   = (65536-60000)/256;
//        TMR1IF  = 0;                                                    /* ����жϱ�־                 */
//        uiDlyMsCnt++;
//        uiMsCnt++;
//        if (uiMsCnt == 18) {
//            uiMsCnt = 0;
//            ucDlyCnt++;                                                 /* 1s��һ��                     */    
//        }                                           
//    }
}  
/*********************************************************************************************************
** Function name:      main
** Descriptions:       ���ܺӵ�ʵ�飨ʵ�����󣺣�
** input parameters:   ucData:  Ҫ��ʾ���ֽ�
** output parameters:  ��
** Returned value:     ��
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
*  ��ʼ��
*/
	             
    gpioInit();                                                         /* GPIO��ʼ��                   */
    timerInit();                                                        /* ��ʱ����ʼ��                 */
    spiInit();
    while (0!=nrfInit()) {
        ledRedToggle(); 
        usDelay(200);
    }                                                          /* ����2.4��ʼ��                */ 
    
    ledAllClose();

    //ledAllOpen();
    ucIndex = 20;
    while ((ucIndex--)>0)
    {
        //nrfRxModeSet();
        //if (nrfPacketRx(ucRxBuf)) {                                     /* ��������                     */
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
            TMR1IF  = 0;                                                    /* ����жϱ�־                 */
            uiDlyMsCnt++;
            uiMsCnt++;
            if (uiMsCnt == 180) {
                uiMsCnt = 0;
                ucDlyCnt++;                                                 /* 1s��һ��                     */
            }                                           
        }


        switch (ucState) {
            
        case 0:                                                         /* ���ͻ��������               */
            if (ucMasterFlag) {
                ledRedClose();
                    
                nrfSetTxMode(ucTxBuf); 
                ledByteDisplay(ucTxBuf[0]++);
                //nrfRxModeSet();
                //if (nrfPacketRx(ucRxBuf)) {                             /* ��������                     */
                    //ledByteDisplay(ucRxBuf[0]);   
                //}               
            }
            else {
                nrfRxModeSet();
                if (nrfPacketRx(ucRxBuf)) {                             /* ��������                     */
                    ledByteDisplay(ucRxBuf[0]);   
                } else {
					ledRedOpen();    
                } 
                ucRxBuf[0] = 0x00;
            }

            ucState    = 0;
            uiDlyMsCnt = 0;
            break;

        case 1:                                                         /* �ı�����״̬                 */                                       
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